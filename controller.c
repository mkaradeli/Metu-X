#include "controller.h"
#include "controller_parameters.h"
#include "filter.h"
#include "lookup.h"
#include <math.h>

void point_reset(point_s *point) {
  point->x = 0;
  point->y = 0;
  point->z = 0;
}

void euler_reset(euler_s *euler) {
  euler->roll = 0;
  euler->pitch = 0;
  euler->yaw = 0;
}

void controller_init(controller_s *controller) {
  // init inputs
  euler_reset(&controller->input.euler);
  controller->input.lidar = 0;
  controller->input.manifoldPress = 0;
  for (int i = 0; i < 4; i++) {
    controller->input.nozzlePress[i] = 0;
    controller->input.encoder[i] = 0;
  }
  controller->input.battery_voltage = 0;
  controller->input.clock = 0;

  // init outputs
  for (int i = 0; i < 4; i++) {
    controller->outputs.motor_voltage[i] = 0;
    controller->outputs.motor_pwm[i] = 0;
  }

  // reset referances
  euler_reset(&controller->refs.attitude);
  point_reset(&controller->refs.velocity);
  for (int i = 0; i < 4; i++) {
    controller->refs.thrust[i] = 0;
  }

  // reset feedbacks
  euler_reset(&controller->fdbs.attitude);
  point_reset(&controller->fdbs.position_e);
  point_reset(&controller->fdbs.velocity_b);
  point_reset(&controller->fdbs.velocity_e);
  for (int i = 0; i < 4; i++) {
    controller->fdbs.thrust[i] = 0;
  }

  controller->call_counter = 0;

  // init pid controllers
  controller->altitude_control_parameters = altitude_controller_parameters;
  controller->attitude_control_parameters = attitude_controller_parameters;
  controller->motor_control_parameters = motor_controller_parameters;

  // TODO: pid controlculeri eklenecek ve birbirlerine baglanacak.
  pid_controller_init(&controller->altitude_controller,
                      &controller->altitude_control_parameters,
                      &controller->refs.velocity.z,
                      &controller->fdbs.velocity_e.z);
  pid_controller_init(
      &controller->pitch_controller, &controller->altitude_control_parameters,
      &controller->refs.attitude.pitch, &controller->fdbs.attitude.pitch);
  pid_controller_init(
      &controller->roll_controller, &controller->attitude_control_parameters,
      &controller->refs.attitude.roll, &controller->fdbs.attitude.roll);

  for (int i = 0; i < 4; i++) {
    pid_controller_init(
        &controller->motor_controller[i], &motor_controller_parameters,
        &controller->refs.thrust[i], &controller->fdbs.thrust[i]);
  }

  lookup_init(&controller->velocity_command_map, conops_heigth, conops_velocity,
              conops_length);

  ema_filter_init(&controller->velocity_feedback_filter,
                  &controller->fdbs.position_e.z, 0.1);
}

void controller_iter(controller_s *controller) {
  controller->call_counter += 1;

  controller_update_feedbacks(controller);

  pid_controller_iterate(&controller->altitude_controller);
  pid_controller_iterate(&controller->pitch_controller);
  pid_controller_iterate(&controller->roll_controller);

  controller->refs.thrust[FRONT] =
      controller->altitude_controller.y + controller->pitch_controller.y;
  controller->refs.thrust[REAR] =
      controller->altitude_controller.y - controller->pitch_controller.y;
  controller->refs.thrust[LEFT] =
      controller->altitude_controller.y + controller->roll_controller.y;
  controller->refs.thrust[RIGHT] =
      controller->altitude_controller.y - controller->roll_controller.y;

  pid_controller_iterate(&controller->motor_controller[FRONT]);
  pid_controller_iterate(&controller->motor_controller[REAR]);
  pid_controller_iterate(&controller->motor_controller[LEFT]);
  pid_controller_iterate(&controller->motor_controller[RIGHT]);

  controller->outputs.motor_pwm[FRONT] = controller->motor_controller[FRONT].y;
  controller->outputs.motor_pwm[REAR] = controller->motor_controller[REAR].y;
  controller->outputs.motor_pwm[LEFT] = controller->motor_controller[LEFT].y;
  controller->outputs.motor_pwm[RIGHT] = controller->motor_controller[RIGHT].y;

  controller->outputs.motor_voltage[FRONT] =
      24 * controller->outputs.motor_pwm[FRONT];
  controller->outputs.motor_voltage[REAR] =
      24 * controller->outputs.motor_pwm[REAR];
  controller->outputs.motor_voltage[LEFT] =
      24 * controller->outputs.motor_pwm[LEFT];
  controller->outputs.motor_voltage[RIGHT] =
      24 * controller->outputs.motor_pwm[RIGHT];
}

void conops_init(controller_s *controller) {
  // TODO: CONOPS EKLENECECK
  lookup_init(&controller->velocity_command_map, conops_heigth, conops_velocity,
              conops_length);
}
void conops_iter(controller_s *controller) {
  lookup_iter(&controller->velocity_command_map, controller->fdbs.position_e.z);
  controller->refs.velocity.z = controller->velocity_command_map.y;
}

void controller_update_feedbacks(controller_s *controller) {
  controller->fdbs.attitude = controller->input.euler;
  controller->fdbs.position_e.z = controller->input.lidar *
                                  cos(controller->fdbs.attitude.pitch) *
                                  cos(controller->fdbs.attitude.roll);
  lookup_iter(&controller->velocity_command_map, controller->fdbs.position_e.z);
  controller->refs.velocity.z = controller->velocity_command_map.y;

  // TODO: VELOCITY FEEDBACK NEEDS TO BE CALCULATED.
  //
  ema_filter_iter(&controller->velocity_feedback_filter);
  controller->fdbs.velocity_e.z = controller->velocity_feedback_filter.y;
}
