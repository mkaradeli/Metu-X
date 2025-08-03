#ifndef __wzIBi0AUvYWXYJ4954HVF_h__
#define __wzIBi0AUvYWXYJ4954HVF_h__

/* Include files */
#include "simstruc.h"
#include "rtwtypes.h"
#include "multiword_types.h"
#include "slexec_vm_zc_functions.h"
#include "slexec_vm_simstruct_bridge.h"
#include "sl_sfcn_cov/sl_sfcn_cov_bridge.h"

/* Type Definitions */
#ifndef typedef_InstanceStruct_wzIBi0AUvYWXYJ4954HVF
#define typedef_InstanceStruct_wzIBi0AUvYWXYJ4954HVF

typedef struct {
  SimStruct *S;
  void *emlrtRootTLSGlobal;
  real_T *u0;
  real_T *b_y0;
  void **pointer;
} InstanceStruct_wzIBi0AUvYWXYJ4954HVF;

#endif                                 /* typedef_InstanceStruct_wzIBi0AUvYWXYJ4954HVF */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
extern void method_dispatcher_wzIBi0AUvYWXYJ4954HVF(SimStruct *S, int_T method,
  void* data);

#endif
