#include "controller.h"
#include "pid.h"
#include <stdio.h>
void dummyFunction() {
  //
  return;
}
void printEuler(euler_s euler) {
  printf("%f, %f, %f \n", euler.pitch, euler.roll, euler.yaw);
}
void printFour(double *vec) {
  printf("%f, %f, %f, %f \n", vec[0], vec[1], vec[2], vec[3]);
}

int main() {

  // init
  controller_s myController;

  controller_init(&myController);

  update_function_p updateIMU_p = &dummyFunction;
  update_function_p updateLidar_p = &dummyFunction;
  update_function_p updatePressureTransducers_p = &dummyFunction;
  update_function_p updateEncoder_p = &dummyFunction;
  update_function_p updateBatteryVoltage_p = &dummyFunction;
  controller_sensors_init(&myController, updateIMU_p, updateLidar_p,
                          updatePressureTransducers_p, updateEncoder_p,
                          updateBatteryVoltage_p);

  // iter
  controller_iter(&myController);
  printFour(myController.outputs.motor_pwm);
  return 0;
}
