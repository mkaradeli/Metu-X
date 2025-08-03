#ifndef __CONTROLLER_PARAMETERS_C__
#define __CONTROLLER_PARAMETERS_C__ 1

#include "pid.h"
#include <assert.h>

static const pid_parameters_s altitude_controller_parameters = {
    5,     // kP
    0,     // kI
    0,     // kD
    0,     // kFF
    0.001, // dT
    1e12,  // rateLimitMax
    -1e12, // rateLimitMin
    1,     // saturationMax
    0,     // saturationMin
    1,     // integralSaturationMax
    0,     // integralSaturationMin
    1,     // integralActiveBandMax
    0      // integralActiveBandMin
};

static const pid_parameters_s attitude_controller_parameters = {
    0,     // kP
    0,     // kI
    0,     // kD
    0,     // kFF
    0.001, // dT
    1e12,  // rateLimitMax
    -1e12, // rateLimitMin
    1,     // saturationMax
    0,     // saturationMin
    1,     // integralSaturationMax
    0,     // integralSaturationMin
    1,     // integralActiveBandMax
    0      // integralActiveBandMin
};

static const pid_parameters_s motor_controller_parameters = {
    50,     // kP
    0,      // kI
    0,      // kD
    0,      // kFF
    0.001,  // dT
    1e12,   // rateLimitMax
    -1e-12, // rateLimitMin
    24,     // saturationMax
    -24,    // saturationMin
    24,     // integralSaturationMax
    -24,    // integralSaturationMin
    0.1,    // integralActiveBandMax
    -0.1    // integralActiveBandMin
};

static const double conops_heigth[] = {0, 1, 2, 3, 4, 10};
static const double conops_velocity[] = {0.1, 1, 2, 3, 4, 10};
static const int conops_length = sizeof(conops_heigth) / sizeof(double);
static_assert(sizeof(conops_heigth) == sizeof(conops_velocity),
              "check conops velocity height map.");

#endif // !__CONTROLLER_PARAMETERS_C__
