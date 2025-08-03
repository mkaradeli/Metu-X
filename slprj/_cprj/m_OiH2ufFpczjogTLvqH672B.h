#ifndef __OiH2ufFpczjogTLvqH672B_h__
#define __OiH2ufFpczjogTLvqH672B_h__

/* Include files */
#include "simstruc.h"
#include "rtwtypes.h"
#include "multiword_types.h"
#include "slexec_vm_zc_functions.h"
#include "slexec_vm_simstruct_bridge.h"
#include "sl_sfcn_cov/sl_sfcn_cov_bridge.h"

/* Type Definitions */
#ifndef typedef_InstanceStruct_OiH2ufFpczjogTLvqH672B
#define typedef_InstanceStruct_OiH2ufFpczjogTLvqH672B

typedef struct {
  SimStruct *S;
  void *emlrtRootTLSGlobal;
  real_T *u0;
  real_T *b_y0;
  void **pointer;
} InstanceStruct_OiH2ufFpczjogTLvqH672B;

#endif                                 /* typedef_InstanceStruct_OiH2ufFpczjogTLvqH672B */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
extern void method_dispatcher_OiH2ufFpczjogTLvqH672B(SimStruct *S, int_T method,
  void* data);

#endif
