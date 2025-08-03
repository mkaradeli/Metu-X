#include "lookup.h"

void lookup_init(lookup_s *lookup, const double *ref_list,
                 const double *val_list, const int list_length) {
  lookup->ref_list = ref_list;
  lookup->val_list = val_list;
  lookup->y = 0;
  lookup->last_ref = 0;
  lookup->list_length = list_length;
}

double lookup_iter(lookup_s *lookup, double u) {
  // printf("u=%f\n", u);
  //  check for boundaries
  if (u <= lookup->ref_list[0]) {
    lookup->y = lookup->val_list[0];
    lookup->last_ref = 0;
    return lookup->y;
  } else if (u >= lookup->ref_list[lookup->list_length - 1]) {
    lookup->y = lookup->val_list[lookup->list_length - 1];
    lookup->last_ref = lookup->list_length - 1;
    return lookup->y;
  }

  if (u < lookup->ref_list[lookup->last_ref]) {
    lookup->last_ref = 0;
  }

  for (int i = lookup->last_ref; i < lookup->list_length - 1; i++) {
    if (u < lookup->ref_list[i + 1]) {
      lookup->last_ref = i;
      // printf("here, %d\n", i);
      break;
    }
  }

  double y1 = lookup->val_list[lookup->last_ref + 1];
  double y0 = lookup->val_list[lookup->last_ref];
  double x1 = lookup->ref_list[lookup->last_ref + 1];
  double x0 = lookup->ref_list[lookup->last_ref];
  // printf("x0,x1,y0,y1 = %f, %f, %f, %f \n", x0, x1, y0, y1);
  lookup->y = (y1 * (u - x0) + y0 * (x1 - u)) / (x1 - x0);

  return lookup->y;
}
