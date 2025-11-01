/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: metux_model_6dof_only_controller_types.h
 *
 * Code generated for Simulink model 'metux_model_6dof_only_controller'.
 *
 * Model version                  : 3.95
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Sat Aug 23 13:17:49 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef metux_model_6dof_only_controller_types_h_
#define metux_model_6dof_only_controller_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_struct_yF8Tqw96nh68LGV1ywvzaG_
#define DEFINED_TYPEDEF_FOR_struct_yF8Tqw96nh68LGV1ywvzaG_

typedef struct {
  real_T kP;
  real_T kI;
  real_T kD;
  real_T N;
  real_T dT;
  real_T saturationMax;
  real_T saturationMin;
} struct_yF8Tqw96nh68LGV1ywvzaG;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_KMH0UeGSoX5knY7MHeOm5C_
#define DEFINED_TYPEDEF_FOR_struct_KMH0UeGSoX5knY7MHeOm5C_

typedef struct {
  real_T kP;
  real_T kI;
  real_T kD;
  real_T N;
  real_T dT;
  real_T rateLimitMax;
  real_T rateLimitMin;
  real_T saturationMax;
  real_T saturationMin;
} struct_KMH0UeGSoX5knY7MHeOm5C;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_d4xIq0AfPJoh6823NMkJc_
#define DEFINED_TYPEDEF_FOR_struct_d4xIq0AfPJoh6823NMkJc_

typedef struct {
  real_T kP;
  real_T kI;
  real_T kD;
  real_T kFF;
  real_T N;
  real_T dT;
  real_T rateLimitMax;
  real_T rateLimitMin;
  real_T saturationMax;
  real_T saturationMin;
} struct_d4xIq0AfPJoh6823NMkJc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_9RpHRXQMRnT7KIsCYzeXvE_
#define DEFINED_TYPEDEF_FOR_struct_9RpHRXQMRnT7KIsCYzeXvE_

typedef struct {
  real_T euler[7];
  real_T lidar[7];
  real_T pressure[7];
} struct_9RpHRXQMRnT7KIsCYzeXvE;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_mTH2Hjl9gp3vp6Bo3Xc0LH_
#define DEFINED_TYPEDEF_FOR_struct_mTH2Hjl9gp3vp6Bo3Xc0LH_

typedef struct {
  real_T time[3];
  real_T value[3];
} struct_mTH2Hjl9gp3vp6Bo3Xc0LH;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_rTlmvm4jPoAzjaxHa4S3EE_
#define DEFINED_TYPEDEF_FOR_struct_rTlmvm4jPoAzjaxHa4S3EE_

typedef struct {
  real_T time[4];
  real_T value[4];
} struct_rTlmvm4jPoAzjaxHa4S3EE;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_DPcEUMvQL3Fyz2RZAxZdHD_
#define DEFINED_TYPEDEF_FOR_struct_DPcEUMvQL3Fyz2RZAxZdHD_

typedef struct {
  real_T height[4];
  real_T value[4];
} struct_DPcEUMvQL3Fyz2RZAxZdHD;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_2JcXGVu0Zd6X9SLlQ4vIQE_
#define DEFINED_TYPEDEF_FOR_struct_2JcXGVu0Zd6X9SLlQ4vIQE_

typedef struct {
  struct_mTH2Hjl9gp3vp6Bo3Xc0LH motorDuty;
  struct_rTlmvm4jPoAzjaxHa4S3EE motorPosDemand;
  struct_rTlmvm4jPoAzjaxHa4S3EE PressureDemand;
  struct_DPcEUMvQL3Fyz2RZAxZdHD VelocityDemand;
} struct_2JcXGVu0Zd6X9SLlQ4vIQE;

#endif

/* Parameters (default storage) */
typedef struct P_metux_model_6dof_only_contr_T_ P_metux_model_6dof_only_contr_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_metux_model_6dof_only_T RT_MODEL_metux_model_6dof_onl_T;

#endif                           /* metux_model_6dof_only_controller_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
