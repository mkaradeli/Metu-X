/* Include files */

#include "modelInterface.h"
#include "m_uxIA067TJG72qMIVkT1ZPC.h"

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
static void cgxe_mdl_start(InstanceStruct_uxIA067TJG72qMIVkT1ZPC *moduleInstance);
static void cgxe_mdl_initialize(InstanceStruct_uxIA067TJG72qMIVkT1ZPC
  *moduleInstance);
static void cgxe_mdl_outputs(InstanceStruct_uxIA067TJG72qMIVkT1ZPC
  *moduleInstance);
static void cgxe_mdl_update(InstanceStruct_uxIA067TJG72qMIVkT1ZPC
  *moduleInstance);
static void cgxe_mdl_derivative(InstanceStruct_uxIA067TJG72qMIVkT1ZPC
  *moduleInstance);
static void cgxe_mdl_enable(InstanceStruct_uxIA067TJG72qMIVkT1ZPC
  *moduleInstance);
static void cgxe_mdl_disable(InstanceStruct_uxIA067TJG72qMIVkT1ZPC
  *moduleInstance);
static void cgxe_mdl_terminate(InstanceStruct_uxIA067TJG72qMIVkT1ZPC
  *moduleInstance);
static void init_simulink_io_address(InstanceStruct_uxIA067TJG72qMIVkT1ZPC
  *moduleInstance);

/* Function Definitions */
static void cgxe_mdl_start(InstanceStruct_uxIA067TJG72qMIVkT1ZPC *moduleInstance)
{
  ema_filter_s myFilter;
  real_T *alpha;
  init_simulink_io_address(moduleInstance);
  alpha = (real_T *)cgxertGetRunTimeParamInfoData(moduleInstance->S, 0);
  cgxertSetSimStateCompliance(moduleInstance->S, 4);
  *moduleInstance->pointer = NULL;
  *moduleInstance->u_p = 0.0;
  *moduleInstance->b_y0 = 0.0;
  ema_filter_init_8YnsiYi4JTQqWAQDKCl8IF(&myFilter, moduleInstance->u_p, *alpha);
  *moduleInstance->pointer = (void *)&myFilter;
}

static void cgxe_mdl_initialize(InstanceStruct_uxIA067TJG72qMIVkT1ZPC
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_outputs(InstanceStruct_uxIA067TJG72qMIVkT1ZPC
  *moduleInstance)
{
  ema_filter_s *myFilter;
  myFilter = (ema_filter_s *)*moduleInstance->pointer;
  *moduleInstance->u_p = *moduleInstance->u0;
  cgxertCheckNullptr(moduleInstance->S, -1, -1, &emlrtRTEI, myFilter, 1);
  ema_filter_iter_8YnsiYi4JTQqWAQDKCl8IF(myFilter);
  cgxertCheckNullptr(moduleInstance->S, -1, -1, &b_emlrtRTEI, myFilter, 2);
  *moduleInstance->b_y0 = myFilter->y;
}

static void cgxe_mdl_update(InstanceStruct_uxIA067TJG72qMIVkT1ZPC
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_derivative(InstanceStruct_uxIA067TJG72qMIVkT1ZPC
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_enable(InstanceStruct_uxIA067TJG72qMIVkT1ZPC
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_disable(InstanceStruct_uxIA067TJG72qMIVkT1ZPC
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_terminate(InstanceStruct_uxIA067TJG72qMIVkT1ZPC
  *moduleInstance)
{
  (void)moduleInstance;
}

static void init_simulink_io_address(InstanceStruct_uxIA067TJG72qMIVkT1ZPC
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
static void mdlOutputs_uxIA067TJG72qMIVkT1ZPC(SimStruct *S, int_T tid)
{
  InstanceStruct_uxIA067TJG72qMIVkT1ZPC *moduleInstance =
    (InstanceStruct_uxIA067TJG72qMIVkT1ZPC *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_outputs(moduleInstance);
}

static void mdlInitialize_uxIA067TJG72qMIVkT1ZPC(SimStruct *S)
{
  InstanceStruct_uxIA067TJG72qMIVkT1ZPC *moduleInstance =
    (InstanceStruct_uxIA067TJG72qMIVkT1ZPC *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_initialize(moduleInstance);
}

static void mdlUpdate_uxIA067TJG72qMIVkT1ZPC(SimStruct *S, int_T tid)
{
  InstanceStruct_uxIA067TJG72qMIVkT1ZPC *moduleInstance =
    (InstanceStruct_uxIA067TJG72qMIVkT1ZPC *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_update(moduleInstance);
}

static void mdlDerivatives_uxIA067TJG72qMIVkT1ZPC(SimStruct *S)
{
  InstanceStruct_uxIA067TJG72qMIVkT1ZPC *moduleInstance =
    (InstanceStruct_uxIA067TJG72qMIVkT1ZPC *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_derivative(moduleInstance);
}

static void mdlTerminate_uxIA067TJG72qMIVkT1ZPC(SimStruct *S)
{
  InstanceStruct_uxIA067TJG72qMIVkT1ZPC *moduleInstance =
    (InstanceStruct_uxIA067TJG72qMIVkT1ZPC *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_terminate(moduleInstance);
  free((void *)moduleInstance);
}

static void mdlEnable_uxIA067TJG72qMIVkT1ZPC(SimStruct *S)
{
  InstanceStruct_uxIA067TJG72qMIVkT1ZPC *moduleInstance =
    (InstanceStruct_uxIA067TJG72qMIVkT1ZPC *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_enable(moduleInstance);
}

static void mdlDisable_uxIA067TJG72qMIVkT1ZPC(SimStruct *S)
{
  InstanceStruct_uxIA067TJG72qMIVkT1ZPC *moduleInstance =
    (InstanceStruct_uxIA067TJG72qMIVkT1ZPC *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_disable(moduleInstance);
}

static void mdlStart_uxIA067TJG72qMIVkT1ZPC(SimStruct *S)
{
  InstanceStruct_uxIA067TJG72qMIVkT1ZPC *moduleInstance =
    (InstanceStruct_uxIA067TJG72qMIVkT1ZPC *)calloc(1, sizeof
    (InstanceStruct_uxIA067TJG72qMIVkT1ZPC));
  moduleInstance->S = S;
  cgxertSetRuntimeInstance(S, (void *)moduleInstance);
  ssSetmdlOutputs(S, mdlOutputs_uxIA067TJG72qMIVkT1ZPC);
  ssSetmdlInitializeConditions(S, mdlInitialize_uxIA067TJG72qMIVkT1ZPC);
  ssSetmdlUpdate(S, mdlUpdate_uxIA067TJG72qMIVkT1ZPC);
  ssSetmdlDerivatives(S, mdlDerivatives_uxIA067TJG72qMIVkT1ZPC);
  ssSetmdlTerminate(S, mdlTerminate_uxIA067TJG72qMIVkT1ZPC);
  ssSetmdlEnable(S, mdlEnable_uxIA067TJG72qMIVkT1ZPC);
  ssSetmdlDisable(S, mdlDisable_uxIA067TJG72qMIVkT1ZPC);
  cgxe_mdl_start(moduleInstance);

  {
    uint_T options = ssGetOptions(S);
    options |= SS_OPTION_RUNTIME_EXCEPTION_FREE_CODE;
    ssSetOptions(S, options);
  }
}

static void mdlProcessParameters_uxIA067TJG72qMIVkT1ZPC(SimStruct *S)
{
}

void method_dispatcher_uxIA067TJG72qMIVkT1ZPC(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_uxIA067TJG72qMIVkT1ZPC(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_uxIA067TJG72qMIVkT1ZPC(S);
    break;

   default:
    /* Unhandled method */
    /*
       sf_mex_error_message("Stateflow Internal Error:\n"
       "Error calling method dispatcher for module: uxIA067TJG72qMIVkT1ZPC.\n"
       "Can't handle method %d.\n", method);
     */
    break;
  }
}

mxArray *cgxe_uxIA067TJG72qMIVkT1ZPC_BuildInfoUpdate(void)
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

mxArray *cgxe_uxIA067TJG72qMIVkT1ZPC_fallback_info(void)
{
  const char* fallbackInfoFields[] = { "fallbackType", "incompatiableSymbol" };

  mxArray* fallbackInfoStruct = mxCreateStructMatrix(1, 1, 2, fallbackInfoFields);
  mxArray* fallbackType = mxCreateString("incompatibleFunction");
  mxArray* incompatibleSymbol = mxCreateString("ema_filter_init");
  mxSetFieldByNumber(fallbackInfoStruct, 0, 0, fallbackType);
  mxSetFieldByNumber(fallbackInfoStruct, 0, 1, incompatibleSymbol);
  return fallbackInfoStruct;
}
