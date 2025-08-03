#include "filter.h"
#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__ 1

#include "common.h"
#include "controller_parameters.h"
#include "lookup.h"
#include "pid.h"
#include <assert.h>

#define IMU_FREQ 250                   // hz
#define LIDAR_FREQ 1000                // hz
#define PRES_TRANS_FREQ 1000           // hz
#define ENCODER_FREQ 1000              // hz
#define BATTERY_VOLTAGE_FREQ 100       // hz
#define CONTROLLER_SCHEDULER_FREQ 1000 // hz

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
  euler_s euler; // in rad or deg
  long int update_euler;

  double lidar; // in mm
  long int updated_lidar;

  double manifoldPress;  // in kPa
  double nozzlePress[4]; // in kPa
  long int updated_transducers;

  double encoder[4]; // as5600 in deg
  long int updated_encoder;

  double battery_voltage; // in V
  long int updated_battery_voltage;

  long int clock; // in us or clock cycles
} controller_input_s;

typedef struct {
  double motor_voltage[4]; // in volts
  double motor_pwm[4];     // normalized, from -1 to 1

} controller_output_s;

typedef struct {
  euler_s attitude;
  point_s velocity;
  double thrust[4];
} controller_references_s;

typedef struct {
  euler_s attitude;
  point_s position_e;
  point_s velocity_e;
  point_s velocity_b;
  double thrust[4];
} controller_feedbacks_s;

typedef struct {
  controller_input_s input;
  controller_output_s outputs;
  controller_references_s refs;
  controller_feedbacks_s fdbs;
  lookup_s velocity_command_map;
  ema_filter_s velocity_feedback_filter;

  pid_parameters_s altitude_control_parameters;
  pid_parameters_s attitude_control_parameters;
  pid_parameters_s motor_control_parameters;

  pid_controller_s altitude_controller;
  pid_controller_s pitch_controller;
  pid_controller_s roll_controller;
  pid_controller_s motor_controller[4];

  long int call_counter;
} controller_s;
void point_reset(point_s *point);
void euler_reset(euler_s *euler);
void controller_init(controller_s *controller);
void controller_iter(controller_s *controller);
void controller_update_feedbacks(controller_s *controller);

void conops_init(controller_s *controller);
void conops_iter(controller_s *controller);
#endif // !__CONTROLLER_H__
