/* Include files */

#include "modelInterface.h"
#include "m_sEMIHykuWPpAUJCz8WqpVH.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static emlrtRTEInfo emlrtRTEI = { 3,   /* lineNo */
  17,                                  /* colNo */
  "OutputCode",                        /* fName */
  ""                                   /* pName */
};

static emlrtRTEInfo b_emlrtRTEI = { 5, /* lineNo */
  5,                                   /* colNo */
  "OutputCode",                        /* fName */
  ""                                   /* pName */
};

/* Function Declarations */
static void cgxe_mdl_start(InstanceStruct_sEMIHykuWPpAUJCz8WqpVH *moduleInstance);
static void cgxe_mdl_initialize(InstanceStruct_sEMIHykuWPpAUJCz8WqpVH
  *moduleInstance);
static void cgxe_mdl_outputs(InstanceStruct_sEMIHykuWPpAUJCz8WqpVH
  *moduleInstance);
static void cgxe_mdl_update(InstanceStruct_sEMIHykuWPpAUJCz8WqpVH
  *moduleInstance);
static void cgxe_mdl_derivative(InstanceStruct_sEMIHykuWPpAUJCz8WqpVH
  *moduleInstance);
static void cgxe_mdl_enable(InstanceStruct_sEMIHykuWPpAUJCz8WqpVH
  *moduleInstance);
static void cgxe_mdl_disable(InstanceStruct_sEMIHykuWPpAUJCz8WqpVH
  *moduleInstance);
static void cgxe_mdl_terminate(InstanceStruct_sEMIHykuWPpAUJCz8WqpVH
  *moduleInstance);
static void init_simulink_io_address(InstanceStruct_sEMIHykuWPpAUJCz8WqpVH
  *moduleInstance);

/* Function Definitions */
static void cgxe_mdl_start(InstanceStruct_sEMIHykuWPpAUJCz8WqpVH *moduleInstance)
{
  ema_filter_s myFilter;
  real_T *alpha;
  init_simulink_io_address(moduleInstance);
  alpha = (real_T *)cgxertGetRunTimeParamInfoData(moduleInstance->S, 0);
  cgxertSetSimStateCompliance(moduleInstance->S, 4);
  *moduleInstance->pointer = NULL;
  *moduleInstance->u_p = 0.0;
  *moduleInstance->b_y0 = 0.0;
  ema_filter_init_A38TBnXKvvbX2wZzRWDdhB(&myFilter, moduleInstance->u_p, *alpha);
  *moduleInstance->pointer = (void *)&myFilter;
}

static void cgxe_mdl_initialize(InstanceStruct_sEMIHykuWPpAUJCz8WqpVH
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_outputs(InstanceStruct_sEMIHykuWPpAUJCz8WqpVH
  *moduleInstance)
{
  ema_filter_s *myFilter;
  myFilter = (ema_filter_s *)*moduleInstance->pointer;
  *moduleInstance->u_p = *moduleInstance->u0;
  cgxertCheckNullptr(moduleInstance->S, -1, -1, &emlrtRTEI, myFilter, 1);
  ema_filter_iter_A38TBnXKvvbX2wZzRWDdhB(myFilter);
  cgxertCheckNullptr(moduleInstance->S, -1, -1, &b_emlrtRTEI, myFilter, 2);
  *moduleInstance->b_y0 = myFilter->y;
}

static void cgxe_mdl_update(InstanceStruct_sEMIHykuWPpAUJCz8WqpVH
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_derivative(InstanceStruct_sEMIHykuWPpAUJCz8WqpVH
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_enable(InstanceStruct_sEMIHykuWPpAUJCz8WqpVH
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_disable(InstanceStruct_sEMIHykuWPpAUJCz8WqpVH
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_terminate(InstanceStruct_sEMIHykuWPpAUJCz8WqpVH
  *moduleInstance)
{
  (void)moduleInstance;
}

static void init_simulink_io_address(InstanceStruct_sEMIHykuWPpAUJCz8WqpVH
  *moduleInstance)
{
  moduleInstance->emlrtRootTLSGlobal = (void *)cgxertGetEMLRTCtx
    (moduleInstance->S);
  moduleInstance->u0 = (real_T *)cgxertGetInputPortSignal(moduleInstance->S, 0);
  moduleInstance->b_y0 = (real_T *)cgxertGetOutputPortSignal(moduleInstance->S,
    0);
  moduleInstance->pointer = (void **)cgxertGetDWork(moduleInstance->S, 0);
  moduleInstance->u_p = (real_T *)cgxertGetDWork(moduleInstance->S, 1);
}

/* CGXE Glue Code */
static void mdlOutputs_sEMIHykuWPpAUJCz8WqpVH(SimStruct *S, int_T tid)
{
  InstanceStruct_sEMIHykuWPpAUJCz8WqpVH *moduleInstance =
    (InstanceStruct_sEMIHykuWPpAUJCz8WqpVH *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_outputs(moduleInstance);
}

static void mdlInitialize_sEMIHykuWPpAUJCz8WqpVH(SimStruct *S)
{
  InstanceStruct_sEMIHykuWPpAUJCz8WqpVH *moduleInstance =
    (InstanceStruct_sEMIHykuWPpAUJCz8WqpVH *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_initialize(moduleInstance);
}

static void mdlUpdate_sEMIHykuWPpAUJCz8WqpVH(SimStruct *S, int_T tid)
{
  InstanceStruct_sEMIHykuWPpAUJCz8WqpVH *moduleInstance =
    (InstanceStruct_sEMIHykuWPpAUJCz8WqpVH *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_update(moduleInstance);
}

static void mdlDerivatives_sEMIHykuWPpAUJCz8WqpVH(SimStruct *S)
{
  InstanceStruct_sEMIHykuWPpAUJCz8WqpVH *moduleInstance =
    (InstanceStruct_sEMIHykuWPpAUJCz8WqpVH *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_derivative(moduleInstance);
}

static void mdlTerminate_sEMIHykuWPpAUJCz8WqpVH(SimStruct *S)
{
  InstanceStruct_sEMIHykuWPpAUJCz8WqpVH *moduleInstance =
    (InstanceStruct_sEMIHykuWPpAUJCz8WqpVH *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_terminate(moduleInstance);
  free((void *)moduleInstance);
}

static void mdlEnable_sEMIHykuWPpAUJCz8WqpVH(SimStruct *S)
{
  InstanceStruct_sEMIHykuWPpAUJCz8WqpVH *moduleInstance =
    (InstanceStruct_sEMIHykuWPpAUJCz8WqpVH *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_enable(moduleInstance);
}

static void mdlDisable_sEMIHykuWPpAUJCz8WqpVH(SimStruct *S)
{
  InstanceStruct_sEMIHykuWPpAUJCz8WqpVH *moduleInstance =
    (InstanceStruct_sEMIHykuWPpAUJCz8WqpVH *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_disable(moduleInstance);
}

static void mdlStart_sEMIHykuWPpAUJCz8WqpVH(SimStruct *S)
{
  InstanceStruct_sEMIHykuWPpAUJCz8WqpVH *moduleInstance =
    (InstanceStruct_sEMIHykuWPpAUJCz8WqpVH *)calloc(1, sizeof
    (InstanceStruct_sEMIHykuWPpAUJCz8WqpVH));
  moduleInstance->S = S;
  cgxertSetRuntimeInstance(S, (void *)moduleInstance);
  ssSetmdlOutputs(S, mdlOutputs_sEMIHykuWPpAUJCz8WqpVH);
  ssSetmdlInitializeConditions(S, mdlInitialize_sEMIHykuWPpAUJCz8WqpVH);
  ssSetmdlUpdate(S, mdlUpdate_sEMIHykuWPpAUJCz8WqpVH);
  ssSetmdlDerivatives(S, mdlDerivatives_sEMIHykuWPpAUJCz8WqpVH);
  ssSetmdlTerminate(S, mdlTerminate_sEMIHykuWPpAUJCz8WqpVH);
  ssSetmdlEnable(S, mdlEnable_sEMIHykuWPpAUJCz8WqpVH);
  ssSetmdlDisable(S, mdlDisable_sEMIHykuWPpAUJCz8WqpVH);
  cgxe_mdl_start(moduleInstance);

  {
    uint_T options = ssGetOptions(S);
    options |= SS_OPTION_RUNTIME_EXCEPTION_FREE_CODE;
    ssSetOptions(S, options);
  }
}

static void mdlProcessParameters_sEMIHykuWPpAUJCz8WqpVH(SimStruct *S)
{
}

void method_dispatcher_sEMIHykuWPpAUJCz8WqpVH(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_sEMIHykuWPpAUJCz8WqpVH(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_sEMIHykuWPpAUJCz8WqpVH(S);
    break;

   default:
    /* Unhandled method */
    /*
       sf_mex_error_message("Stateflow Internal Error:\n"
       "Error calling method dispatcher for module: sEMIHykuWPpAUJCz8WqpVH.\n"
       "Can't handle method %d.\n", method);
     */
    break;
  }
}

mxArray *cgxe_sEMIHykuWPpAUJCz8WqpVH_BuildInfoUpdate(void)
{
  mxArray * mxBIArgs;
  mxArray * elem_1;
  mxArray * elem_2;
  mxArray * elem_3;
  double * pointer;
  mxBIArgs = mxCreateCellMatrix(1,3);
  elem_1 = mxCreateDoubleMatrix(0,0, mxREAL);
  pointer = mxGetPr(elem_1);
  mxSetCell(mxBIArgs,0,elem_1);
  elem_2 = mxCreateDoubleMatrix(0,0, mxREAL);
  pointer = mxGetPr(elem_2);
  mxSetCell(mxBIArgs,1,elem_2);
  elem_3 = mxCreateCellMatrix(1,0);
  mxSetCell(mxBIArgs,2,elem_3);
  return mxBIArgs;
}

mxArray *cgxe_sEMIHykuWPpAUJCz8WqpVH_fallback_info(void)
{
  const char* fallbackInfoFields[] = { "fallbackType", "incompatiableSymbol" };

  mxArray* fallbackInfoStruct = mxCreateStructMatrix(1, 1, 2, fallbackInfoFields);
  mxArray* fallbackType = mxCreateString("incompatibleFunction");
  mxArray* incompatibleSymbol = mxCreateString("ema_filter_init");
  mxSetFieldByNumber(fallbackInfoStruct, 0, 0, fallbackType);
  mxSetFieldByNumber(fallbackInfoStruct, 0, 1, incompatibleSymbol);
  return fallbackInfoStruct;
}
