#include "pid.h"

pid_object_s pid_object_create(pid_parameters_s *param, double *ref,
                               double *feedback) {
  pid_object_s myPidStruct;
  myPidStruct.parameter = param;
  myPidStruct.ref = ref;
  myPidStruct.feedback = feedback;
  return myPidStruct;
};

void pid_object_iterate() {
  // to do
  return;
};
