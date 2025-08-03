/* Include files */

#include "modelInterface.h"
#include "m_xTvKGoSriW4GNDMRo1sXUH.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static emlrtRTEInfo emlrtRTEI = { 5,   /* lineNo */
  5,                                   /* colNo */
  "OutputCode",                        /* fName */
  ""                                   /* pName */
};

/* Function Declarations */
static void cgxe_mdl_start(InstanceStruct_xTvKGoSriW4GNDMRo1sXUH *moduleInstance);
static void cgxe_mdl_initialize(InstanceStruct_xTvKGoSriW4GNDMRo1sXUH
  *moduleInstance);
static void cgxe_mdl_outputs(InstanceStruct_xTvKGoSriW4GNDMRo1sXUH
  *moduleInstance);
static void cgxe_mdl_update(InstanceStruct_xTvKGoSriW4GNDMRo1sXUH
  *moduleInstance);
static void cgxe_mdl_derivative(InstanceStruct_xTvKGoSriW4GNDMRo1sXUH
  *moduleInstance);
static void cgxe_mdl_enable(InstanceStruct_xTvKGoSriW4GNDMRo1sXUH
  *moduleInstance);
static void cgxe_mdl_disable(InstanceStruct_xTvKGoSriW4GNDMRo1sXUH
  *moduleInstance);
static void cgxe_mdl_terminate(InstanceStruct_xTvKGoSriW4GNDMRo1sXUH
  *moduleInstance);
static void init_simulink_io_address(InstanceStruct_xTvKGoSriW4GNDMRo1sXUH
  *moduleInstance);

/* Function Definitions */
static void cgxe_mdl_start(InstanceStruct_xTvKGoSriW4GNDMRo1sXUH *moduleInstance)
{
  ema_filter_s myFilter;
  init_simulink_io_address(moduleInstance);
  cgxertSetSimStateCompliance(moduleInstance->S, 4);
  *moduleInstance->b_y0 = 0.0;
  myFilter.u = 0.0;
  myFilter.y = 0.0;
  myFilter.y_pre = 0.0;
  myFilter.alpha = 10.0;
  *moduleInstance->pointer = (void *)&myFilter;
}

static void cgxe_mdl_initialize(InstanceStruct_xTvKGoSriW4GNDMRo1sXUH
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_outputs(InstanceStruct_xTvKGoSriW4GNDMRo1sXUH
  *moduleInstance)
{
  ema_filter_s *myFilter;
  ema_filter_s *r;
  myFilter = (ema_filter_s *)0U;
  myFilter = (ema_filter_s *)*moduleInstance->pointer;
  ema_filter_iter_A07rCUBQCItfiH3cynSDBG((ema_filter_s *)&myFilter,
    *moduleInstance->u0);
  r = myFilter;
  cgxertCheckNullptr(moduleInstance->S, -1, -1, &emlrtRTEI, r, 2);
  *moduleInstance->b_y0 = r->y;
}

static void cgxe_mdl_update(InstanceStruct_xTvKGoSriW4GNDMRo1sXUH
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_derivative(InstanceStruct_xTvKGoSriW4GNDMRo1sXUH
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_enable(InstanceStruct_xTvKGoSriW4GNDMRo1sXUH
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_disable(InstanceStruct_xTvKGoSriW4GNDMRo1sXUH
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_terminate(InstanceStruct_xTvKGoSriW4GNDMRo1sXUH
  *moduleInstance)
{
  (void)moduleInstance;
}

static void init_simulink_io_address(InstanceStruct_xTvKGoSriW4GNDMRo1sXUH
  *moduleInstance)
{
  moduleInstance->emlrtRootTLSGlobal = (void *)cgxertGetEMLRTCtx
    (moduleInstance->S);
  moduleInstance->u0 = (real_T *)cgxertGetInputPortSignal(moduleInstance->S, 0);
  moduleInstance->b_y0 = (real_T *)cgxertGetOutputPortSignal(moduleInstance->S,
    0);
  moduleInstance->pointer = (void **)cgxertGetDWork(moduleInstance->S, 0);
}

/* CGXE Glue Code */
static void mdlOutputs_xTvKGoSriW4GNDMRo1sXUH(SimStruct *S, int_T tid)
{
  InstanceStruct_xTvKGoSriW4GNDMRo1sXUH *moduleInstance =
    (InstanceStruct_xTvKGoSriW4GNDMRo1sXUH *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_outputs(moduleInstance);
}

static void mdlInitialize_xTvKGoSriW4GNDMRo1sXUH(SimStruct *S)
{
  InstanceStruct_xTvKGoSriW4GNDMRo1sXUH *moduleInstance =
    (InstanceStruct_xTvKGoSriW4GNDMRo1sXUH *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_initialize(moduleInstance);
}

static void mdlUpdate_xTvKGoSriW4GNDMRo1sXUH(SimStruct *S, int_T tid)
{
  InstanceStruct_xTvKGoSriW4GNDMRo1sXUH *moduleInstance =
    (InstanceStruct_xTvKGoSriW4GNDMRo1sXUH *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_update(moduleInstance);
}

static void mdlDerivatives_xTvKGoSriW4GNDMRo1sXUH(SimStruct *S)
{
  InstanceStruct_xTvKGoSriW4GNDMRo1sXUH *moduleInstance =
    (InstanceStruct_xTvKGoSriW4GNDMRo1sXUH *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_derivative(moduleInstance);
}

static void mdlTerminate_xTvKGoSriW4GNDMRo1sXUH(SimStruct *S)
{
  InstanceStruct_xTvKGoSriW4GNDMRo1sXUH *moduleInstance =
    (InstanceStruct_xTvKGoSriW4GNDMRo1sXUH *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_terminate(moduleInstance);
  free((void *)moduleInstance);
}

static void mdlEnable_xTvKGoSriW4GNDMRo1sXUH(SimStruct *S)
{
  InstanceStruct_xTvKGoSriW4GNDMRo1sXUH *moduleInstance =
    (InstanceStruct_xTvKGoSriW4GNDMRo1sXUH *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_enable(moduleInstance);
}

static void mdlDisable_xTvKGoSriW4GNDMRo1sXUH(SimStruct *S)
{
  InstanceStruct_xTvKGoSriW4GNDMRo1sXUH *moduleInstance =
    (InstanceStruct_xTvKGoSriW4GNDMRo1sXUH *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_disable(moduleInstance);
}

static void mdlStart_xTvKGoSriW4GNDMRo1sXUH(SimStruct *S)
{
  InstanceStruct_xTvKGoSriW4GNDMRo1sXUH *moduleInstance =
    (InstanceStruct_xTvKGoSriW4GNDMRo1sXUH *)calloc(1, sizeof
    (InstanceStruct_xTvKGoSriW4GNDMRo1sXUH));
  moduleInstance->S = S;
  cgxertSetRuntimeInstance(S, (void *)moduleInstance);
  ssSetmdlOutputs(S, mdlOutputs_xTvKGoSriW4GNDMRo1sXUH);
  ssSetmdlInitializeConditions(S, mdlInitialize_xTvKGoSriW4GNDMRo1sXUH);
  ssSetmdlUpdate(S, mdlUpdate_xTvKGoSriW4GNDMRo1sXUH);
  ssSetmdlDerivatives(S, mdlDerivatives_xTvKGoSriW4GNDMRo1sXUH);
  ssSetmdlTerminate(S, mdlTerminate_xTvKGoSriW4GNDMRo1sXUH);
  ssSetmdlEnable(S, mdlEnable_xTvKGoSriW4GNDMRo1sXUH);
  ssSetmdlDisable(S, mdlDisable_xTvKGoSriW4GNDMRo1sXUH);
  cgxe_mdl_start(moduleInstance);

  {
    uint_T options = ssGetOptions(S);
    options |= SS_OPTION_RUNTIME_EXCEPTION_FREE_CODE;
    ssSetOptions(S, options);
  }
}

static void mdlProcessParameters_xTvKGoSriW4GNDMRo1sXUH(SimStruct *S)
{
}

void method_dispatcher_xTvKGoSriW4GNDMRo1sXUH(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_xTvKGoSriW4GNDMRo1sXUH(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_xTvKGoSriW4GNDMRo1sXUH(S);
    break;

   default:
    /* Unhandled method */
    /*
       sf_mex_error_message("Stateflow Internal Error:\n"
       "Error calling method dispatcher for module: xTvKGoSriW4GNDMRo1sXUH.\n"
       "Can't handle method %d.\n", method);
     */
    break;
  }
}

mxArray *cgxe_xTvKGoSriW4GNDMRo1sXUH_BuildInfoUpdate(void)
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

mxArray *cgxe_xTvKGoSriW4GNDMRo1sXUH_fallback_info(void)
{
  const char* fallbackInfoFields[] = { "fallbackType", "incompatiableSymbol" };

  mxArray* fallbackInfoStruct = mxCreateStructMatrix(1, 1, 2, fallbackInfoFields);
  mxArray* fallbackType = mxCreateString("incompatibleFunction");
  mxArray* incompatibleSymbol = mxCreateString("ema_filter_iter");
  mxSetFieldByNumber(fallbackInfoStruct, 0, 0, fallbackType);
  mxSetFieldByNumber(fallbackInfoStruct, 0, 1, incompatibleSymbol);
  return fallbackInfoStruct;
}
