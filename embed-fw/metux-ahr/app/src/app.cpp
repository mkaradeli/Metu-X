/*
 * app.cpp
 *
 *  Created on: Aug 1, 2025
 *      Author: alica
 */
#include "app.hpp"
#include "usart.h"
#include "tim.h"
#include "Lidar.hpp"

#define USART2_RX_BUFFER_SIZE 64
uint8_t usart2_rx_buffer[USART2_RX_BUFFER_SIZE];
Lidar lidar;

void app_start(){
	HAL_TIM_Base_Start(&htim23);
	HAL_UARTEx_ReceiveToIdle_DMA(&huart2, usart2_rx_buffer, USART2_RX_BUFFER_SIZE);
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
	if (huart->Instance == USART2) {
	  	lidar.FrameHandler(usart2_rx_buffer, Size);
		HAL_UARTEx_ReceiveToIdle_DMA(&huart2, usart2_rx_buffer, USART2_RX_BUFFER_SIZE);
	}
}
