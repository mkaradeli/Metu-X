#ifndef __sEMIHykuWPpAUJCz8WqpVH_h__
#define __sEMIHykuWPpAUJCz8WqpVH_h__

/* Include files */
#include "simstruc.h"
#include "rtwtypes.h"
#include "multiword_types.h"
#include "slexec_vm_zc_functions.h"
#include "slexec_vm_simstruct_bridge.h"
#include "sl_sfcn_cov/sl_sfcn_cov_bridge.h"

/* Type Definitions */
#ifndef typedef_InstanceStruct_sEMIHykuWPpAUJCz8WqpVH
#define typedef_InstanceStruct_sEMIHykuWPpAUJCz8WqpVH

typedef struct {
  SimStruct *S;
  void *emlrtRootTLSGlobal;
  real_T *u0;
  real_T *b_y0;
  void **pointer;
  real_T *u_p;
} InstanceStruct_sEMIHykuWPpAUJCz8WqpVH;

#endif                                 /* typedef_InstanceStruct_sEMIHykuWPpAUJCz8WqpVH */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
extern void method_dispatcher_sEMIHykuWPpAUJCz8WqpVH(SimStruct *S, int_T method,
  void* data);

#endif
