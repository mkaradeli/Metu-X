#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "common.h"
// #include "controller_parameters.h"
#include "pid.h"
#include <assert.h>

#define IMU_FREQ 400                   // hz
#define LIDAR_FREQ 1000                // hz
#define PRES_TRANS_FREQ 1000           // hz
#define ENCODER_FREQ 1000              // hz
#define BATTERY_VOLTAGE_FREQ 100       // hz
#define CONTROLLER_SCHEDULER_FREQ 2000 // hz

static_assert(CONTROLLER_SCHEDULER_FREQ % IMU_FREQ == 0);
static_assert(CONTROLLER_SCHEDULER_FREQ % LIDAR_FREQ == 0);
static_assert(CONTROLLER_SCHEDULER_FREQ % PRES_TRANS_FREQ == 0);
static_assert(CONTROLLER_SCHEDULER_FREQ % ENCODER_FREQ == 0);
static_assert(CONTROLLER_SCHEDULER_FREQ % BATTERY_VOLTAGE_FREQ == 0);

#define FRONT 0
#define REAR 1
#define LEFT 2
#define RIGHT 3

typedef struct {
  euler_s *euler; // in rad or deg
  double quaternion[4];

  double lidar; // in mm

  double manifoldPress;  // in kPa
  double nozzlePress[4]; // in kPa

  double encoder[4];      // as5600 in deg
  double battery_voltage; // in V

  long int clock; // in ns or clock cycles
} controller_input_s;

typedef void (*update_function_p)();

typedef struct {
  update_function_p updateIMU;
  update_function_p updateLidar;
  update_function_p updatePressureTransducers;
  update_function_p updateEncoder;
  update_function_p updateBatteryVoltage;
  int IMU_period;
  int Lidar_period;
  int PressureTranducers_period;
  int Encoder_period;
  int BatteryVoltage_period;
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

  point_s position_earth;
  point_s velocity_earth;
  point_s velocity_body;
  double height_command;
  euler_s attitude_command;
  euler_s euler;
  double thrust_command[4];
  double thrust_feedback[4];

  long int call_counter;
} controller_s;
void point_reset(point_s *point);
void euler_reset(euler_s *euler);
void controller_init(controller_s *controller);
void controller_iter(controller_s *controller);

void controller_sensors_init(controller_s *controller,
                             update_function_p updateIMU,
                             update_function_p updateLidar,
                             update_function_p updatePressureTransducers,
                             update_function_p updateEncoder,
                             update_function_p updateBatteryVoltage);

void controller_sensors_iter(controller_s *controller);
double CONOPS(double time);
#endif // !__CONTROLLER_H__
