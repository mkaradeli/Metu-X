/* Include files */

#include "modelInterface.h"
#include "m_EGnr1VSlkTYILtjl5ZTb9C.h"

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
static void cgxe_mdl_start(InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C *moduleInstance);
static void cgxe_mdl_initialize(InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C
  *moduleInstance);
static void cgxe_mdl_outputs(InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C
  *moduleInstance);
static void cgxe_mdl_update(InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C
  *moduleInstance);
static void cgxe_mdl_derivative(InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C
  *moduleInstance);
static void cgxe_mdl_enable(InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C
  *moduleInstance);
static void cgxe_mdl_disable(InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C
  *moduleInstance);
static void cgxe_mdl_terminate(InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C
  *moduleInstance);
static void init_simulink_io_address(InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C
  *moduleInstance);

/* Function Definitions */
static void cgxe_mdl_start(InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C *moduleInstance)
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

static void cgxe_mdl_initialize(InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_outputs(InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C
  *moduleInstance)
{
  ema_filter_s *myFilter;
  myFilter = (ema_filter_s *)*moduleInstance->pointer;
  cgxertCheckNullptr(moduleInstance->S, -1, -1, &emlrtRTEI, myFilter, 1);
  ema_filter_iter_buqOs9baKS3mMaZ1iNtPUC(myFilter, *moduleInstance->u0);
  cgxertCheckNullptr(moduleInstance->S, -1, -1, &b_emlrtRTEI, myFilter, 2);
  *moduleInstance->b_y0 = myFilter->y;
}

static void cgxe_mdl_update(InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_derivative(InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_enable(InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_disable(InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_terminate(InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C
  *moduleInstance)
{
  (void)moduleInstance;
}

static void init_simulink_io_address(InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C
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
static void mdlOutputs_EGnr1VSlkTYILtjl5ZTb9C(SimStruct *S, int_T tid)
{
  InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C *moduleInstance =
    (InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_outputs(moduleInstance);
}

static void mdlInitialize_EGnr1VSlkTYILtjl5ZTb9C(SimStruct *S)
{
  InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C *moduleInstance =
    (InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_initialize(moduleInstance);
}

static void mdlUpdate_EGnr1VSlkTYILtjl5ZTb9C(SimStruct *S, int_T tid)
{
  InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C *moduleInstance =
    (InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_update(moduleInstance);
}

static void mdlDerivatives_EGnr1VSlkTYILtjl5ZTb9C(SimStruct *S)
{
  InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C *moduleInstance =
    (InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_derivative(moduleInstance);
}

static void mdlTerminate_EGnr1VSlkTYILtjl5ZTb9C(SimStruct *S)
{
  InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C *moduleInstance =
    (InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_terminate(moduleInstance);
  free((void *)moduleInstance);
}

static void mdlEnable_EGnr1VSlkTYILtjl5ZTb9C(SimStruct *S)
{
  InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C *moduleInstance =
    (InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_enable(moduleInstance);
}

static void mdlDisable_EGnr1VSlkTYILtjl5ZTb9C(SimStruct *S)
{
  InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C *moduleInstance =
    (InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_disable(moduleInstance);
}

static void mdlStart_EGnr1VSlkTYILtjl5ZTb9C(SimStruct *S)
{
  InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C *moduleInstance =
    (InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C *)calloc(1, sizeof
    (InstanceStruct_EGnr1VSlkTYILtjl5ZTb9C));
  moduleInstance->S = S;
  cgxertSetRuntimeInstance(S, (void *)moduleInstance);
  ssSetmdlOutputs(S, mdlOutputs_EGnr1VSlkTYILtjl5ZTb9C);
  ssSetmdlInitializeConditions(S, mdlInitialize_EGnr1VSlkTYILtjl5ZTb9C);
  ssSetmdlUpdate(S, mdlUpdate_EGnr1VSlkTYILtjl5ZTb9C);
  ssSetmdlDerivatives(S, mdlDerivatives_EGnr1VSlkTYILtjl5ZTb9C);
  ssSetmdlTerminate(S, mdlTerminate_EGnr1VSlkTYILtjl5ZTb9C);
  ssSetmdlEnable(S, mdlEnable_EGnr1VSlkTYILtjl5ZTb9C);
  ssSetmdlDisable(S, mdlDisable_EGnr1VSlkTYILtjl5ZTb9C);
  cgxe_mdl_start(moduleInstance);

  {
    uint_T options = ssGetOptions(S);
    options |= SS_OPTION_RUNTIME_EXCEPTION_FREE_CODE;
    ssSetOptions(S, options);
  }
}

static void mdlProcessParameters_EGnr1VSlkTYILtjl5ZTb9C(SimStruct *S)
{
}

void method_dispatcher_EGnr1VSlkTYILtjl5ZTb9C(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_EGnr1VSlkTYILtjl5ZTb9C(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_EGnr1VSlkTYILtjl5ZTb9C(S);
    break;

   default:
    /* Unhandled method */
    /*
       sf_mex_error_message("Stateflow Internal Error:\n"
       "Error calling method dispatcher for module: EGnr1VSlkTYILtjl5ZTb9C.\n"
       "Can't handle method %d.\n", method);
     */
    break;
  }
}

mxArray *cgxe_EGnr1VSlkTYILtjl5ZTb9C_BuildInfoUpdate(void)
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

mxArray *cgxe_EGnr1VSlkTYILtjl5ZTb9C_fallback_info(void)
{
  const char* fallbackInfoFields[] = { "fallbackType", "incompatiableSymbol" };

  mxArray* fallbackInfoStruct = mxCreateStructMatrix(1, 1, 2, fallbackInfoFields);
  mxArray* fallbackType = mxCreateString("incompatibleFunction");
  mxArray* incompatibleSymbol = mxCreateString("ema_filter_iter");
  mxSetFieldByNumber(fallbackInfoStruct, 0, 0, fallbackType);
  mxSetFieldByNumber(fallbackInfoStruct, 0, 1, incompatibleSymbol);
  return fallbackInfoStruct;
}
