#include "pid.h"

#ifndef __CONTROLLER_PARAMETERS_C__
#define __CONTROLLER_PARAMETERS_C__

pid_parameters_s altitude_controller = {
    1,  // kP
    2,  // kI
    3,  // kD
    4,  // kFF
    5,  // dT
    6,  // rateLimitMax
    7,  // rateLimitMin
    8,  // saturationMax
    9,  // saturationMin
    10, // integralSaturationMax
    11  // integralSaturationMin
};

pid_parameters_s attitude_controller = {
    1,  // kP
    2,  // kI
    3,  // kD
    4,  // kFF
    5,  // dT
    6,  // rateLimitMax
    7,  // rateLimitMin
    8,  // saturationMax
    9,  // saturationMin
    10, // integralSaturationMax
    11  // integralSaturationMin
};

pid_parameters_s motor_controller = {
    1,  // kP
    2,  // kI
    3,  // kD
    4,  // kFF
    5,  // dT
    6,  // rateLimitMax
    7,  // rateLimitMin
    8,  // saturationMax
    9,  // saturationMin
    10, // integralSaturationMax
    11  // integralSaturationMin
};

#endif // !__CONTROLLER_PARAMETERS_C__
