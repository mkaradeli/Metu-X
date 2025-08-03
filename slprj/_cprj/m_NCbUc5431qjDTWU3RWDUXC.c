/* Include files */

#include "modelInterface.h"
#include "m_NCbUc5431qjDTWU3RWDUXC.h"

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
static void cgxe_mdl_start(InstanceStruct_NCbUc5431qjDTWU3RWDUXC *moduleInstance);
static void cgxe_mdl_initialize(InstanceStruct_NCbUc5431qjDTWU3RWDUXC
  *moduleInstance);
static void cgxe_mdl_outputs(InstanceStruct_NCbUc5431qjDTWU3RWDUXC
  *moduleInstance);
static void cgxe_mdl_update(InstanceStruct_NCbUc5431qjDTWU3RWDUXC
  *moduleInstance);
static void cgxe_mdl_derivative(InstanceStruct_NCbUc5431qjDTWU3RWDUXC
  *moduleInstance);
static void cgxe_mdl_enable(InstanceStruct_NCbUc5431qjDTWU3RWDUXC
  *moduleInstance);
static void cgxe_mdl_disable(InstanceStruct_NCbUc5431qjDTWU3RWDUXC
  *moduleInstance);
static void cgxe_mdl_terminate(InstanceStruct_NCbUc5431qjDTWU3RWDUXC
  *moduleInstance);
static void init_simulink_io_address(InstanceStruct_NCbUc5431qjDTWU3RWDUXC
  *moduleInstance);

/* Function Definitions */
static void cgxe_mdl_start(InstanceStruct_NCbUc5431qjDTWU3RWDUXC *moduleInstance)
{
  ema_filter_s myFilter;
  init_simulink_io_address(moduleInstance);
  cgxertSetSimStateCompliance(moduleInstance->S, 4);
  *moduleInstance->b_y0 = 0.0;
  myFilter.u = 0.0;
  myFilter.y = 0.0;
  myFilter.y_pre = 0.0;
  myFilter.alpha = 0.0;
  *moduleInstance->pointer = (void *)&myFilter;
}

static void cgxe_mdl_initialize(InstanceStruct_NCbUc5431qjDTWU3RWDUXC
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_outputs(InstanceStruct_NCbUc5431qjDTWU3RWDUXC
  *moduleInstance)
{
  ema_filter_s *myFilter;
  myFilter = (ema_filter_s *)*moduleInstance->pointer;
  cgxertCheckNullptr(moduleInstance->S, -1, -1, &emlrtRTEI, myFilter, 1);
  ema_filter_iter_buqOs9baKS3mMaZ1iNtPUC(myFilter, *moduleInstance->u0);
  cgxertCheckNullptr(moduleInstance->S, -1, -1, &b_emlrtRTEI, myFilter, 2);
  *moduleInstance->b_y0 = myFilter->y;
}

static void cgxe_mdl_update(InstanceStruct_NCbUc5431qjDTWU3RWDUXC
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_derivative(InstanceStruct_NCbUc5431qjDTWU3RWDUXC
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_enable(InstanceStruct_NCbUc5431qjDTWU3RWDUXC
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_disable(InstanceStruct_NCbUc5431qjDTWU3RWDUXC
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_terminate(InstanceStruct_NCbUc5431qjDTWU3RWDUXC
  *moduleInstance)
{
  (void)moduleInstance;
}

static void init_simulink_io_address(InstanceStruct_NCbUc5431qjDTWU3RWDUXC
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
static void mdlOutputs_NCbUc5431qjDTWU3RWDUXC(SimStruct *S, int_T tid)
{
  InstanceStruct_NCbUc5431qjDTWU3RWDUXC *moduleInstance =
    (InstanceStruct_NCbUc5431qjDTWU3RWDUXC *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_outputs(moduleInstance);
}

static void mdlInitialize_NCbUc5431qjDTWU3RWDUXC(SimStruct *S)
{
  InstanceStruct_NCbUc5431qjDTWU3RWDUXC *moduleInstance =
    (InstanceStruct_NCbUc5431qjDTWU3RWDUXC *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_initialize(moduleInstance);
}

static void mdlUpdate_NCbUc5431qjDTWU3RWDUXC(SimStruct *S, int_T tid)
{
  InstanceStruct_NCbUc5431qjDTWU3RWDUXC *moduleInstance =
    (InstanceStruct_NCbUc5431qjDTWU3RWDUXC *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_update(moduleInstance);
}

static void mdlDerivatives_NCbUc5431qjDTWU3RWDUXC(SimStruct *S)
{
  InstanceStruct_NCbUc5431qjDTWU3RWDUXC *moduleInstance =
    (InstanceStruct_NCbUc5431qjDTWU3RWDUXC *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_derivative(moduleInstance);
}

static void mdlTerminate_NCbUc5431qjDTWU3RWDUXC(SimStruct *S)
{
  InstanceStruct_NCbUc5431qjDTWU3RWDUXC *moduleInstance =
    (InstanceStruct_NCbUc5431qjDTWU3RWDUXC *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_terminate(moduleInstance);
  free((void *)moduleInstance);
}

static void mdlEnable_NCbUc5431qjDTWU3RWDUXC(SimStruct *S)
{
  InstanceStruct_NCbUc5431qjDTWU3RWDUXC *moduleInstance =
    (InstanceStruct_NCbUc5431qjDTWU3RWDUXC *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_enable(moduleInstance);
}

static void mdlDisable_NCbUc5431qjDTWU3RWDUXC(SimStruct *S)
{
  InstanceStruct_NCbUc5431qjDTWU3RWDUXC *moduleInstance =
    (InstanceStruct_NCbUc5431qjDTWU3RWDUXC *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_disable(moduleInstance);
}

static void mdlStart_NCbUc5431qjDTWU3RWDUXC(SimStruct *S)
{
  InstanceStruct_NCbUc5431qjDTWU3RWDUXC *moduleInstance =
    (InstanceStruct_NCbUc5431qjDTWU3RWDUXC *)calloc(1, sizeof
    (InstanceStruct_NCbUc5431qjDTWU3RWDUXC));
  moduleInstance->S = S;
  cgxertSetRuntimeInstance(S, (void *)moduleInstance);
  ssSetmdlOutputs(S, mdlOutputs_NCbUc5431qjDTWU3RWDUXC);
  ssSetmdlInitializeConditions(S, mdlInitialize_NCbUc5431qjDTWU3RWDUXC);
  ssSetmdlUpdate(S, mdlUpdate_NCbUc5431qjDTWU3RWDUXC);
  ssSetmdlDerivatives(S, mdlDerivatives_NCbUc5431qjDTWU3RWDUXC);
  ssSetmdlTerminate(S, mdlTerminate_NCbUc5431qjDTWU3RWDUXC);
  ssSetmdlEnable(S, mdlEnable_NCbUc5431qjDTWU3RWDUXC);
  ssSetmdlDisable(S, mdlDisable_NCbUc5431qjDTWU3RWDUXC);
  cgxe_mdl_start(moduleInstance);

  {
    uint_T options = ssGetOptions(S);
    options |= SS_OPTION_RUNTIME_EXCEPTION_FREE_CODE;
    ssSetOptions(S, options);
  }
}

static void mdlProcessParameters_NCbUc5431qjDTWU3RWDUXC(SimStruct *S)
{
}

void method_dispatcher_NCbUc5431qjDTWU3RWDUXC(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_NCbUc5431qjDTWU3RWDUXC(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_NCbUc5431qjDTWU3RWDUXC(S);
    break;

   default:
    /* Unhandled method */
    /*
       sf_mex_error_message("Stateflow Internal Error:\n"
       "Error calling method dispatcher for module: NCbUc5431qjDTWU3RWDUXC.\n"
       "Can't handle method %d.\n", method);
     */
    break;
  }
}

mxArray *cgxe_NCbUc5431qjDTWU3RWDUXC_BuildInfoUpdate(void)
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

mxArray *cgxe_NCbUc5431qjDTWU3RWDUXC_fallback_info(void)
{
  const char* fallbackInfoFields[] = { "fallbackType", "incompatiableSymbol" };

  mxArray* fallbackInfoStruct = mxCreateStructMatrix(1, 1, 2, fallbackInfoFields);
  mxArray* fallbackType = mxCreateString("incompatibleFunction");
  mxArray* incompatibleSymbol = mxCreateString("ema_filter_iter");
  mxSetFieldByNumber(fallbackInfoStruct, 0, 0, fallbackType);
  mxSetFieldByNumber(fallbackInfoStruct, 0, 1, incompatibleSymbol);
  return fallbackInfoStruct;
}
