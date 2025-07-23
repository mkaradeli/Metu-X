#include "controller.h"

pid_controller_s pid_create(pid_parameters_s *param, double *ref,
                            double *feedback) {
  pid_controller_s myPidStruct;
  myPidStruct.parameter = param;
  myPidStruct.ref = ref;
  myPidStruct.feedback = feedback;
  myPidStruct.error = 0;
  myPidStruct.error_pre = 0;
  myPidStruct.ref_rateLimited = 0;
  myPidStruct.ref_pre = 0;
  myPidStruct.u = 0;
  myPidStruct.uP = 0;
  myPidStruct.uI = 0;
  myPidStruct.uD = 0;
  myPidStruct.uFF = 0;
  myPidStruct.y = 0;

  return myPidStruct;
};

void pid_iterate(pid_controller_s *pid) {
  // Rate limit the referance
  pid->ref_rateLimited = *pid->ref;
  if (*pid->ref - pid->ref_pre > pid->parameter->rateLimitMax) {
    pid->ref_rateLimited = pid->ref_pre + pid->parameter->rateLimitMax;
  } else if (*pid->ref - pid->ref_pre < pid->parameter->rateLimitMin) {
    pid->ref_rateLimited = pid->ref_pre + pid->parameter->rateLimitMin;
  }

  // calculate error
  pid->error = pid->ref_rateLimited - *pid->feedback;

  // calculate the pre saturated controller output
  pid->uP = pid->parameter->kP * pid->error;
  pid->uI = pid->parameter->kI * pid->error + pid->uI;
  // check if integrator component is saturated.
  if (pid->uI > pid->parameter->integralSaturationMax) {
    pid->uI = pid->parameter->integralSaturationMax;
  } else if (pid->uI < pid->parameter->integralSaturationMin) {
    pid->uI = pid->parameter->integralSaturationMin;
  }
  pid->uD = pid->parameter->kD * (pid->error - pid->error_pre);
  pid->uFF = pid->parameter->kFF * pid->ref_rateLimited;
  pid->u = pid->uP + pid->uI + pid->uD + pid->uFF;
  // check if controller output is saturated.
  pid->y = pid->u;
  if (pid->y > pid->parameter->saturationMax) {
    pid->y = pid->parameter->saturationMax;
  } else if (pid->y < pid->parameter->saturationMin) {
    pid->y = pid->parameter->saturationMin;
  };

  pid->ref_pre = pid->ref_rateLimited;
  pid->error_pre = pid->error;
};
