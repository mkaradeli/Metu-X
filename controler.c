#include "controller.h"
#include "controller_parameters.c"
#include "filter.h"
#include "pid.h"

void controller_init(controller_s *controller, update_function_p updateIMU,
                     update_function_p updateLidar,
                     update_function_p updatePressureTransducers,
                     update_function_p updateEncoder,
                     update_function_p updateBatteryVoltage) {
  // init inputs
  for (int i = 0; i < 3; i++)
    controller->input.euler[i] = 0;
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
  for (int i; i < 4; i++) {
    controller->outputs.motor_voltage[i] = 0;
    controller->outputs.motor_pwm[i] = 0;
  }

  // sensor outputs.
  // set sensor function pointers that will update the controller inputs.
  controller->sensor_update.updateIMU = updateIMU;
  controller->sensor_update.updateLidar = updateLidar;
  controller->sensor_update.updatePressureTransducers =
      updatePressureTransducers;
  controller->sensor_update.updateEncoder = updateEncoder;
  controller->sensor_update.updateBatteryVoltage = updateBatteryVoltage;

  // init pid controllers
  // TODO: pid controlculeri eklenecek ve birbirlerine baglanacak.
}

void controller_iter(controller_s *controller) {
  // TODO: Controlcu implementasyonu buraya eklenecek.
}
