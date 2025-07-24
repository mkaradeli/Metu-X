#ifndef __PID_H__
#define __PID_H__

typedef struct {
  double kP;
  double kI;
  double kD;
  double kFF;
  double dT;

  double rateLimitMax;
  double rateLimitMin;

  double saturationMax;
  double saturationMin;
  double integralSaturationMax;
  double integralSaturationMin;
} pid_parameters_s;

typedef struct {
  pid_parameters_s *parameter;
  double *ref;
  double *feedback;
  double y;
  double ref_rateLimited;
  double ref_pre;
  double error;
  double error_pre;

  double uP;
  double uI;
  double uD;
  double uFF;
  double u;

} pid_controller_s;

void pid_controller_init(pid_controller_s *pid, pid_parameters_s *param,
                         double *ref, double *feedback);
void pid_controller_iterate(pid_controller_s *pid);
void pid_controller_reset(pid_controller_s *pid);

#endif // !__PID_H__
