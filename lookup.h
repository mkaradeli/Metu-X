#ifndef __LOOKUP_H__
#define __LOOKUP_H__

typedef struct {
  double y;
  const double *ref_list;
  const double *val_list;
  int list_length;
  int last_ref;
} lookup_s;

void lookup_init(lookup_s *lookup, const double *ref_list,
                 const double *val_list, const int list_length);
double lookup_iter(lookup_s *lookup, double u);

#endif // !__LOOKUP_H__
