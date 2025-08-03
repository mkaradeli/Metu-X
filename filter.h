#ifndef __FILTER_H__
#define __FILTER_H__
typedef struct {
  double *u;
  double y;
  double y_pre;
  double alpha;
} ema_filter_s; // exponential moving average

void ema_filter_init(ema_filter_s *ema_filter, double *ref,
                     double alpha); // exponential moving average
void ema_filter_iter(ema_filter_s *ema_filter);
void ema_filter_reset(ema_filter_s *ema_filter);

#endif // !__FILTER_H__
