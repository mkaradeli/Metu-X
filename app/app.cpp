  /*
 * app.cpp
 *
 *  Created on: Aug 7, 2025
 *      Author: alica
 */

#include "globals.hpp"
#include "globals.h"
#include "app.h"

#include "adc.h"
#include "usart.h"
#include "spi.h"

#include "string.h"
#include "stdio.h"


#define PACKET_SIZE 114
#define BUFFER_PACKETS 512
#define BUFFER_SIZE (PACKET_SIZE * BUFFER_PACKETS)

uint8_t bufferA[BUFFER_SIZE];
uint8_t bufferB[BUFFER_SIZE];
uint8_t *activeBuffer = bufferA;
uint8_t *writeBuffer = NULL;
uint32_t bufferIndex = 0;
bool lastWrite = false;
SemaphoreHandle_t writeSemaphore;

uint8_t myrxBuffer[5];
TaskHandle_t dischargeTaskHandle;

uint8_t lidar_counter = 0;

typedef struct {
    float x;
    float y;
    float z;
} Force_t;

Force_t force_measurement = {0, 0, 0};

uint8_t counter = 0;
uint8_t mc = 0;
uint16_t sinCounter = 0;
bool controllerStarted = false;

TaskHandle_t controlTaskHandle;
TaskHandle_t bufferDataTaskHandle;
TaskHandle_t safetyConnectorTaskHandle;

void lidarTask(void *pvParameters){
	uint8_t Size = 0;
	for(;;) {
		xTaskNotifyWait(0x00, 0x00, (uint32_t *)&Size, portMAX_DELAY);
		lidar.FrameHandler(Size);
	}
}

void motorTask(void *pvParameters){
	for(;;){
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		for (uint8_t i = 0; i < MAX_MOTOR_COUNT; i++)
			motors[i].updatePosition(EncoderValues[i]);
	}
}

void psTask(void *pvParameters){
	for(;;){
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		for (uint8_t i = 0; i < MAX_PS_COUNT; i++)
			psSensors[i].updatePS(PSValues[i]);
		force_measurement.x = PSValues[2]/65535.0*3300.0/5000.0*750.0 + 0.5;
		force_measurement.y = PSValues[4]/65535.0*3300.0/5000.0*750.0 + 0.5;
	}
}

void sdCardTask(void *pvParameters){
	osDelay(5000);
	sd_mount();
	sd_create_log_file();
	ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
	for(;;){
        if (xSemaphoreTake(writeSemaphore, portMAX_DELAY) == pdTRUE) {
            // Write full buffer to SD
    		sd_write_log_file(writeBuffer, bufferIndex > 0 ? bufferIndex : BUFFER_SIZE);
            writeBuffer = NULL;
            if (lastWrite){
            	sd_close_log_file();
            	osThreadTerminate(NULL);
            }
        }

	}
}

void bufferDataTask(void *pvParameters){
	osDelay(5000);
	ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
	uint32_t flag = micros();
	for(;;){
		osDelay(1);
		if ((micros()-flag) < 10000000){
			txData.data.timestamp = micros();
			txData.data.distance = lidar.getDistance();
			for(uint8_t i = 0; i < MAX_MOTOR_COUNT; i++){
				txData.data.motor_pos[i] = motors[i].getPositionDegree();
				txData.data.motor_duty[i] = motors[i].getDutyCycle();
			}

			for(uint8_t i = 0; i < MAX_PS_COUNT; i++)
				txData.data.pressure[i] = psSensors[i].getBar();
			txData.data.quaternion = quaternion;
			txData.data.CurrentSetPoint = metux_model_6dof_only_control_Y.currentsetpoint;
			txData.data.PressureDemand[0] = force_measurement.x;
			txData.data.PressureDemand[1] = force_measurement.y;
			txData.data.PressureDemand[2] = metux_model_6dof_only_control_Y.PressureDemand[2];
			txData.data.PressureDemand[3] = metux_model_6dof_only_control_Y.PressureDemand[3];
			txData.data.Velocity = metux_model_6dof_only_control_Y.VelocityMeasured;
			txData.data.heightFiltered = metux_model_6dof_only_control_Y.height_filtered;
			txData.data.eulerCalculated[0] = metux_model_6dof_only_control_Y.eulercalculated[0];
			txData.data.eulerCalculated[1] = metux_model_6dof_only_control_Y.eulercalculated[1];
			txData.data.eulerCalculated[2] = metux_model_6dof_only_control_Y.eulercalculated[2];

		    memcpy(&activeBuffer[bufferIndex], txData.bytes, PACKET_SIZE);
		    bufferIndex += PACKET_SIZE;

		    if (bufferIndex >= BUFFER_SIZE) {
		        // Prepare buffer for writing
		        writeBuffer = activeBuffer;

		        // Swap active buffer
		        activeBuffer = (activeBuffer == bufferA) ? bufferB : bufferA;
		        bufferIndex = 0;
		        xSemaphoreGive(writeSemaphore);
		    }
		}
		else {
	        writeBuffer = activeBuffer;
	        lastWrite = true;
	        xSemaphoreGive(writeSemaphore);
		}
	}
}

void controllerTask(void *pvParameters){
	metux_model_6dof_only_controller_initialize();
	osDelay(5000);
	metux_model_6dof_only_control_U.Activate = 0;
	metux_model_6dof_only_control_U.ESTOP = 0;
	metux_model_6dof_only_control_U.ControllerMode = 1;
	ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
	metux_model_6dof_only_control_U.PositionDemand = 1300.0;
	controllerStarted = true;
	for(uint8_t i = 0; i < 4; i++){
		motors[i].setPositionDegree(0*360.0);
	}
	uint32_t flag = micros();
	for(;;){
		osDelay(1);
		metux_model_6dof_only_control_U.Activate = 1;
		metux_model_6dof_only_control_U.N1pressure = psSensors[0].getBar();
		metux_model_6dof_only_control_U.N2pressure = psSensors[1].getBar();
		metux_model_6dof_only_control_U.N3pressure = psSensors[2].getBar();
		metux_model_6dof_only_control_U.N4pressure = psSensors[3].getBar();
		metux_model_6dof_only_control_U.manifoldpressure = psSensors[4].getBar();
		metux_model_6dof_only_control_U.Time = micros()/1000;
		metux_model_6dof_only_control_U.RightMotorAngle = motors[0].getPositionDegree();
		metux_model_6dof_only_control_U.FrontMotorAngle = motors[1].getPositionDegree();
		metux_model_6dof_only_control_U.LeftMotorAngle = motors[2].getPositionDegree();
		metux_model_6dof_only_control_U.BackMotorAngle = motors[3].getPositionDegree();
		metux_model_6dof_only_control_U.height_measured = lidar.getDistance();
		metux_model_6dof_only_control_U.quaternion[0] = force_measurement.x;
		metux_model_6dof_only_control_U.quaternion[1] = force_measurement.y;
		metux_model_6dof_only_control_U.quaternion[2] = 0;;
		metux_model_6dof_only_control_U.quaternion[3] = 0;
		metux_model_6dof_only_controller_step();
		motors[0].setSpeed(metux_model_6dof_only_control_Y.RightDuty);
		motors[1].setSpeed(metux_model_6dof_only_control_Y.FrontDuty);
		motors[2].setSpeed(metux_model_6dof_only_control_Y.LeftDuty);
		motors[3].setSpeed(metux_model_6dof_only_control_Y.BackDuty);
		if ((micros() - flag) > 1000000)
			metux_model_6dof_only_control_U.PositionDemand = 1450 - ((micros()-flag-1000000.0)/1000000.0f * 470.0);
		else if (motors[1].getPositionDegree() < 1400.0)
			motors[1].setSpeed(1.0);
		if (metux_model_6dof_only_control_U.PositionDemand < 100)
			metux_model_6dof_only_control_U.PositionDemand = 50;
	}
}


void safetyConnectorTask(void *pvParameters){
	osDelay(5000);
	for(;;){
		osDelay(1);
		while (HAL_GPIO_ReadPin(SAFETY_GPIO_Port, SAFETY_Pin)){
			counter++;
			if (counter > 50)
				break;
		}
		if (counter > 50){
			xTaskNotifyGive(bufferDataTaskHandle);
			xTaskNotifyGive(sdCardTaskHandle);
			xTaskNotifyGive(controlTaskHandle);
			osThreadTerminate(NULL);
		}
	}
}

void dischargeTask(void *pvParameters){
	ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
	osThreadTerminate(controlTaskHandle);
	osThreadTerminate(bufferDataTaskHandle);
	osThreadTerminate(sdCardTaskHandle);
	for(;;){
		printf("Tahliye Başlatılıyor...\n");
		osDelay(1000);
		uint32_t flag = micros();
		motors[0].setSpeed(0.65);
		motors[1].setSpeed(0.65);
		motors[2].setSpeed(0.65);
		motors[3].setSpeed(0.65);
		while((micros()-flag) < 50000);
		motors[0].setSpeed(0);
		motors[1].setSpeed(0);
		motors[2].setSpeed(0);
		motors[3].setSpeed(0);
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
	}
}

void app_start(){
	HAL_UART_Receive_DMA(&huart1, myrxBuffer, 5);

	IMU_Init();

    writeSemaphore = xSemaphoreCreateBinary();

	xTaskCreate(lidarTask, "Lidar Task", 128, NULL, 6, &lidarTaskHandle);
	xTaskCreate(motorTask, "Motor Task", 128, NULL, 5, &motorTaskHandle);
	xTaskCreate(psTask, "PS Task", 128, NULL, 5, &psTaskHandle);
	xTaskCreate(bufferDataTask, "Buffer Data", 128, NULL, 5, &bufferDataTaskHandle);
	xTaskCreate(sdCardTask, "PS Task", 128*5, NULL, 5, &sdCardTaskHandle);
	xTaskCreate(dischargeTask, "Discharge Task", 128, NULL, 6, &dischargeTaskHandle);


	lidar.Reset();

	HAL_UARTEx_ReceiveToIdle_DMA(&huart2, lidar.getBuffer(), 128);


	HAL_ADCEx_Calibration_Start(&hadc1, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
	//HAL_ADCEx_Calibration_Start(&hadc1, ADC_CALIB_OFFSET_LINEARITY, ADC_SINGLE_ENDED);

	HAL_ADCEx_Calibration_Start(&hadc2, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
	//HAL_ADCEx_Calibration_Start(&hadc2, ADC_CALIB_OFFSET_LINEARITY, ADC_SINGLE_ENDED);

	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)PSValues, 5);
	HAL_ADC_Start_DMA(&hadc2, (uint32_t *)EncoderValues, 4);

	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
	HAL_TIM_Base_Start_IT(&htim13);

	xTaskCreate(controllerTask, "Control Task", 128*30, NULL, 5, &controlTaskHandle);
	xTaskCreate(safetyConnectorTask, "Safety Connector", 128, NULL, 6, &safetyConnectorTaskHandle);

	for(uint8_t i = 0; i < 4; i++){
		motors[i].setPositionDegree(0*360.0);
	}


}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
    static BaseType_t xHigherPriorityTaskWoken;
	if (huart->Instance == USART2){
		HAL_UARTEx_ReceiveToIdle_DMA(&huart2, lidar.getBuffer(), 128);
		xHigherPriorityTaskWoken = pdFALSE;
		xTaskGenericNotifyFromISR(lidarTaskHandle, Size, eSetValueWithOverwrite, NULL, &xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    static BaseType_t xHigherPriorityTaskWoken;
    if (huart->Instance == USART1)
    {
		xHigherPriorityTaskWoken = pdFALSE;
		vTaskNotifyGiveFromISR(dischargeTaskHandle, &xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
    	HAL_UART_Receive_DMA(&huart1, myrxBuffer, 5);
    }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	static BaseType_t xHigherPriorityTaskWoken;
	if (hadc->Instance == ADC1){
		HAL_ADC_Start_DMA(&hadc1, (uint32_t *)PSValues, MAX_PS_COUNT);
		xHigherPriorityTaskWoken = pdFALSE;
		vTaskNotifyGiveFromISR(psTaskHandle, &xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
	}
	else if (hadc->Instance == ADC2) {
		HAL_ADC_Start_DMA(&hadc2, (uint32_t *)EncoderValues, MAX_MOTOR_COUNT);
		xHigherPriorityTaskWoken = pdFALSE;
		vTaskNotifyGiveFromISR(motorTaskHandle, &xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

	}
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi) {
	static BaseType_t xHigherPriorityTaskWoken;
	if (hspi == &SD_SPI_HANDLE){
		xHigherPriorityTaskWoken = pdFALSE;
		vTaskNotifyGiveFromISR(sdCardTaskHandle, &xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
	}
	if (hspi == &hspi1){
		xHigherPriorityTaskWoken = pdFALSE;
		vTaskNotifyGiveFromISR(imuTaskHandle, &xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi) {
	static BaseType_t xHigherPriorityTaskWoken;
	if (hspi == &SD_SPI_HANDLE) {
		xHigherPriorityTaskWoken = pdFALSE;
		vTaskNotifyGiveFromISR(sdCardTaskHandle, &xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
	}
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */
  if (htim->Instance == TIM13) {
	  if (controllerStarted){
		  for (mc = 0; mc < 4; mc++){
			  //motors[mc].setSpeed(motors[mc].getDutyCycle() + sineLookupTable[sinCounter]);
		  }
		  sinCounter++;
		  if (sinCounter == 5)
			  sinCounter = 0;
	  }
  }
  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM17)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}
