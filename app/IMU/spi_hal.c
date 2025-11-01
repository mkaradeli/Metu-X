/*
 * Copyright 2021 CEVA, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License and 
 * any applicable agreements you may have with CEVA, Inc.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * SPI-based HALs for SH2 and DFU.
 */

#include "sh2_hal_init.h"

#include "sh2.h"
#include "sh2_hal.h"
#include "sh2_err.h"

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "gpio.h"
#include "tim.h"
#include "spi.h"

#include "globals.h"

// Keep reset asserted this long.
// (Some targets have a long RC decay on reset.)
#define RESET_DELAY_US (10000)

// Wait up to this long to see first interrupt from SH
#define START_DELAY_US (2000000)

// How many bytes to read when reading the length field
#define READ_LEN (4)

// ------------------------------------------------------------------------
// Private types

typedef enum SpiState_e
{
    SPI_INIT,
    SPI_DUMMY,
    SPI_DFU,
    SPI_IDLE,
    SPI_RD_HDR,
    SPI_RD_BODY,
    SPI_WRITE
} SpiState_t;

// ------------------------------------------------------------------------
// Private data

// Dummy transmit data for SPI reads
static uint8_t txZeros[SH2_HAL_MAX_TRANSFER_IN] = {0};

// SPI Bus access state machine state
static SpiState_t spiState = SPI_INIT;

// Timestamp
static volatile uint32_t rxTimestamp_us;

// true from time SH is put in reset until first INTN indication
static volatile bool inReset;

// set true when INTN is observed, until RX operation starts
static volatile bool rxReady;

// Receive support
static uint8_t rxBuf[SH2_HAL_MAX_TRANSFER_IN];
static volatile uint32_t rxBufLen;
static volatile bool rxDataReady;

// Transmit support
static uint8_t txBuf[SH2_HAL_MAX_TRANSFER_OUT];
static uint32_t txBufLen;

// Instances of the SPI HAL for SH2 and DFU
static sh2_Hal_t sh2Hal;

static bool isOpen = false;

osThreadId imuTaskHandle;

static uint8_t checker = 0;
// ------------------------------------------------------------------------
// Private methods

static void bootn(bool state)
{
 // NOT SETTED
}

static void rstn(bool state)
{
    HAL_GPIO_WritePin(IMU_RST_GPIO_Port, IMU_RST_Pin,
                      state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

static void ps0_waken(bool state)
{
    HAL_GPIO_WritePin(IMU_WAKE_GPIO_Port, IMU_WAKE_Pin,
                      state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

static void ps1(bool state)
{
	 // NOT SETTED
}

static void csn(bool state)
{
    HAL_GPIO_WritePin(IMU_CS_GPIO_Port, IMU_CS_Pin,
                      state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

static uint32_t timeNowUs(void)
{
    return micros();
}

static void hal_init_timer(void)
{
	// SETTED EXTERNALLY
}

static void hal_init_gpio(void)
{

}

static void spiDummyOp(void)
{
    // We need to establish SCLK in proper initial state.
    // Do one SPI operation with reset asserted and no CS asserted to get clock sorted.
    uint8_t dummyTx[1];
    uint8_t dummyRx[1];
    
    memset(dummyTx, 0xAA, sizeof(dummyTx));

    HAL_SPI_TransmitReceive(&hspi1, dummyTx, dummyRx, sizeof(dummyTx), 2);
}

static void hal_init_spi(bool dfu)
{
	// SETTED EXTERNALLY
}

static void hal_init_hw(bool dfu)
{
    hal_init_timer();
    hal_init_gpio();
    hal_init_spi(dfu);
}

static void enableInts(void)
{
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
    HAL_NVIC_EnableIRQ(SPI1_IRQn);
}

static void disableInts()
{
    HAL_NVIC_DisableIRQ(SPI1_IRQn);
    HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
}

// Attempt to start a SPI operation.
// This can be done from interrupt context or with interrupts disabled.
// If SPI periph is not in use and there is data to send or receive,
// this will start a SPI operation.
static void spiActivate(void)
{
    if ((spiState == SPI_IDLE) && (rxBufLen == 0))
    {
        if (rxReady)
        {
            // reset flag that was set with INTN
            rxReady = false;
            
            // assert CSN
            csn(false);

            if (txBufLen > 0)
            {
                spiState = SPI_WRITE;
                
                // Start operation to write (and, incidentally, read)
                HAL_SPI_TransmitReceive_DMA(&hspi1, txBuf, rxBuf, txBufLen);

                // Deassert Wake
                ps0_waken(true);
            }
            else
            {
                spiState = SPI_RD_HDR;
                
                // Start SPI operation to read header (writing zeros)
                HAL_SPI_TransmitReceive_DMA(&hspi1, (uint8_t *)txZeros, rxBuf, READ_LEN);
            }
        }
    }
}

// Handle the end of a SPI operation.
// This can be done from interrupt context or with interrupts disabled.
// Depending on spiState, it may start a follow-up operation or transition
// to idle.  In the latter case, it will call spiActivate
static void spiCompleted(void)
{
    // Get length of payload available
    uint16_t rxLen = (rxBuf[0] + (rxBuf[1] << 8)) & ~0x8000;
        
    // Truncate that to max len we can read
    if (rxLen > sizeof(rxBuf))
    {
        rxLen = sizeof(rxBuf);
    }

    if (spiState == SPI_DUMMY)
    {
        // SPI Dummy operation completed, transition now to idle
        spiState = SPI_IDLE;
    }
    else if (spiState == SPI_RD_HDR)
    {
        // We read a header

        if (rxLen > READ_LEN) {
            // There is more to read

            // Transition to RD_BODY state
            spiState = SPI_RD_BODY;
        
            // Start a read operation for the remaining length.  (We already read the first READ_LEN bytes.)
            HAL_SPI_TransmitReceive_DMA(&hspi1, (uint8_t *)txZeros, rxBuf+READ_LEN, rxLen-READ_LEN);
        }
        else
        {
            // No SHTP payload was received, this operation is done
            csn(true);            // deassert CSN
            rxBufLen = 0;         // no rx data available
            spiState = SPI_IDLE;  // back to idle state
            spiActivate();        // activate next operation, if any.
        }
    }
    else if (spiState == SPI_RD_BODY)
    {
        // We completed the read or write of a payload
        // deassert CSN.
        csn(true);

        // Check len of data read and set rxBufLen
        rxBufLen = rxLen;

        // transition back to idle state
        spiState = SPI_IDLE;

        // Activate the next operation, if any.
        spiActivate();
    }
    else if (spiState == SPI_WRITE)
    {
        // We completed the read or write of a payload
        // deassert CSN.
        csn(true);

        // Since operation was a write, transaction was for txBufLen bytes.  So received
        // data len is, at a maximum, txBufLen.
        rxBufLen = (txBufLen < rxLen) ? txBufLen : rxLen;

        // Tx buffer is empty now.
        txBufLen = 0;
        
        // transition back to idle state
        spiState = SPI_IDLE;

        // Activate the next operation, if any.
        spiActivate();
    }
}


// Interrupt handlers and SPI operation callbacks

void HAL_GPIO_EXTI_Callback(uint16_t n)
{
    rxTimestamp_us = timeNowUs();
    
    inReset = false;
    rxReady = true;
    checker++;
    // Start read, if possible
    spiActivate();
}

//void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef * hspi)
//{
//    static BaseType_t xHigherPriorityTaskWoken;
//    if (isOpen)
//    {
//    	spiCompleted();
//        if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED && 0) {
//        	xHigherPriorityTaskWoken = pdFALSE;
//        	vTaskNotifyGiveFromISR(imuTaskHandle, &xHigherPriorityTaskWoken);
//        	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
//        }
//        else
//        {
//        	sh2_service();
//        }
//    }
//}

void HAL_SPI_ErrorCallback(SPI_HandleTypeDef * hspi)
{
    // Shouldn't happen
    while (1);
}

void delayUs(uint32_t delay)
{
    volatile uint32_t now = timeNowUs();
    uint32_t start = now;
    while ((now - start) < delay) {
        now = timeNowUs();
    }
}

void resetDelayUs(uint32_t delay)
{
    volatile uint32_t now = timeNowUs();
    uint32_t start = now;
    while (((now - start) < delay) && (inReset))
    {
        now = timeNowUs();
    }
}

// ------------------------------------------------------------------------
// SH2 SPI Hal Methods
static void imuTask(void *pvParameters){
	for(;;) {
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        spiCompleted();
		sh2_service();
	}
}

static int sh2_spi_hal_open(sh2_Hal_t *self)
{
	osThreadDef(IMUTask, imuTask, 6, 0, 128*5);
	imuTaskHandle = osThreadCreate(osThread(IMUTask), NULL);

    int retval = SH2_OK;

    if (isOpen)
    {
        // Can't open if another instance is already open
        return SH2_ERR;
    }

    isOpen = true;

    // Init hardware (false -> non-DFU config)
    hal_init_hw(false);

    // Hold in reset
    rstn(false);

    // deassert CSN
    csn(true);

    // Clear rx, tx buffers
    rxBufLen = 0;
    txBufLen = 0;
    rxDataReady = false;
    rxReady = false;
    
    inReset = true;  // will change back to false when INTN serviced

    // Do dummy SPI operation
    // (First SPI op after reconfig has bad initial state of signals
    // so this is a throwaway operation.  Afterward, all is well.)
    spiState = SPI_DUMMY;
    spiDummyOp();
    spiState = SPI_IDLE;
    
    // Delay for RESET_DELAY_US to ensure reset takes effect
    delayUs(RESET_DELAY_US);
    
    // To boot in SHTP-SPI mode, must have PS1=1, PS0=1.
    // PS1 is set via jumper.
    // PS0 will be 1 PS1 jumper is 1 AND PS0_WAKEN sig is 1.
    // So we set PS0_WAKEN signal to 1
    ps0_waken(true);
    ps1(true);

    // Deassert reset, boot in non-DFU mode
    bootn(true);
    rstn(true);

    // enable interrupts
    enableInts();

    // Wait for INTN to be asserted
    resetDelayUs(START_DELAY_US);

    return retval;
}

static void sh2_spi_hal_close(sh2_Hal_t *self)
{
    // Disable interrupts
    disableInts();
    
    // Set state machine to INIT state
    spiState = SPI_INIT;
    
    // Hold sensor hub in reset
    rstn(false);
    
    // deassert CSN
    csn(true);

    // Deinit SPI peripheral
    HAL_SPI_DeInit(&hspi1);
    
    // No longer open
    isOpen = false;
}

static int sh2_spi_hal_read(sh2_Hal_t *self, uint8_t *pBuffer, unsigned len, uint32_t *t)
{
    int retval = 0;

    // If there is received data available...
    if (rxBufLen > 0)
    {
        // And if the data will fit in this buffer...
        if (len >= rxBufLen)
        {
            // Copy data to the client buffer
            memcpy(pBuffer, rxBuf, rxBufLen);
            retval = rxBufLen;

            // Set timestamp of that data
            *t = rxTimestamp_us;

            // Clear rxBuf so we can receive again
            rxBufLen = 0;
        }
        else
        {
            // Discard what was read and return error because buffer was too small.
            retval = SH2_ERR_BAD_PARAM;
            rxBufLen = 0;
        }
        
        // Now that rxBuf is empty, activate SPI processing to send any
        // potential write that was blocked.
        disableInts();
        spiActivate();
        enableInts();
    }

    return retval;
}

static int sh2_spi_hal_write(sh2_Hal_t *self, uint8_t *pBuffer, unsigned len)
{
    int retval = SH2_OK;

    // Validate parameters
    if ((self == 0) || (len > sizeof(txBuf)) ||
        ((len > 0) && (pBuffer == 0)))
    {
        return SH2_ERR_BAD_PARAM;
    }

    // If tx buffer is not empty, return 0
    if (txBufLen != 0)
    {
        return 0;
    }
    
    // Copy data to tx buffer
    memcpy(txBuf, pBuffer, len);
    txBufLen = len;
    retval = len;

    // disable SH2 interrupts for a moment
    disableInts();

    // Assert Wake
    ps0_waken(false);

    // re-enable SH2 interrupts.
    enableInts();

    return retval;
}

static uint32_t sh2_spi_hal_getTimeUs(sh2_Hal_t *self)
{
    return timeNowUs();
}


// ------------------------------------------------------------------------
// Public methods

sh2_Hal_t *sh2_hal_init(void)
{
    // Set up the HAL reference object for the client
    sh2Hal.open = sh2_spi_hal_open;
    sh2Hal.close = sh2_spi_hal_close;
    sh2Hal.read = sh2_spi_hal_read;
    sh2Hal.write = sh2_spi_hal_write;
    sh2Hal.getTimeUs = sh2_spi_hal_getTimeUs;

    return &sh2Hal;
}


    
