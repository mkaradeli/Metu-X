
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
  double error;
  double error_pre;
  double error_rateLimited;

  double uP;
  double uI;
  double uD;
  double uFF;
  double u;
  double saturated;

} pid_object_s;

pid_object_s pid_object_create(pid_parameters_s *param, double *ref,
                               double *feedback);
void pid_object_iterate();
