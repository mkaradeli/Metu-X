/*
 * Lidar.cpp
 *
 *  Created on: Aug 1, 2025
 *      Author: alica
 */
#include "Lidar.hpp"
#include "tim.h"

Lidar::Lidar(){

}

void Lidar::FrameHandler(uint8_t* frame, uint8_t size){
    static uint8_t checksum = 0;
    if (size != LIDAR_FRAME_SIZE){
        this->status = false;
        return; // Invalid frame size
    }
    if (frame[0] != LIDAR_FRAME_HEADER && frame[1] != LIDAR_FRAME_HEADER){
        this->status = false;
        return; // Invalid frame header
    }
    for (uint8_t i = 0; i < (LIDAR_FRAME_SIZE - 1); i++){
        checksum += frame[i];
    }
    if (checksum != frame[LIDAR_FRAME_SIZE - 1]){
        this->status = false;
        return; // Checksum mismatch
    }
    checksum = 0;

    this->interval_us = micros() - this->flag_us;
    this->flag_us = micros();

    this->distance = frame[2] | (frame[3] << 8);
    this->strength = frame[4] | (frame[5] << 8);
    this->temperature = frame[6] | (frame[7] << 8);
}
