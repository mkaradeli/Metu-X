/*
 * app.cpp
 *
 *  Created on: Aug 1, 2025
 *      Author: alica
 */
#include "app.hpp"
#include "adc.h"
#include "usart.h"
#include "tim.h"
#include "Lidar.hpp"
#include "Motor.hpp"
#include "cmsis_os.h"

#define USART2_RX_BUFFER_SIZE 64
uint8_t usart2_rx_buffer[USART2_RX_BUFFER_SIZE];
Lidar lidar;

uint16_t PSValues[5] = {0};

uint16_t EncoderValues[MAX_MOTOR_COUNT] = {0};
uint16_t PreviousEncoderValues[MAX_MOTOR_COUNT] = {0};
float MotorPositions[MAX_MOTOR_COUNT] = {0};
Motor Motors[MAX_MOTOR_COUNT] = {
		Motor(LEFT_EN_1_GPIO_Port, LEFT_EN_1_Pin, RIGHT_EN_1_GPIO_Port, RIGHT_EN_1_Pin, &htim4, TIM_CHANNEL_1),
		Motor(LEFT_EN_2_GPIO_Port, LEFT_EN_2_Pin, RIGHT_EN_2_GPIO_Port, RIGHT_EN_2_Pin, &htim4, TIM_CHANNEL_2),
		Motor(LEFT_EN_3_GPIO_Port, LEFT_EN_3_Pin, RIGHT_EN_3_GPIO_Port, RIGHT_EN_3_Pin, &htim4, TIM_CHANNEL_3),
		Motor(LEFT_EN_4_GPIO_Port, LEFT_EN_4_Pin, RIGHT_EN_4_GPIO_Port, RIGHT_EN_4_Pin, &htim4, TIM_CHANNEL_4)
};


uint32_t tm_flag = 0;
uint32_t interval = 0;

//Tasks
// Lidar Task
TaskHandle_t lidarTaskHandle = NULL;
void lidarTask(void *pvParameters){
	uint8_t Size = 0;
	for(;;) {
		xTaskNotifyWait(0x00, 0x00, (uint32_t *)&Size, portMAX_DELAY);
		lidar.FrameHandler(usart2_rx_buffer, Size);
	}
}
// Pressure Sensor Task
TaskHandle_t psTaskHandle = NULL;
void psTask(void *pvParameters){
	for(;;) {
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
	}
}
// Motor Position Task
TaskHandle_t mpTaskHandle = NULL;
void mpTask(void *pvParameters){
	for(;;) {
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		for (uint8_t i = 0; i < MAX_MOTOR_COUNT; i++){
			Motors[i].updatePosition(PreviousEncoderValues[i], EncoderValues[i]);
			PreviousEncoderValues[i] = EncoderValues[i];
		}
	}
}


void app_start(){
	xTaskCreate(
		    lidarTask,      	 // Task function
		    "Lidar Task",        // Name
		    128,                 // Stack size in words
		    NULL,                // Parameter to pass
		    9,					 // Priority
		    &lidarTaskHandle     // Handler
		);
	xTaskCreate(
		    psTask,      	 // Task function
		    "Pressure Sensor Task",        // Name
		    128,                 // Stack size in words
		    NULL,                // Parameter to pass
		    9,					 // Priority
		    &psTaskHandle     // Handler
		);
	xTaskCreate(
		    mpTask,      	 // Task function
		    "Motor Position Task",        // Name
		    128,                 // Stack size in words
		    NULL,                // Parameter to pass
		    9,					 // Priority
		    &mpTaskHandle     // Handler
		);

	HAL_TIM_Base_Start(&htim23);
	HAL_TIM_Base_Start(&htim6);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);

	HAL_ADCEx_Calibration_Start(&hadc1, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
	HAL_ADCEx_Calibration_Start(&hadc1, ADC_CALIB_OFFSET_LINEARITY, ADC_SINGLE_ENDED);

	HAL_ADCEx_Calibration_Start(&hadc2, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
	HAL_ADCEx_Calibration_Start(&hadc2, ADC_CALIB_OFFSET_LINEARITY, ADC_SINGLE_ENDED);

	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)PSValues, 5);
	HAL_ADC_Start_DMA(&hadc2, (uint32_t *)EncoderValues, 4);

	lidar.Reset();

	HAL_UARTEx_ReceiveToIdle_DMA(&huart2, usart2_rx_buffer, USART2_RX_BUFFER_SIZE);

	osKernelStart();

}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
    static BaseType_t xHigherPriorityTaskWoken;
	if (huart->Instance == USART2) {
		HAL_UARTEx_ReceiveToIdle_DMA(&huart2, usart2_rx_buffer, USART2_RX_BUFFER_SIZE);
		xHigherPriorityTaskWoken = pdFALSE;
		xTaskGenericNotifyFromISR(lidarTaskHandle, Size, eSetValueWithOverwrite, NULL, &xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	static BaseType_t  xHigherPriorityTaskWoken;
	if (hadc->Instance == ADC1){
		HAL_ADC_Start_DMA(hadc, (uint32_t *)PSValues, 5);
	    xHigherPriorityTaskWoken = pdFALSE;
	    vTaskNotifyGiveFromISR(psTaskHandle, &xHigherPriorityTaskWoken);
	    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
	if (hadc->Instance == ADC2){
		HAL_ADC_Start_DMA(hadc, (uint32_t *)EncoderValues, 4);
	    xHigherPriorityTaskWoken = pdFALSE;
	    vTaskNotifyGiveFromISR(mpTaskHandle, &xHigherPriorityTaskWoken);
	    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
}
