/* Include files */

#include "modelInterface.h"
#include "m_G1gXoVuXuHl4aJH7y2ITWF.h"

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
static void cgxe_mdl_start(InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF *moduleInstance);
static void cgxe_mdl_initialize(InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF
  *moduleInstance);
static void cgxe_mdl_outputs(InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF
  *moduleInstance);
static void cgxe_mdl_update(InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF
  *moduleInstance);
static void cgxe_mdl_derivative(InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF
  *moduleInstance);
static void cgxe_mdl_enable(InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF
  *moduleInstance);
static void cgxe_mdl_disable(InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF
  *moduleInstance);
static void cgxe_mdl_terminate(InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF
  *moduleInstance);
static void init_simulink_io_address(InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF
  *moduleInstance);

/* Function Definitions */
static void cgxe_mdl_start(InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF *moduleInstance)
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

static void cgxe_mdl_initialize(InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_outputs(InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF
  *moduleInstance)
{
  ema_filter_s *myFilter;
  myFilter = (ema_filter_s *)*moduleInstance->pointer;
  cgxertCheckNullptr(moduleInstance->S, -1, -1, &emlrtRTEI, myFilter, 1);
  ema_filter_iter_A07rCUBQCItfiH3cynSDBG(myFilter, *moduleInstance->u0);
  cgxertCheckNullptr(moduleInstance->S, -1, -1, &b_emlrtRTEI, myFilter, 2);
  *moduleInstance->b_y0 = myFilter->y;
}

static void cgxe_mdl_update(InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_derivative(InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_enable(InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_disable(InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_terminate(InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF
  *moduleInstance)
{
  (void)moduleInstance;
}

static void init_simulink_io_address(InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF
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
static void mdlOutputs_G1gXoVuXuHl4aJH7y2ITWF(SimStruct *S, int_T tid)
{
  InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF *moduleInstance =
    (InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_outputs(moduleInstance);
}

static void mdlInitialize_G1gXoVuXuHl4aJH7y2ITWF(SimStruct *S)
{
  InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF *moduleInstance =
    (InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_initialize(moduleInstance);
}

static void mdlUpdate_G1gXoVuXuHl4aJH7y2ITWF(SimStruct *S, int_T tid)
{
  InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF *moduleInstance =
    (InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_update(moduleInstance);
}

static void mdlDerivatives_G1gXoVuXuHl4aJH7y2ITWF(SimStruct *S)
{
  InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF *moduleInstance =
    (InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_derivative(moduleInstance);
}

static void mdlTerminate_G1gXoVuXuHl4aJH7y2ITWF(SimStruct *S)
{
  InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF *moduleInstance =
    (InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_terminate(moduleInstance);
  free((void *)moduleInstance);
}

static void mdlEnable_G1gXoVuXuHl4aJH7y2ITWF(SimStruct *S)
{
  InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF *moduleInstance =
    (InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_enable(moduleInstance);
}

static void mdlDisable_G1gXoVuXuHl4aJH7y2ITWF(SimStruct *S)
{
  InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF *moduleInstance =
    (InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_disable(moduleInstance);
}

static void mdlStart_G1gXoVuXuHl4aJH7y2ITWF(SimStruct *S)
{
  InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF *moduleInstance =
    (InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF *)calloc(1, sizeof
    (InstanceStruct_G1gXoVuXuHl4aJH7y2ITWF));
  moduleInstance->S = S;
  cgxertSetRuntimeInstance(S, (void *)moduleInstance);
  ssSetmdlOutputs(S, mdlOutputs_G1gXoVuXuHl4aJH7y2ITWF);
  ssSetmdlInitializeConditions(S, mdlInitialize_G1gXoVuXuHl4aJH7y2ITWF);
  ssSetmdlUpdate(S, mdlUpdate_G1gXoVuXuHl4aJH7y2ITWF);
  ssSetmdlDerivatives(S, mdlDerivatives_G1gXoVuXuHl4aJH7y2ITWF);
  ssSetmdlTerminate(S, mdlTerminate_G1gXoVuXuHl4aJH7y2ITWF);
  ssSetmdlEnable(S, mdlEnable_G1gXoVuXuHl4aJH7y2ITWF);
  ssSetmdlDisable(S, mdlDisable_G1gXoVuXuHl4aJH7y2ITWF);
  cgxe_mdl_start(moduleInstance);

  {
    uint_T options = ssGetOptions(S);
    options |= SS_OPTION_RUNTIME_EXCEPTION_FREE_CODE;
    ssSetOptions(S, options);
  }
}

static void mdlProcessParameters_G1gXoVuXuHl4aJH7y2ITWF(SimStruct *S)
{
}

void method_dispatcher_G1gXoVuXuHl4aJH7y2ITWF(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_G1gXoVuXuHl4aJH7y2ITWF(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_G1gXoVuXuHl4aJH7y2ITWF(S);
    break;

   default:
    /* Unhandled method */
    /*
       sf_mex_error_message("Stateflow Internal Error:\n"
       "Error calling method dispatcher for module: G1gXoVuXuHl4aJH7y2ITWF.\n"
       "Can't handle method %d.\n", method);
     */
    break;
  }
}

mxArray *cgxe_G1gXoVuXuHl4aJH7y2ITWF_BuildInfoUpdate(void)
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

mxArray *cgxe_G1gXoVuXuHl4aJH7y2ITWF_fallback_info(void)
{
  const char* fallbackInfoFields[] = { "fallbackType", "incompatiableSymbol" };

  mxArray* fallbackInfoStruct = mxCreateStructMatrix(1, 1, 2, fallbackInfoFields);
  mxArray* fallbackType = mxCreateString("incompatibleFunction");
  mxArray* incompatibleSymbol = mxCreateString("ema_filter_iter");
  mxSetFieldByNumber(fallbackInfoStruct, 0, 0, fallbackType);
  mxSetFieldByNumber(fallbackInfoStruct, 0, 1, incompatibleSymbol);
  return fallbackInfoStruct;
}
