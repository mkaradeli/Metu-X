/*
 * Lidar.cpp
 *
 *  Created on: Aug 1, 2025
 *      Author: alica
 */
#include "Lidar.hpp"
#include "tim.h"
#include "usart.h"

Lidar::Lidar(){

}

void Lidar::FrameHandler(uint8_t* frame, uint8_t size){
    if (size != LIDAR_FRAME_SIZE){
        this->status = false;
        return; // Invalid frame size
    }
    if (frame[0] != LIDAR_FRAME_HEADER && frame[1] != LIDAR_FRAME_HEADER){
        this->status = false;
        return; // Invalid frame header
    }
    for (uint8_t i = 0; i < (LIDAR_FRAME_SIZE - 1); i++){
        this->checksum += frame[i];
    }
    if (this->checksum != frame[LIDAR_FRAME_SIZE - 1]){
        this->status = false;
        return; // Checksum mismatch
    }
    this->checksum = 0;

    this->interval_us = micros() - this->flag_us;
    this->flag_us = micros();

    this->distance = frame[2] | (frame[3] << 8);
    this->strength = frame[4] | (frame[5] << 8);
    this->temperature = frame[6] | (frame[7] << 8);

}

void Lidar::SaveConfig(){
	uint8_t command[] = {
			0x5A, 0x04, 0x11, 0x6F
	};
	HAL_UART_Transmit(&huart2, command, sizeof(command), 1000);
}

void Lidar::SetFrameRate(uint16_t rate){
	if (rate > 1000 && rate < 1){
		return;
	}
	uint8_t command[] = {
			0x5A, 0x06, 0x03, rate, (rate >> 8), 0x00
	};
	for (uint8_t i = 0; i < (sizeof(command)-1); i++){
		command[sizeof(command)-1] += command[i];
	}
	HAL_UART_Transmit(&huart2, command, sizeof(command), 1000);
}

void Lidar::Reset(){
	uint8_t command[] = {
			0x5A, 0x04, 0x02, 0x60
	};
	uint8_t buffer[15] = {0};
	HAL_UART_Transmit(&huart2, command, sizeof(command), 1000);
	HAL_UART_Receive(&huart2, buffer, 5, 10000);
}

