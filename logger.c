#include "logger.h"
#include <stdio.h>

void logger_init(LogBuffer_s *buffer) {
  buffer->count = 0;
  buffer->head = 0;
  return;
};

void logger_add(LogBuffer_s *buffer, LogEntry_s data) {
  buffer->data[buffer->head] = data;
  buffer->head = (buffer->head + 1) % LOG_BUFFER_SIZE;
  if (buffer->count < LOG_BUFFER_SIZE)
    buffer->count++;
  return;
};

void logger_send(LogBuffer_s *buffer) {
  // TODO:
  LogEntry_s *entry;
  while (buffer->count) {
    entry = &buffer->data[buffer->head - 1];
    // TODO: Change printf to fprintf
    printf("%d, %.f, %.f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, "
           "%f, %f, %f\n",
           entry->timestamp, entry->euler.roll, entry->euler.pitch,
           entry->euler.yaw, entry->lidar, entry->manifoldPress,
           entry->nozzlePress[0], entry->nozzlePress[1], entry->nozzlePress[2],
           entry->nozzlePress[3], entry->encoder[0], entry->encoder[1],
           entry->encoder[2], entry->encoder[3], entry->battery_voltage,
           entry->motor_pwm[0], entry->motor_pwm[1], entry->motor_pwm[2],
           entry->motor_pwm[3]);
    buffer->count--;
    buffer->head = (buffer->head - 1) % LOG_BUFFER_SIZE;
  }
};
