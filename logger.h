// TODO: logger eklenecek.
#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "common.h"
#include <assert.h>
#include <stddef.h>
#include <sys/types.h>

#define LOG_BUFFER_SIZE 128000

typedef struct {
  unsigned int timestamp;
  euler_s euler;
  u_int8_t lidar; // in mm

  double manifoldPress;  // in kPa
  double nozzlePress[4]; // in kPa

  double encoder[4];      // as5600 in deg
  double battery_voltage; // in V

  double motor_pwm[4];
} LogEntry_s; // Size 153 bytes

typedef struct {
  unsigned int head;
  unsigned int count;
  LogEntry_s data[LOG_BUFFER_SIZE];
} LogBuffer_s;

void logger_init(LogBuffer_s *buffer);
void logger_add(LogBuffer_s *buffer, LogEntry_s data);
void logger_send(LogBuffer_s *buffer);

#endif // !__LOGGER_H__
