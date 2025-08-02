#include "controller.h"
#include "controller_parameters.h"

void point_reset(point_s *point) {
  point->x = 0;
  point->y = 0;
  point->z = 0;
}

void euler_reset(euler_s *point) {
  point->roll = 0;
  point->pitch = 0;
  point->yaw = 0;
}

void controller_init(controller_s *controller) {
  // init inputs
  for (int i = 0; i < 4; i++)
    controller->input.quaternion[i] = 0;
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

  // init intermediary values
  point_reset(&controller->position_earth);
  point_reset(&controller->velocity_earth);
  point_reset(&controller->velocity_body);
  euler_reset(&controller->attitude_command);
  euler_reset(&controller->euler);
  for (int i = 0; i < 4; i++) {
    controller->thrust_command[i] = 0;
  }
  controller->call_counter = 0;

  // init pid controllers
  // TODO: pid controlculeri eklenecek ve birbirlerine baglanacak.
  pid_controller_init(&controller->altitude_controller, &altitude_controller,
                      &controller->height_command,
                      &controller->position_earth.z);
  pid_controller_init(&controller->pitch_controller, &attitude_controller,
                      &controller->attitude_command.pitch,
                      &controller->euler.pitch);
  pid_controller_init(&controller->roll_controller, &attitude_controller,
                      &controller->attitude_command.roll,
                      &controller->euler.roll);

  for (int i = 0; i < 4; i++) {
    pid_controller_init(&controller->motor_controller[i], &motor_controller,
                        &controller->thrust_command[i],
                        &controller->thrust_feedback[i]);
  }
}

void controller_sensors_init(controller_s *controller,
                             update_function_p updateIMU,
                             update_function_p updateLidar,
                             update_function_p updatePressureTransducers,
                             update_function_p updateEncoder,
                             update_function_p updateBatteryVoltage) {

  // sensor outputs.
  // set sensor function pointers that will update the controller inputs.

  controller->sensor_update.updateIMU = updateIMU;
  controller->sensor_update.updateLidar = updateLidar;
  controller->sensor_update.updatePressureTransducers =
      updatePressureTransducers;
  controller->sensor_update.updateEncoder = updateEncoder;
  controller->sensor_update.updateBatteryVoltage = updateBatteryVoltage;

  controller->sensor_update.IMU_period = CONTROLLER_SCHEDULER_FREQ / IMU_FREQ;
  controller->sensor_update.Lidar_period =
      CONTROLLER_SCHEDULER_FREQ / LIDAR_FREQ;
  controller->sensor_update.PressureTranducers_period =
      CONTROLLER_SCHEDULER_FREQ / PRES_TRANS_FREQ;
  controller->sensor_update.Encoder_period =
      CONTROLLER_SCHEDULER_FREQ / ENCODER_FREQ;
  controller->sensor_update.BatteryVoltage_period =
      CONTROLLER_SCHEDULER_FREQ / BATTERY_VOLTAGE_FREQ;
}

void controller_sensors_iter(controller_s *controller) {
  // TODO:  add updates
  if (0 == controller->call_counter % controller->sensor_update.IMU_period)
    controller->sensor_update.updateIMU();
  if (0 == controller->call_counter % controller->sensor_update.Lidar_period)
    controller->sensor_update.updateLidar();
  if (0 == controller->call_counter %
               controller->sensor_update.PressureTranducers_period)
    controller->sensor_update.updatePressureTransducers();
  if (0 == controller->call_counter % controller->sensor_update.Encoder_period)
    controller->sensor_update.updateEncoder();
  if (0 == controller->call_counter %
               controller->sensor_update.BatteryVoltage_period)
    controller->sensor_update.updateBatteryVoltage();
}

void controller_iter(controller_s *controller) {
  controller->call_counter += 1;

  controller_sensors_iter(controller);
  controller->height_command = CONOPS(controller->input.clock);

  pid_controller_iterate(&controller->altitude_controller);
  pid_controller_iterate(&controller->pitch_controller);
  pid_controller_iterate(&controller->roll_controller);

  controller->thrust_command[FRONT] =
      controller->altitude_controller.y + controller->pitch_controller.y;
  controller->thrust_command[REAR] =
      controller->altitude_controller.y - controller->pitch_controller.y;
  controller->thrust_command[LEFT] =
      controller->altitude_controller.y + controller->roll_controller.y;
  controller->thrust_command[RIGHT] =
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

double CONOPS(double time) {
  // TODO: CONOPS EKLENECECK
  return 1.0f;
}
