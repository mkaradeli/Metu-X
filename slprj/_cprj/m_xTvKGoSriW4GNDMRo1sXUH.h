#ifndef __xTvKGoSriW4GNDMRo1sXUH_h__
#define __xTvKGoSriW4GNDMRo1sXUH_h__

/* Include files */
#include "simstruc.h"
#include "rtwtypes.h"
#include "multiword_types.h"
#include "slexec_vm_zc_functions.h"
#include "slexec_vm_simstruct_bridge.h"
#include "sl_sfcn_cov/sl_sfcn_cov_bridge.h"

/* Type Definitions */
#ifndef typedef_InstanceStruct_xTvKGoSriW4GNDMRo1sXUH
#define typedef_InstanceStruct_xTvKGoSriW4GNDMRo1sXUH

typedef struct {
  SimStruct *S;
  void *emlrtRootTLSGlobal;
  real_T *u0;
  real_T *b_y0;
  void **pointer;
} InstanceStruct_xTvKGoSriW4GNDMRo1sXUH;

#endif                                 /* typedef_InstanceStruct_xTvKGoSriW4GNDMRo1sXUH */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
extern void method_dispatcher_xTvKGoSriW4GNDMRo1sXUH(SimStruct *S, int_T method,
  void* data);

#endif
