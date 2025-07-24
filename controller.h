#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#define IMU_FREQ 400                   // hz
#define LIDAR_FREQ 1000                // hz
#define PRES_TRANS_FREQ 1000           // hz
#define ENCODER_FREQ 1000              // hz
#define VOLTAGE_MEAS_FREQ 100          // hz
#define CONTROLLER_SCHEDULER_FREQ 2000 // hz

typedef struct {
  double euler[3]; // in rad or deg
  double quaternion[4];

  double lidar; // in mm

  double manifoldPress;  // in kPa
  double nozzlePress[4]; // in kPa

  double encoder[4];      // as5600 in deg
  double battery_voltage; // in V

  long int clock; // in ns or clock cycles
} controller_input_s;

typedef struct {
  double motor_voltage[4]; // in volts
  double motor_pwm[4];     // normalized, from -1 to 1

} controller_output_s;

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

typedef struct {
  double *u;
  double y;
  double y_pre;
  double alpha;
} ema_filter_s; // exponential moving average

void pid_controller_init(pid_controller_s *pid, pid_parameters_s *param,
                         double *ref, double *feedback);
void pid_controller_iterate(pid_controller_s *pid);
void pid_controller_reset(pid_controller_s *pid);

void controller_scheduler();

void ema_filter_init(ema_filter_s *ema_filter, double *ref,
                     double alpha); // exponential moving average
void ema_filter_iter(ema_filter_s *ema_filter);
void ema_filter_reset(ema_filter_s *ema_filter);

#endif
