#include "pid.h"

#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#define IMU_FREQ 400                   // hz
#define LIDAR_FREQ 1000                // hz
#define PRES_TRANS_FREQ 1000           // hz
#define ENCODER_FREQ 1000              // hz
#define VOLTAGE_MEAS_FREQ 100          // hz
#define CONTROLLER_SCHEDULER_FREQ 2000 // hz

typedef struct {
  double euler[3]; // in rad or deg
  double quaternion[4];

  double lidar; // in mm

  double manifoldPress;  // in kPa
  double nozzlePress[4]; // in kPa

  double encoder[4];      // as5600 in deg
  double battery_voltage; // in V

  long int clock; // in ns or clock cycles
} controller_input_s;

typedef void (*update_function_p)(controller_input_s *);
typedef struct {
  update_function_p updateIMU;
  update_function_p updateLidar;
  update_function_p updatePressureTransducers;
  update_function_p updateEncoder;
  update_function_p updateBatteryVoltage;
} sensor_updates_functions_s;

typedef struct {
  double motor_voltage[4]; // in volts
  double motor_pwm[4];     // normalized, from -1 to 1

} controller_output_s;

typedef struct {
  controller_input_s input;
  controller_output_s outputs;
  sensor_updates_functions_s sensor_update;

  pid_parameters_s altitude_control_parameters;
  pid_parameters_s attitude_control_parameters;
  pid_parameters_s motor_control_parameters;

  pid_controller_s altitude_controller;
  pid_controller_s pitch_controller;
  pid_controller_s roll_controller;
  pid_controller_s motor_controller[4];

} controller_s;

void controller_init(controller_s *controller, update_function_p updateIMU,
                     update_function_p updateLidar,
                     update_function_p updatePressureTransducers,
                     update_function_p updateEncoder,
                     update_function_p updateBatteryVoltage);
void controller_iter(controller_s *controller);

#endif
