
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

pid_controller_s pid_create(pid_parameters_s *param, double *ref,
                            double *feedback);
void pid_iterate(pid_controller_s *pid);
