/* Include files */

#include "modelInterface.h"
#include "m_wzIBi0AUvYWXYJ4954HVF.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static emlrtRTEInfo emlrtRTEI = { 4,   /* lineNo */
  27,                                  /* colNo */
  "StartCode",                         /* fName */
  ""                                   /* pName */
};

static emlrtRTEInfo b_emlrtRTEI = { 3, /* lineNo */
  1,                                   /* colNo */
  "OutputCode",                        /* fName */
  ""                                   /* pName */
};

static emlrtRTEInfo c_emlrtRTEI = { 4, /* lineNo */
  17,                                  /* colNo */
  "OutputCode",                        /* fName */
  ""                                   /* pName */
};

static emlrtRTEInfo d_emlrtRTEI = { 6, /* lineNo */
  5,                                   /* colNo */
  "OutputCode",                        /* fName */
  ""                                   /* pName */
};

/* Function Declarations */
static void cgxe_mdl_start(InstanceStruct_wzIBi0AUvYWXYJ4954HVF *moduleInstance);
static void cgxe_mdl_initialize(InstanceStruct_wzIBi0AUvYWXYJ4954HVF
  *moduleInstance);
static void cgxe_mdl_outputs(InstanceStruct_wzIBi0AUvYWXYJ4954HVF
  *moduleInstance);
static void cgxe_mdl_update(InstanceStruct_wzIBi0AUvYWXYJ4954HVF *moduleInstance);
static void cgxe_mdl_derivative(InstanceStruct_wzIBi0AUvYWXYJ4954HVF
  *moduleInstance);
static void cgxe_mdl_enable(InstanceStruct_wzIBi0AUvYWXYJ4954HVF *moduleInstance);
static void cgxe_mdl_disable(InstanceStruct_wzIBi0AUvYWXYJ4954HVF
  *moduleInstance);
static void cgxe_mdl_terminate(InstanceStruct_wzIBi0AUvYWXYJ4954HVF
  *moduleInstance);
static void init_simulink_io_address(InstanceStruct_wzIBi0AUvYWXYJ4954HVF
  *moduleInstance);

/* Function Definitions */
static void cgxe_mdl_start(InstanceStruct_wzIBi0AUvYWXYJ4954HVF *moduleInstance)
{
  ema_filter_s myFilter;
  real_T *alpha;
  real_T *r;
  init_simulink_io_address(moduleInstance);
  alpha = (real_T *)cgxertGetRunTimeParamInfoData(moduleInstance->S, 0);
  cgxertSetSimStateCompliance(moduleInstance->S, 4);
  *moduleInstance->pointer = NULL;
  *moduleInstance->b_y0 = 0.0;
  r = (real_T *)0U;
  cgxertCheckNullptr(moduleInstance->S, -1, -1, &emlrtRTEI, r, 1);
  ema_filter_init_A38TBnXKvvbX2wZzRWDdhB(&myFilter, r, *alpha);
  *moduleInstance->pointer = (void *)&myFilter;
}

static void cgxe_mdl_initialize(InstanceStruct_wzIBi0AUvYWXYJ4954HVF
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_outputs(InstanceStruct_wzIBi0AUvYWXYJ4954HVF
  *moduleInstance)
{
  ema_filter_s *myFilter;
  myFilter = (ema_filter_s *)*moduleInstance->pointer;
  cgxertCheckNullptr(moduleInstance->S, -1, -1, &b_emlrtRTEI, myFilter, 2);
  myFilter->u = moduleInstance->u0;
  cgxertCheckNullptr(moduleInstance->S, -1, -1, &c_emlrtRTEI, myFilter, 1);
  ema_filter_iter_A38TBnXKvvbX2wZzRWDdhB(myFilter);
  cgxertCheckNullptr(moduleInstance->S, -1, -1, &d_emlrtRTEI, myFilter, 2);
  *moduleInstance->b_y0 = myFilter->y;
}

static void cgxe_mdl_update(InstanceStruct_wzIBi0AUvYWXYJ4954HVF *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_derivative(InstanceStruct_wzIBi0AUvYWXYJ4954HVF
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_enable(InstanceStruct_wzIBi0AUvYWXYJ4954HVF *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_disable(InstanceStruct_wzIBi0AUvYWXYJ4954HVF
  *moduleInstance)
{
  (void)moduleInstance;
}

static void cgxe_mdl_terminate(InstanceStruct_wzIBi0AUvYWXYJ4954HVF
  *moduleInstance)
{
  (void)moduleInstance;
}

static void init_simulink_io_address(InstanceStruct_wzIBi0AUvYWXYJ4954HVF
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
static void mdlOutputs_wzIBi0AUvYWXYJ4954HVF(SimStruct *S, int_T tid)
{
  InstanceStruct_wzIBi0AUvYWXYJ4954HVF *moduleInstance =
    (InstanceStruct_wzIBi0AUvYWXYJ4954HVF *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_outputs(moduleInstance);
}

static void mdlInitialize_wzIBi0AUvYWXYJ4954HVF(SimStruct *S)
{
  InstanceStruct_wzIBi0AUvYWXYJ4954HVF *moduleInstance =
    (InstanceStruct_wzIBi0AUvYWXYJ4954HVF *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_initialize(moduleInstance);
}

static void mdlUpdate_wzIBi0AUvYWXYJ4954HVF(SimStruct *S, int_T tid)
{
  InstanceStruct_wzIBi0AUvYWXYJ4954HVF *moduleInstance =
    (InstanceStruct_wzIBi0AUvYWXYJ4954HVF *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_update(moduleInstance);
}

static void mdlDerivatives_wzIBi0AUvYWXYJ4954HVF(SimStruct *S)
{
  InstanceStruct_wzIBi0AUvYWXYJ4954HVF *moduleInstance =
    (InstanceStruct_wzIBi0AUvYWXYJ4954HVF *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_derivative(moduleInstance);
}

static void mdlTerminate_wzIBi0AUvYWXYJ4954HVF(SimStruct *S)
{
  InstanceStruct_wzIBi0AUvYWXYJ4954HVF *moduleInstance =
    (InstanceStruct_wzIBi0AUvYWXYJ4954HVF *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_terminate(moduleInstance);
  free((void *)moduleInstance);
}

static void mdlEnable_wzIBi0AUvYWXYJ4954HVF(SimStruct *S)
{
  InstanceStruct_wzIBi0AUvYWXYJ4954HVF *moduleInstance =
    (InstanceStruct_wzIBi0AUvYWXYJ4954HVF *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_enable(moduleInstance);
}

static void mdlDisable_wzIBi0AUvYWXYJ4954HVF(SimStruct *S)
{
  InstanceStruct_wzIBi0AUvYWXYJ4954HVF *moduleInstance =
    (InstanceStruct_wzIBi0AUvYWXYJ4954HVF *)cgxertGetRuntimeInstance(S);
  cgxe_mdl_disable(moduleInstance);
}

static void mdlStart_wzIBi0AUvYWXYJ4954HVF(SimStruct *S)
{
  InstanceStruct_wzIBi0AUvYWXYJ4954HVF *moduleInstance =
    (InstanceStruct_wzIBi0AUvYWXYJ4954HVF *)calloc(1, sizeof
    (InstanceStruct_wzIBi0AUvYWXYJ4954HVF));
  moduleInstance->S = S;
  cgxertSetRuntimeInstance(S, (void *)moduleInstance);
  ssSetmdlOutputs(S, mdlOutputs_wzIBi0AUvYWXYJ4954HVF);
  ssSetmdlInitializeConditions(S, mdlInitialize_wzIBi0AUvYWXYJ4954HVF);
  ssSetmdlUpdate(S, mdlUpdate_wzIBi0AUvYWXYJ4954HVF);
  ssSetmdlDerivatives(S, mdlDerivatives_wzIBi0AUvYWXYJ4954HVF);
  ssSetmdlTerminate(S, mdlTerminate_wzIBi0AUvYWXYJ4954HVF);
  ssSetmdlEnable(S, mdlEnable_wzIBi0AUvYWXYJ4954HVF);
  ssSetmdlDisable(S, mdlDisable_wzIBi0AUvYWXYJ4954HVF);
  cgxe_mdl_start(moduleInstance);

  {
    uint_T options = ssGetOptions(S);
    options |= SS_OPTION_RUNTIME_EXCEPTION_FREE_CODE;
    ssSetOptions(S, options);
  }
}

static void mdlProcessParameters_wzIBi0AUvYWXYJ4954HVF(SimStruct *S)
{
}

void method_dispatcher_wzIBi0AUvYWXYJ4954HVF(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_wzIBi0AUvYWXYJ4954HVF(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_wzIBi0AUvYWXYJ4954HVF(S);
    break;

   default:
    /* Unhandled method */
    /*
       sf_mex_error_message("Stateflow Internal Error:\n"
       "Error calling method dispatcher for module: wzIBi0AUvYWXYJ4954HVF.\n"
       "Can't handle method %d.\n", method);
     */
    break;
  }
}

mxArray *cgxe_wzIBi0AUvYWXYJ4954HVF_BuildInfoUpdate(void)
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

mxArray *cgxe_wzIBi0AUvYWXYJ4954HVF_fallback_info(void)
{
  const char* fallbackInfoFields[] = { "fallbackType", "incompatiableSymbol" };

  mxArray* fallbackInfoStruct = mxCreateStructMatrix(1, 1, 2, fallbackInfoFields);
  mxArray* fallbackType = mxCreateString("incompatibleFunction");
  mxArray* incompatibleSymbol = mxCreateString("ema_filter_init");
  mxSetFieldByNumber(fallbackInfoStruct, 0, 0, fallbackType);
  mxSetFieldByNumber(fallbackInfoStruct, 0, 1, incompatibleSymbol);
  return fallbackInfoStruct;
}
