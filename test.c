#include "controller.h"
#include "lookup.h"
#include <stdio.h>

#define PRINTF(val) printf(#val " = %f\n", val);
#define PRINTF4(val)                                                           \
  printf(#val " = %f, %f, %f, %f\n", val[0], val[1], val[2], val[3]);

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
  lookup_s height_command;
  lookup_init(&height_command, conops_heigth, conops_velocity,
              sizeof(conops_heigth));
  controller_s myController;
  controller_init(&myController);

  // iter
  myController.input.lidar = 10;

  controller_iter(&myController);
  controller_iter(&myController);
  controller_iter(&myController);
  PRINTF(myController.input.lidar);
  PRINTF(myController.fdbs.position_e.z);
  PRINTF(*myController.altitude_controller.ref);
  PRINTF(myController.altitude_controller.ref_rateLimited);
  PRINTF(myController.altitude_controller.y);
  PRINTF4(myController.refs.thrust);
  PRINTF4(myController.fdbs.thrust);
  PRINTF(myController.motor_controller[0].y);
  printf("%f,%f,%f\n", *myController.altitude_controller.ref,
         *myController.altitude_controller.feedback,
         myController.altitude_controller.uD);

  printf("%f,%f,%f\n", *myController.altitude_controller.ref,
         *myController.altitude_controller.feedback,
         myController.altitude_controller.y);
  printf("%f\n", myController.altitude_controller.uP);
  printFour(myController.refs.thrust);
  printFour(myController.fdbs.thrust);
  printf("%f,%f\n", myController.motor_controller[0].y,
         *myController.motor_controller[0].ref);
  printFour(myController.outputs.motor_pwm);
  return 0;
}
