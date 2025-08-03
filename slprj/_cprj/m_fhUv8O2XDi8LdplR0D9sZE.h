#ifndef __fhUv8O2XDi8LdplR0D9sZE_h__
#define __fhUv8O2XDi8LdplR0D9sZE_h__

/* Include files */
#include "simstruc.h"
#include "rtwtypes.h"
#include "multiword_types.h"
#include "slexec_vm_zc_functions.h"
#include "slexec_vm_simstruct_bridge.h"
#include "sl_sfcn_cov/sl_sfcn_cov_bridge.h"

/* Type Definitions */
#ifndef typedef_InstanceStruct_fhUv8O2XDi8LdplR0D9sZE
#define typedef_InstanceStruct_fhUv8O2XDi8LdplR0D9sZE

typedef struct {
  SimStruct *S;
  void *emlrtRootTLSGlobal;
  real_T *u0;
  real_T *b_y0;
  void **pointer;
} InstanceStruct_fhUv8O2XDi8LdplR0D9sZE;

#endif                                 /* typedef_InstanceStruct_fhUv8O2XDi8LdplR0D9sZE */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
extern void method_dispatcher_fhUv8O2XDi8LdplR0D9sZE(SimStruct *S, int_T method,
  void* data);

#endif
