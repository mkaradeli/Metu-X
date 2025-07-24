#include "controller.h"
#include "controller_parameters.c"

void pid_create_init(pid_controller_s *pid, pid_parameters_s *param,
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

void pid_reset(pid_controller_s *pid) {
  pid->error_pre = 0;
  pid->ref_pre = 0;
  pid->y = 0;
  pid->ref_rateLimited = 0;
  pid->error = 0;
}

void controller_scheduler() {
  // TODO: write the scheduler;
}

void ema_filter_init(ema_filter_s *ema_filter, double *ref, double alpha) {
  ema_filter->u = ref;
  ema_filter->y = *ref;
  ema_filter->y_pre = *ref;
  ema_filter->alpha = alpha;
}

void ema_filter_iter(ema_filter_s *ema_filter) {
  ema_filter->y_pre = ema_filter->y;
  ema_filter->y = ema_filter->y_pre * (1 - ema_filter->alpha) +
                  *ema_filter->u * ema_filter->alpha;
}

void ema_filter_reset(ema_filter_s *ema_filter) {
  ema_filter->y = *ema_filter->u;
  ema_filter->y_pre = ema_filter->y;
}
