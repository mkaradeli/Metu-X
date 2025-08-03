#include "filter.h"

void ema_filter_init(ema_filter_s *ema_filter, double *ref, double alpha) {
  ema_filter->u = ref;
  ema_filter->y = *ref;
  ema_filter->y_pre = *ref;
  ema_filter->alpha = alpha;
}

void ema_filter_iter(ema_filter_s *ema_filter) {
  ema_filter->y_pre = ema_filter->y;
  ema_filter->y = (ema_filter->y_pre * (1 - ema_filter->alpha)) +
                  (*ema_filter->u * ema_filter->alpha);

  return;
}

void ema_filter_reset(ema_filter_s *ema_filter) {
  ema_filter->y = 0;
  ema_filter->y_pre = ema_filter->y;
}
