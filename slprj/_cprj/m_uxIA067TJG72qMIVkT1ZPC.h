#ifndef __uxIA067TJG72qMIVkT1ZPC_h__
#define __uxIA067TJG72qMIVkT1ZPC_h__

/* Include files */
#include "simstruc.h"
#include "rtwtypes.h"
#include "multiword_types.h"
#include "slexec_vm_zc_functions.h"
#include "slexec_vm_simstruct_bridge.h"
#include "sl_sfcn_cov/sl_sfcn_cov_bridge.h"
#include "cCodeTester_1_interface.h"

/* Type Definitions */
#ifndef typedef_InstanceStruct_uxIA067TJG72qMIVkT1ZPC
#define typedef_InstanceStruct_uxIA067TJG72qMIVkT1ZPC

typedef struct {
  SimStruct *S;
  void *emlrtRootTLSGlobal;
  real_T *u0;
  real_T *b_y0;
  void **pointer;
  real_T *u_p;
} InstanceStruct_uxIA067TJG72qMIVkT1ZPC;

#endif                                 /* typedef_InstanceStruct_uxIA067TJG72qMIVkT1ZPC */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
extern void method_dispatcher_uxIA067TJG72qMIVkT1ZPC(SimStruct *S, int_T method,
  void* data);

#endif
