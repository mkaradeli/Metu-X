#include "pid.h"

void pid_controller_init(pid_controller_s *pid, pid_parameters_s *param,
                         double *ref, double *feedback) {
  pid->parameter = param;
  pid->ref = ref;
  pid->feedback = feedback;
  pid->error = 0;
  pid->error_pre = 0;
  pid->ref_rateLimited = 0;
  pid->ref_pre = 0;
  pid->u = 0;
  pid->uP = 0;
  pid->uI = 0;
  pid->uD = 0;
  pid->uFF = 0;
  pid->y = 0;
}

void pid_controller_iterate(pid_controller_s *pid) {
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
    pid->uI = pid->parameter->integralSaturationMax + pid->uI;
  } else if (pid->uI < pid->parameter->integralSaturationMin) {
    pid->uI = pid->parameter->integralSaturationMin + pid->uI;
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

void pid_controller_reset(pid_controller_s *pid) {
  pid->error_pre = 0;
  pid->ref_pre = 0;
  pid->y = 0;
  pid->ref_rateLimited = 0;
  pid->error = 0;
}
