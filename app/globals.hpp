/*
 * globals.h
 *
 *  Created on: Aug 17, 2025
 *      Author: alica
 */

#ifndef GLOBALS_HPP_
#define GLOBALS_HPP_

#define MAX_MOTOR_COUNT 4
#define MAX_PS_COUNT 5

#include <stdint.h>

#include "Lidar.hpp"
#include "Motor.hpp"
#include "PressureSensor.hpp"
#include "sh2_SensorValue.h"

#include "cmsis_os.h"



// Message Pack
typedef struct {
    uint32_t timestamp;
    sh2_RotationVector_t quaternion;
    float motor_pos[4];
    float motor_duty[4];
    float pressure[5];
    float PressureDemand[4];
    float Velocity;
    float CurrentSetPoint;
    float eulerCalculated[3];
    float heightFiltered;
    uint16_t distance;
} SensorData_t;

typedef union {
    SensorData_t data;
    uint8_t bytes[sizeof(SensorData_t)];
} SensorDataUnion_t;

extern SensorDataUnion_t txData;

// Lidar Variables
extern TaskHandle_t lidarTaskHandle;
extern Lidar lidar;

// Pressure Sensor Variables
extern TaskHandle_t psTaskHandle;
extern uint16_t PSValues[MAX_PS_COUNT];
extern PressureSensor psSensors[MAX_PS_COUNT];

// Motor Variables
extern TaskHandle_t motorTaskHandle;
extern uint16_t EncoderValues[MAX_MOTOR_COUNT];
extern Motor motors[MAX_MOTOR_COUNT];

// SD Card Varibles
extern TaskHandle_t sdCardTaskHandle;

const float sineLookupTable[] = { 0.0, 0.4, 0.0, -0.4, 0.0
};

#endif /* GLOBALS_HPP_ */
