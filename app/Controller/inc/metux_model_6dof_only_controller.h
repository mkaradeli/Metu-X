/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: metux_model_6dof_only_controller.h
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

#ifndef metux_model_6dof_only_controller_h_
#define metux_model_6dof_only_controller_h_
#ifndef metux_model_6dof_only_controller_COMMON_INCLUDES_
#define metux_model_6dof_only_controller_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                   /* metux_model_6dof_only_controller_COMMON_INCLUDES_ */

#include "metux_model_6dof_only_controller_types.h"
#include <stddef.h>
#include <string.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  real_T Probe[2];                     /* '<S151>/Probe' */
  real_T Probe_b[2];                   /* '<S137>/Probe' */
  real_T Probe_h[2];                   /* '<S144>/Probe' */
  real_T BaseSignal;                   /* '<S23>/Sum' */
  real_T Switch;                       /* '<S19>/Switch' */
  real_T Switch1;                      /* '<S19>/Switch1' */
  real_T Switch2;                      /* '<S19>/Switch2' */
  real_T Switch3;                      /* '<S19>/Switch3' */
  real_T Saturation;                   /* '<S205>/Saturation' */
  real_T Saturation_a;                 /* '<S259>/Saturation' */
  real_T Saturation_h;                 /* '<S313>/Saturation' */
  real_T Saturation_n;                 /* '<S367>/Saturation' */
  real_T Time;                         /* '<S10>/Time' */
  real_T ControllerMode;               /* '<S9>/Controller Mode' */
  real_T RightDuty;                    /* '<S8>/Right Duty' */
  real_T FrontDuty;                    /* '<S8>/Front Duty' */
  real_T LeftDuty;                     /* '<S8>/Left Duty' */
  real_T BackDuty;                     /* '<S8>/Back Duty' */
  real_T Saturation4;                  /* '<S1>/Saturation4' */
  real_T Saturation3;                  /* '<S1>/Saturation3' */
  real_T Saturation2;                  /* '<S1>/Saturation2' */
  real_T Saturation1;                  /* '<S1>/Saturation1' */
} B_metux_model_6dof_only_contr_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE[3];         /* '<S157>/Integrator' */
  real_T Integrator_DSTATE_m;          /* '<S143>/Integrator' */
  real_T UD_DSTATE;                    /* '<S645>/UD' */
  real_T UD_DSTATE_e;                  /* '<S7>/UD' */
  real_T DiscreteFIRFilter1_states[24];/* '<Root>/Discrete FIR Filter1' */
  real_T Integrator_DSTATE_e[3];       /* '<S150>/Integrator' */
  real_T Integrator_DSTATE_d;          /* '<S683>/Integrator' */
  real_T Filter_DSTATE;                /* '<S678>/Filter' */
  real_T Integrator_DSTATE_o;          /* '<S585>/Integrator' */
  real_T Filter_DSTATE_b;              /* '<S580>/Filter' */
  real_T Integrator_DSTATE_c;          /* '<S423>/Integrator' */
  real_T Filter_DSTATE_h;              /* '<S418>/Filter' */
  real_T Integrator_DSTATE_j;          /* '<S477>/Integrator' */
  real_T Filter_DSTATE_p;              /* '<S472>/Filter' */
  real_T Integrator_DSTATE_n;          /* '<S531>/Integrator' */
  real_T Filter_DSTATE_j;              /* '<S526>/Filter' */
  real_T Integrator_DSTATE_a;          /* '<S198>/Integrator' */
  real_T Filter_DSTATE_f;              /* '<S193>/Filter' */
  real_T Integrator_DSTATE_k;          /* '<S252>/Integrator' */
  real_T Filter_DSTATE_k;              /* '<S247>/Filter' */
  real_T Integrator_DSTATE_do;         /* '<S306>/Integrator' */
  real_T Filter_DSTATE_l;              /* '<S301>/Filter' */
  real_T Integrator_DSTATE_p;          /* '<S360>/Integrator' */
  real_T Filter_DSTATE_lz;             /* '<S355>/Filter' */
  real_T DiscreteFIRFilter_states[18]; /* '<S1>/Discrete FIR Filter' */
  real_T Integrator_DSTATE_ku;         /* '<S119>/Integrator' */
  real_T Filter_DSTATE_f2;             /* '<S114>/Filter' */
  real_T Integrator_DSTATE_ky;         /* '<S65>/Integrator' */
  real_T Filter_DSTATE_ft;             /* '<S60>/Filter' */
  real_T DiscreteFIRFilter1_simContextBu[48];/* '<Root>/Discrete FIR Filter1' */
  real_T DiscreteFIRFilter1_simRevCoeff[7];/* '<Root>/Discrete FIR Filter1' */
  real_T PrevY;                        /* '<S23>/Rate Limiter' */
  real_T PrevY_i;                      /* '<S19>/Rate Limiter' */
  real_T PrevY_m;                      /* '<S19>/Rate Limiter1' */
  real_T PrevY_a;                      /* '<S19>/Rate Limiter2' */
  real_T PrevY_g;                      /* '<S19>/Rate Limiter3' */
  real_T PrevY_n;                      /* '<S14>/Rate Limiter' */
  real_T DiscreteFIRFilter_simContextBuf[36];/* '<S1>/Discrete FIR Filter' */
  real_T DiscreteFIRFilter_simRevCoeff[7];/* '<S1>/Discrete FIR Filter' */
  int32_T DiscreteFIRFilter1_circBuf;  /* '<Root>/Discrete FIR Filter1' */
  int32_T DiscreteFIRFilter_circBuf;   /* '<S1>/Discrete FIR Filter' */
  uint32_T m_bpIndex;                  /* '<Root>/velocity demand lookup' */
  uint32_T m_bpIndex_c;                /* '<Root>/pressure demand lookup' */
  uint32_T m_bpIndex_m;              /* '<Root>/motor position demand lookup' */
  uint32_T m_bpIndex_mh;               /* '<Root>/motor duty lookup' */
  boolean_T DelayInput1_DSTATE;        /* '<S6>/Delay Input1' */
  int8_T Integrator_PrevResetState;    /* '<S157>/Integrator' */
  int8_T Integrator_PrevResetState_h;  /* '<S143>/Integrator' */
  int8_T Integrator_PrevResetState_n;  /* '<S150>/Integrator' */
  uint8_T Integrator_IC_LOADING;       /* '<S157>/Integrator' */
  uint8_T Integrator_IC_LOADING_p;     /* '<S143>/Integrator' */
  uint8_T Integrator_IC_LOADING_e;     /* '<S150>/Integrator' */
  boolean_T VerticalSpeedController_MODE;/* '<Root>/Vertical Speed Controller' */
  boolean_T PressureControllers_MODE;  /* '<Root>/Pressure Controllers' */
  boolean_T MotorPositionControllers_MODE;/* '<Root>/Motor Position Controllers' */
  boolean_T ESTOPOverride_MODE;        /* '<Root>/E-STOP Override' */
  boolean_T AttitudeController_MODE;   /* '<Root>/Attitude Controller' */
} DW_metux_model_6dof_only_cont_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: [0.08 0.13 0.19 0.2 0.19 0.13 0.08]
   * Referenced by: '<S1>/Discrete FIR Filter'
   */
  real_T DiscreteFIRFilter_Coefficients[7];
} ConstP_metux_model_6dof_only__T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T RightMotorAngle;              /* '<Root>/Right Motor Angle' */
  real_T FrontMotorAngle;              /* '<Root>/Front Motor Angle' */
  real_T LeftMotorAngle;               /* '<Root>/Left Motor Angle' */
  real_T BackMotorAngle;               /* '<Root>/Back Motor Angle' */
  real_T euler_measured[3];            /* '<Root>/euler_measured' */
  real_T height_measured;              /* '<Root>/height_measured' */
  real_T N1pressure;                   /* '<Root>/N1 pressure' */
  real_T N2pressure;                   /* '<Root>/N2 pressure' */
  real_T N3pressure;                   /* '<Root>/N3 pressure' */
  real_T N4pressure;                   /* '<Root>/N4 pressure' */
  real_T manifoldpressure;             /* '<Root>/manifold pressure' */
  boolean_T ESTOP;                     /* '<Root>/E-STOP' */
  real_T ControllerMode;               /* '<Root>/Controller Mode' */
  real_T Time;                         /* '<Root>/Time' */
  boolean_T Activate;                  /* '<Root>/Activate' */
  real_T PositionDemand;               /* '<Root>/Position Demand' */
  real_T quaternion[4];                /* '<Root>/quaternion' */
} ExtU_metux_model_6dof_only_co_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T RightDuty;                    /* '<Root>/Right Duty' */
  real_T FrontDuty;                    /* '<Root>/Front Duty' */
  real_T LeftDuty;                     /* '<Root>/Left Duty' */
  real_T BackDuty;                     /* '<Root>/Back Duty' */
  real_T PressureDemand[4];            /* '<Root>/Pressure Demand' */
  real_T VelocityMeasured;             /* '<Root>/Velocity Measured' */
  real_T height_filtered;              /* '<Root>/height_filtered' */
  real_T currentsetpoint;              /* '<Root>/current setpoint' */
  real_T eulercalculated[3];           /* '<Root>/euler calculated' */
} ExtY_metux_model_6dof_only_co_T;

/* Parameters (default storage) */
struct P_metux_model_6dof_only_contr_T_ {
  struct_2JcXGVu0Zd6X9SLlQ4vIQE conops;/* Variable: conops
                                        * Referenced by:
                                        *   '<Root>/motor duty lookup'
                                        *   '<Root>/motor position demand lookup'
                                        *   '<Root>/pressure demand lookup'
                                        *   '<Root>/velocity demand lookup'
                                        */
  struct_9RpHRXQMRnT7KIsCYzeXvE filter;/* Variable: filter
                                        * Referenced by: '<Root>/Discrete FIR Filter1'
                                        */
  struct_d4xIq0AfPJoh6823NMkJc AltitudeController;/* Variable: AltitudeController
                                                   * Referenced by:
                                                   *   '<S23>/Gain1'
                                                   *   '<S23>/Rate Limiter'
                                                   *   '<S645>/UD'
                                                   *   '<S676>/Derivative Gain'
                                                   *   '<S680>/Integral Gain'
                                                   *   '<S683>/Integrator'
                                                   *   '<S686>/Filter Coefficient'
                                                   *   '<S688>/Proportional Gain'
                                                   *   '<S690>/Saturation'
                                                   *   '<S675>/DeadZone'
                                                   */
  struct_KMH0UeGSoX5knY7MHeOm5C motorController;/* Variable: motorController
                                                 * Referenced by:
                                                 *   '<S19>/Rate Limiter'
                                                 *   '<S19>/Rate Limiter1'
                                                 *   '<S19>/Rate Limiter2'
                                                 *   '<S19>/Rate Limiter3'
                                                 *   '<S191>/Derivative Gain'
                                                 *   '<S195>/Integral Gain'
                                                 *   '<S198>/Integrator'
                                                 *   '<S201>/Filter Coefficient'
                                                 *   '<S203>/Proportional Gain'
                                                 *   '<S205>/Saturation'
                                                 *   '<S245>/Derivative Gain'
                                                 *   '<S249>/Integral Gain'
                                                 *   '<S252>/Integrator'
                                                 *   '<S255>/Filter Coefficient'
                                                 *   '<S257>/Proportional Gain'
                                                 *   '<S259>/Saturation'
                                                 *   '<S299>/Derivative Gain'
                                                 *   '<S303>/Integral Gain'
                                                 *   '<S306>/Integrator'
                                                 *   '<S309>/Filter Coefficient'
                                                 *   '<S311>/Proportional Gain'
                                                 *   '<S313>/Saturation'
                                                 *   '<S416>/Derivative Gain'
                                                 *   '<S420>/Integral Gain'
                                                 *   '<S423>/Integrator'
                                                 *   '<S426>/Filter Coefficient'
                                                 *   '<S428>/Proportional Gain'
                                                 *   '<S430>/Saturation'
                                                 *   '<S470>/Derivative Gain'
                                                 *   '<S474>/Integral Gain'
                                                 *   '<S477>/Integrator'
                                                 *   '<S480>/Filter Coefficient'
                                                 *   '<S482>/Proportional Gain'
                                                 *   '<S484>/Saturation'
                                                 *   '<S524>/Derivative Gain'
                                                 *   '<S528>/Integral Gain'
                                                 *   '<S531>/Integrator'
                                                 *   '<S534>/Filter Coefficient'
                                                 *   '<S536>/Proportional Gain'
                                                 *   '<S538>/Saturation'
                                                 *   '<S578>/Derivative Gain'
                                                 *   '<S582>/Integral Gain'
                                                 *   '<S585>/Integrator'
                                                 *   '<S588>/Filter Coefficient'
                                                 *   '<S590>/Proportional Gain'
                                                 *   '<S592>/Saturation'
                                                 *   '<S190>/DeadZone'
                                                 *   '<S244>/DeadZone'
                                                 *   '<S298>/DeadZone'
                                                 *   '<S415>/DeadZone'
                                                 *   '<S469>/DeadZone'
                                                 *   '<S523>/DeadZone'
                                                 *   '<S577>/DeadZone'
                                                 */
  struct_KMH0UeGSoX5knY7MHeOm5C motorPositionContreller;/* Variable: motorPositionContreller
                                                         * Referenced by:
                                                         *   '<S14>/Rate Limiter'
                                                         *   '<S353>/Derivative Gain'
                                                         *   '<S357>/Integral Gain'
                                                         *   '<S360>/Integrator'
                                                         *   '<S363>/Filter Coefficient'
                                                         *   '<S365>/Proportional Gain'
                                                         *   '<S367>/Saturation'
                                                         *   '<S352>/DeadZone'
                                                         */
  struct_yF8Tqw96nh68LGV1ywvzaG AttitudeController;/* Variable: AttitudeController
                                                    * Referenced by:
                                                    *   '<S1>/Saturation1'
                                                    *   '<S1>/Saturation2'
                                                    *   '<S1>/Saturation3'
                                                    *   '<S1>/Saturation4'
                                                    *   '<S58>/Derivative Gain'
                                                    *   '<S62>/Integral Gain'
                                                    *   '<S68>/Filter Coefficient'
                                                    *   '<S70>/Proportional Gain'
                                                    *   '<S72>/Saturation'
                                                    *   '<S112>/Derivative Gain'
                                                    *   '<S116>/Integral Gain'
                                                    *   '<S122>/Filter Coefficient'
                                                    *   '<S124>/Proportional Gain'
                                                    *   '<S126>/Saturation'
                                                    *   '<S57>/DeadZone'
                                                    *   '<S111>/DeadZone'
                                                    */
  real_T lidar_height;                 /* Variable: lidar_height
                                        * Referenced by:
                                        *   '<Root>/Add Constant'
                                        *   '<S645>/UD'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_metux_model_6dof_only_T {
  const char_T * volatile errorStatus;
};

/* Block parameters (default storage) */
extern P_metux_model_6dof_only_contr_T metux_model_6dof_only_control_P;

/* Block signals (default storage) */
extern B_metux_model_6dof_only_contr_T metux_model_6dof_only_control_B;

/* Block states (default storage) */
extern DW_metux_model_6dof_only_cont_T metux_model_6dof_only_contro_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_metux_model_6dof_only_co_T metux_model_6dof_only_control_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_metux_model_6dof_only_co_T metux_model_6dof_only_control_Y;

/* Constant parameters (default storage) */
extern const ConstP_metux_model_6dof_only__T metux_model_6dof_only_co_ConstP;

/* Model entry point functions */
extern void metux_model_6dof_only_controller_initialize(void);
extern void metux_model_6dof_only_controller_step(void);

/* Real-time Model object */
extern RT_MODEL_metux_model_6dof_onl_T *const metux_model_6dof_only_contro_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Pitch PID' : Unused code path elimination
 * Block '<S1>/Pitch error' : Unused code path elimination
 * Block '<S27>/Gain' : Unused code path elimination
 * Block '<S28>/Gain' : Unused code path elimination
 * Block '<S1>/Roll PID' : Unused code path elimination
 * Block '<S1>/Scope' : Unused code path elimination
 * Block '<S1>/Scope1' : Unused code path elimination
 * Block '<S1>/Scope8' : Unused code path elimination
 * Block '<S7>/Data Type Duplicate' : Unused code path elimination
 * Block '<S378>/Data Type Duplicate' : Unused code path elimination
 * Block '<S378>/Data Type Propagation' : Unused code path elimination
 * Block '<S379>/Data Type Duplicate' : Unused code path elimination
 * Block '<S379>/Data Type Propagation' : Unused code path elimination
 * Block '<S380>/Data Type Duplicate' : Unused code path elimination
 * Block '<S380>/Data Type Propagation' : Unused code path elimination
 * Block '<S381>/Data Type Duplicate' : Unused code path elimination
 * Block '<S381>/Data Type Propagation' : Unused code path elimination
 * Block '<Root>/Scope' : Unused code path elimination
 * Block '<Root>/Scope1' : Unused code path elimination
 * Block '<Root>/Scope2' : Unused code path elimination
 * Block '<Root>/Scope4' : Unused code path elimination
 * Block '<S645>/Data Type Duplicate' : Unused code path elimination
 * Block '<S22>/Scope' : Unused code path elimination
 * Block '<S22>/Scope1' : Unused code path elimination
 * Block '<S23>/Scope' : Unused code path elimination
 * Block '<S23>/pid contr' : Unused code path elimination
 * Block '<S23>/vel error' : Unused code path elimination
 * Block '<Root>/Cast To Boolean' : Eliminate redundant data type conversion
 * Block '<S143>/Saturation' : Eliminated Saturate block
 * Block '<S11>/K' : Eliminated nontunable gain of 1
 * Block '<S150>/Saturation' : Eliminated Saturate block
 * Block '<S12>/K' : Eliminated nontunable gain of 1
 * Block '<S157>/Saturation' : Eliminated Saturate block
 * Block '<S13>/K' : Eliminated nontunable gain of 1
 * Block '<S607>/Reshape' : Reshape block reduction
 * Block '<S607>/Reshape1' : Reshape block reduction
 * Block '<S607>/Reshape2' : Reshape block reduction
 * Block '<S621>/Reshape' : Reshape block reduction
 * Block '<S630>/Reshape' : Reshape block reduction
 * Block '<S641>/Reshape (9) to [3x3] column-major' : Reshape block reduction
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'metux_model_6dof_only_controller'
 * '<S1>'   : 'metux_model_6dof_only_controller/Attitude Controller'
 * '<S2>'   : 'metux_model_6dof_only_controller/Compare To Constant'
 * '<S3>'   : 'metux_model_6dof_only_controller/Compare To Constant1'
 * '<S4>'   : 'metux_model_6dof_only_controller/Compare To Constant2'
 * '<S5>'   : 'metux_model_6dof_only_controller/Compare To Constant3'
 * '<S6>'   : 'metux_model_6dof_only_controller/Detect Increase'
 * '<S7>'   : 'metux_model_6dof_only_controller/Discrete Derivative'
 * '<S8>'   : 'metux_model_6dof_only_controller/E-STOP Override'
 * '<S9>'   : 'metux_model_6dof_only_controller/Enabled Subsystem'
 * '<S10>'  : 'metux_model_6dof_only_controller/Enabled Subsystem1'
 * '<S11>'  : 'metux_model_6dof_only_controller/Low-Pass Filter (Discrete or Continuous)'
 * '<S12>'  : 'metux_model_6dof_only_controller/Low-Pass Filter (Discrete or Continuous)1'
 * '<S13>'  : 'metux_model_6dof_only_controller/Low-Pass Filter (Discrete or Continuous)2'
 * '<S14>'  : 'metux_model_6dof_only_controller/Motor Position Controllers'
 * '<S15>'  : 'metux_model_6dof_only_controller/Needle Valve Soft Limits1'
 * '<S16>'  : 'metux_model_6dof_only_controller/Needle Valve Soft Limits2'
 * '<S17>'  : 'metux_model_6dof_only_controller/Needle Valve Soft Limits3'
 * '<S18>'  : 'metux_model_6dof_only_controller/Needle Valve Soft Limits4'
 * '<S19>'  : 'metux_model_6dof_only_controller/Pressure Controllers'
 * '<S20>'  : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles'
 * '<S21>'  : 'metux_model_6dof_only_controller/Radians to Degrees'
 * '<S22>'  : 'metux_model_6dof_only_controller/Velocity Calc'
 * '<S23>'  : 'metux_model_6dof_only_controller/Vertical Speed Controller'
 * '<S24>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1'
 * '<S25>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2'
 * '<S26>'  : 'metux_model_6dof_only_controller/Attitude Controller/Radians to Degrees'
 * '<S27>'  : 'metux_model_6dof_only_controller/Attitude Controller/Radians to Degrees1'
 * '<S28>'  : 'metux_model_6dof_only_controller/Attitude Controller/Radians to Degrees2'
 * '<S29>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Anti-windup'
 * '<S30>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/D Gain'
 * '<S31>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/External Derivative'
 * '<S32>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Filter'
 * '<S33>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Filter ICs'
 * '<S34>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/I Gain'
 * '<S35>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Ideal P Gain'
 * '<S36>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Ideal P Gain Fdbk'
 * '<S37>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Integrator'
 * '<S38>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Integrator ICs'
 * '<S39>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/N Copy'
 * '<S40>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/N Gain'
 * '<S41>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/P Copy'
 * '<S42>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Parallel P Gain'
 * '<S43>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Reset Signal'
 * '<S44>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Saturation'
 * '<S45>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Saturation Fdbk'
 * '<S46>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Sum'
 * '<S47>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Sum Fdbk'
 * '<S48>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Tracking Mode'
 * '<S49>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Tracking Mode Sum'
 * '<S50>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Tsamp - Integral'
 * '<S51>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Tsamp - Ngain'
 * '<S52>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/postSat Signal'
 * '<S53>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/preInt Signal'
 * '<S54>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/preSat Signal'
 * '<S55>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Anti-windup/Disc. Clamping Parallel'
 * '<S56>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S57>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S58>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/D Gain/Internal Parameters'
 * '<S59>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/External Derivative/Error'
 * '<S60>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Filter/Disc. Forward Euler Filter'
 * '<S61>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Filter ICs/Internal IC - Filter'
 * '<S62>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/I Gain/Internal Parameters'
 * '<S63>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Ideal P Gain/Passthrough'
 * '<S64>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Ideal P Gain Fdbk/Disabled'
 * '<S65>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Integrator/Discrete'
 * '<S66>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Integrator ICs/Internal IC'
 * '<S67>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/N Copy/Disabled'
 * '<S68>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/N Gain/Internal Parameters'
 * '<S69>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/P Copy/Disabled'
 * '<S70>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Parallel P Gain/Internal Parameters'
 * '<S71>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Reset Signal/Disabled'
 * '<S72>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Saturation/Enabled'
 * '<S73>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Saturation Fdbk/Disabled'
 * '<S74>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Sum/Sum_PID'
 * '<S75>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Sum Fdbk/Disabled'
 * '<S76>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Tracking Mode/Disabled'
 * '<S77>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Tracking Mode Sum/Passthrough'
 * '<S78>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Tsamp - Integral/TsSignalSpecification'
 * '<S79>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/Tsamp - Ngain/Passthrough'
 * '<S80>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/postSat Signal/Forward_Path'
 * '<S81>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/preInt Signal/Internal PreInt'
 * '<S82>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller1/preSat Signal/Forward_Path'
 * '<S83>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Anti-windup'
 * '<S84>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/D Gain'
 * '<S85>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/External Derivative'
 * '<S86>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Filter'
 * '<S87>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Filter ICs'
 * '<S88>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/I Gain'
 * '<S89>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Ideal P Gain'
 * '<S90>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Ideal P Gain Fdbk'
 * '<S91>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Integrator'
 * '<S92>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Integrator ICs'
 * '<S93>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/N Copy'
 * '<S94>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/N Gain'
 * '<S95>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/P Copy'
 * '<S96>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Parallel P Gain'
 * '<S97>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Reset Signal'
 * '<S98>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Saturation'
 * '<S99>'  : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Saturation Fdbk'
 * '<S100>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Sum'
 * '<S101>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Sum Fdbk'
 * '<S102>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Tracking Mode'
 * '<S103>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Tracking Mode Sum'
 * '<S104>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Tsamp - Integral'
 * '<S105>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Tsamp - Ngain'
 * '<S106>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/postSat Signal'
 * '<S107>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/preInt Signal'
 * '<S108>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/preSat Signal'
 * '<S109>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Anti-windup/Disc. Clamping Parallel'
 * '<S110>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S111>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S112>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/D Gain/Internal Parameters'
 * '<S113>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/External Derivative/Error'
 * '<S114>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Filter/Disc. Forward Euler Filter'
 * '<S115>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Filter ICs/Internal IC - Filter'
 * '<S116>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/I Gain/Internal Parameters'
 * '<S117>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Ideal P Gain/Passthrough'
 * '<S118>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Ideal P Gain Fdbk/Disabled'
 * '<S119>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Integrator/Discrete'
 * '<S120>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Integrator ICs/Internal IC'
 * '<S121>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/N Copy/Disabled'
 * '<S122>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/N Gain/Internal Parameters'
 * '<S123>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/P Copy/Disabled'
 * '<S124>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Parallel P Gain/Internal Parameters'
 * '<S125>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Reset Signal/Disabled'
 * '<S126>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Saturation/Enabled'
 * '<S127>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Saturation Fdbk/Disabled'
 * '<S128>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Sum/Sum_PID'
 * '<S129>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Sum Fdbk/Disabled'
 * '<S130>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Tracking Mode/Disabled'
 * '<S131>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Tracking Mode Sum/Passthrough'
 * '<S132>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Tsamp - Integral/TsSignalSpecification'
 * '<S133>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/Tsamp - Ngain/Passthrough'
 * '<S134>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/postSat Signal/Forward_Path'
 * '<S135>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/preInt Signal/Internal PreInt'
 * '<S136>' : 'metux_model_6dof_only_controller/Attitude Controller/PID Controller2/preSat Signal/Forward_Path'
 * '<S137>' : 'metux_model_6dof_only_controller/Low-Pass Filter (Discrete or Continuous)/Enable//disable time constant'
 * '<S138>' : 'metux_model_6dof_only_controller/Low-Pass Filter (Discrete or Continuous)/Initialization'
 * '<S139>' : 'metux_model_6dof_only_controller/Low-Pass Filter (Discrete or Continuous)/Integrator (Discrete or Continuous)'
 * '<S140>' : 'metux_model_6dof_only_controller/Low-Pass Filter (Discrete or Continuous)/Enable//disable time constant/Compare To Constant'
 * '<S141>' : 'metux_model_6dof_only_controller/Low-Pass Filter (Discrete or Continuous)/Enable//disable time constant/Compare To Zero'
 * '<S142>' : 'metux_model_6dof_only_controller/Low-Pass Filter (Discrete or Continuous)/Initialization/Init_u'
 * '<S143>' : 'metux_model_6dof_only_controller/Low-Pass Filter (Discrete or Continuous)/Integrator (Discrete or Continuous)/Discrete'
 * '<S144>' : 'metux_model_6dof_only_controller/Low-Pass Filter (Discrete or Continuous)1/Enable//disable time constant'
 * '<S145>' : 'metux_model_6dof_only_controller/Low-Pass Filter (Discrete or Continuous)1/Initialization'
 * '<S146>' : 'metux_model_6dof_only_controller/Low-Pass Filter (Discrete or Continuous)1/Integrator (Discrete or Continuous)'
 * '<S147>' : 'metux_model_6dof_only_controller/Low-Pass Filter (Discrete or Continuous)1/Enable//disable time constant/Compare To Constant'
 * '<S148>' : 'metux_model_6dof_only_controller/Low-Pass Filter (Discrete or Continuous)1/Enable//disable time constant/Compare To Zero'
 * '<S149>' : 'metux_model_6dof_only_controller/Low-Pass Filter (Discrete or Continuous)1/Initialization/Init_u'
 * '<S150>' : 'metux_model_6dof_only_controller/Low-Pass Filter (Discrete or Continuous)1/Integrator (Discrete or Continuous)/Discrete'
 * '<S151>' : 'metux_model_6dof_only_controller/Low-Pass Filter (Discrete or Continuous)2/Enable//disable time constant'
 * '<S152>' : 'metux_model_6dof_only_controller/Low-Pass Filter (Discrete or Continuous)2/Initialization'
 * '<S153>' : 'metux_model_6dof_only_controller/Low-Pass Filter (Discrete or Continuous)2/Integrator (Discrete or Continuous)'
 * '<S154>' : 'metux_model_6dof_only_controller/Low-Pass Filter (Discrete or Continuous)2/Enable//disable time constant/Compare To Constant'
 * '<S155>' : 'metux_model_6dof_only_controller/Low-Pass Filter (Discrete or Continuous)2/Enable//disable time constant/Compare To Zero'
 * '<S156>' : 'metux_model_6dof_only_controller/Low-Pass Filter (Discrete or Continuous)2/Initialization/Init_u'
 * '<S157>' : 'metux_model_6dof_only_controller/Low-Pass Filter (Discrete or Continuous)2/Integrator (Discrete or Continuous)/Discrete'
 * '<S158>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1'
 * '<S159>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2'
 * '<S160>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3'
 * '<S161>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4'
 * '<S162>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Anti-windup'
 * '<S163>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/D Gain'
 * '<S164>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/External Derivative'
 * '<S165>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Filter'
 * '<S166>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Filter ICs'
 * '<S167>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/I Gain'
 * '<S168>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Ideal P Gain'
 * '<S169>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Ideal P Gain Fdbk'
 * '<S170>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Integrator'
 * '<S171>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Integrator ICs'
 * '<S172>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/N Copy'
 * '<S173>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/N Gain'
 * '<S174>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/P Copy'
 * '<S175>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Parallel P Gain'
 * '<S176>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Reset Signal'
 * '<S177>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Saturation'
 * '<S178>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Saturation Fdbk'
 * '<S179>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Sum'
 * '<S180>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Sum Fdbk'
 * '<S181>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Tracking Mode'
 * '<S182>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Tracking Mode Sum'
 * '<S183>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Tsamp - Integral'
 * '<S184>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Tsamp - Ngain'
 * '<S185>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/postSat Signal'
 * '<S186>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/preInt Signal'
 * '<S187>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/preSat Signal'
 * '<S188>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Anti-windup/Disc. Clamping Parallel'
 * '<S189>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S190>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S191>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/D Gain/Internal Parameters'
 * '<S192>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/External Derivative/Error'
 * '<S193>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Filter/Disc. Forward Euler Filter'
 * '<S194>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Filter ICs/Internal IC - Filter'
 * '<S195>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/I Gain/Internal Parameters'
 * '<S196>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Ideal P Gain/Passthrough'
 * '<S197>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Ideal P Gain Fdbk/Disabled'
 * '<S198>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Integrator/Discrete'
 * '<S199>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Integrator ICs/Internal IC'
 * '<S200>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/N Copy/Disabled'
 * '<S201>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/N Gain/Internal Parameters'
 * '<S202>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/P Copy/Disabled'
 * '<S203>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Parallel P Gain/Internal Parameters'
 * '<S204>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Reset Signal/Disabled'
 * '<S205>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Saturation/Enabled'
 * '<S206>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Saturation Fdbk/Disabled'
 * '<S207>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Sum/Sum_PID'
 * '<S208>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Sum Fdbk/Disabled'
 * '<S209>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Tracking Mode/Disabled'
 * '<S210>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Tracking Mode Sum/Passthrough'
 * '<S211>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Tsamp - Integral/TsSignalSpecification'
 * '<S212>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/Tsamp - Ngain/Passthrough'
 * '<S213>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/postSat Signal/Forward_Path'
 * '<S214>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/preInt Signal/Internal PreInt'
 * '<S215>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller1/preSat Signal/Forward_Path'
 * '<S216>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Anti-windup'
 * '<S217>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/D Gain'
 * '<S218>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/External Derivative'
 * '<S219>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Filter'
 * '<S220>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Filter ICs'
 * '<S221>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/I Gain'
 * '<S222>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Ideal P Gain'
 * '<S223>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Ideal P Gain Fdbk'
 * '<S224>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Integrator'
 * '<S225>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Integrator ICs'
 * '<S226>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/N Copy'
 * '<S227>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/N Gain'
 * '<S228>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/P Copy'
 * '<S229>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Parallel P Gain'
 * '<S230>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Reset Signal'
 * '<S231>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Saturation'
 * '<S232>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Saturation Fdbk'
 * '<S233>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Sum'
 * '<S234>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Sum Fdbk'
 * '<S235>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Tracking Mode'
 * '<S236>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Tracking Mode Sum'
 * '<S237>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Tsamp - Integral'
 * '<S238>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Tsamp - Ngain'
 * '<S239>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/postSat Signal'
 * '<S240>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/preInt Signal'
 * '<S241>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/preSat Signal'
 * '<S242>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Anti-windup/Disc. Clamping Parallel'
 * '<S243>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S244>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S245>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/D Gain/Internal Parameters'
 * '<S246>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/External Derivative/Error'
 * '<S247>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Filter/Disc. Forward Euler Filter'
 * '<S248>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Filter ICs/Internal IC - Filter'
 * '<S249>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/I Gain/Internal Parameters'
 * '<S250>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Ideal P Gain/Passthrough'
 * '<S251>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Ideal P Gain Fdbk/Disabled'
 * '<S252>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Integrator/Discrete'
 * '<S253>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Integrator ICs/Internal IC'
 * '<S254>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/N Copy/Disabled'
 * '<S255>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/N Gain/Internal Parameters'
 * '<S256>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/P Copy/Disabled'
 * '<S257>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Parallel P Gain/Internal Parameters'
 * '<S258>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Reset Signal/Disabled'
 * '<S259>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Saturation/Enabled'
 * '<S260>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Saturation Fdbk/Disabled'
 * '<S261>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Sum/Sum_PID'
 * '<S262>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Sum Fdbk/Disabled'
 * '<S263>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Tracking Mode/Disabled'
 * '<S264>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Tracking Mode Sum/Passthrough'
 * '<S265>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Tsamp - Integral/TsSignalSpecification'
 * '<S266>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/Tsamp - Ngain/Passthrough'
 * '<S267>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/postSat Signal/Forward_Path'
 * '<S268>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/preInt Signal/Internal PreInt'
 * '<S269>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller2/preSat Signal/Forward_Path'
 * '<S270>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Anti-windup'
 * '<S271>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/D Gain'
 * '<S272>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/External Derivative'
 * '<S273>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Filter'
 * '<S274>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Filter ICs'
 * '<S275>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/I Gain'
 * '<S276>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Ideal P Gain'
 * '<S277>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Ideal P Gain Fdbk'
 * '<S278>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Integrator'
 * '<S279>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Integrator ICs'
 * '<S280>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/N Copy'
 * '<S281>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/N Gain'
 * '<S282>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/P Copy'
 * '<S283>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Parallel P Gain'
 * '<S284>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Reset Signal'
 * '<S285>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Saturation'
 * '<S286>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Saturation Fdbk'
 * '<S287>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Sum'
 * '<S288>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Sum Fdbk'
 * '<S289>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Tracking Mode'
 * '<S290>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Tracking Mode Sum'
 * '<S291>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Tsamp - Integral'
 * '<S292>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Tsamp - Ngain'
 * '<S293>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/postSat Signal'
 * '<S294>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/preInt Signal'
 * '<S295>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/preSat Signal'
 * '<S296>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Anti-windup/Disc. Clamping Parallel'
 * '<S297>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S298>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S299>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/D Gain/Internal Parameters'
 * '<S300>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/External Derivative/Error'
 * '<S301>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Filter/Disc. Forward Euler Filter'
 * '<S302>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Filter ICs/Internal IC - Filter'
 * '<S303>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/I Gain/Internal Parameters'
 * '<S304>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Ideal P Gain/Passthrough'
 * '<S305>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Ideal P Gain Fdbk/Disabled'
 * '<S306>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Integrator/Discrete'
 * '<S307>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Integrator ICs/Internal IC'
 * '<S308>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/N Copy/Disabled'
 * '<S309>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/N Gain/Internal Parameters'
 * '<S310>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/P Copy/Disabled'
 * '<S311>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Parallel P Gain/Internal Parameters'
 * '<S312>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Reset Signal/Disabled'
 * '<S313>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Saturation/Enabled'
 * '<S314>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Saturation Fdbk/Disabled'
 * '<S315>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Sum/Sum_PID'
 * '<S316>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Sum Fdbk/Disabled'
 * '<S317>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Tracking Mode/Disabled'
 * '<S318>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Tracking Mode Sum/Passthrough'
 * '<S319>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Tsamp - Integral/TsSignalSpecification'
 * '<S320>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/Tsamp - Ngain/Passthrough'
 * '<S321>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/postSat Signal/Forward_Path'
 * '<S322>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/preInt Signal/Internal PreInt'
 * '<S323>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller3/preSat Signal/Forward_Path'
 * '<S324>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Anti-windup'
 * '<S325>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/D Gain'
 * '<S326>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/External Derivative'
 * '<S327>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Filter'
 * '<S328>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Filter ICs'
 * '<S329>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/I Gain'
 * '<S330>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Ideal P Gain'
 * '<S331>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Ideal P Gain Fdbk'
 * '<S332>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Integrator'
 * '<S333>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Integrator ICs'
 * '<S334>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/N Copy'
 * '<S335>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/N Gain'
 * '<S336>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/P Copy'
 * '<S337>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Parallel P Gain'
 * '<S338>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Reset Signal'
 * '<S339>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Saturation'
 * '<S340>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Saturation Fdbk'
 * '<S341>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Sum'
 * '<S342>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Sum Fdbk'
 * '<S343>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Tracking Mode'
 * '<S344>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Tracking Mode Sum'
 * '<S345>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Tsamp - Integral'
 * '<S346>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Tsamp - Ngain'
 * '<S347>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/postSat Signal'
 * '<S348>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/preInt Signal'
 * '<S349>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/preSat Signal'
 * '<S350>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Anti-windup/Disc. Clamping Parallel'
 * '<S351>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S352>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S353>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/D Gain/Internal Parameters'
 * '<S354>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/External Derivative/Error'
 * '<S355>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Filter/Disc. Forward Euler Filter'
 * '<S356>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Filter ICs/Internal IC - Filter'
 * '<S357>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/I Gain/Internal Parameters'
 * '<S358>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Ideal P Gain/Passthrough'
 * '<S359>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Ideal P Gain Fdbk/Disabled'
 * '<S360>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Integrator/Discrete'
 * '<S361>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Integrator ICs/Internal IC'
 * '<S362>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/N Copy/Disabled'
 * '<S363>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/N Gain/Internal Parameters'
 * '<S364>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/P Copy/Disabled'
 * '<S365>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Parallel P Gain/Internal Parameters'
 * '<S366>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Reset Signal/Disabled'
 * '<S367>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Saturation/Enabled'
 * '<S368>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Saturation Fdbk/Disabled'
 * '<S369>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Sum/Sum_PID'
 * '<S370>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Sum Fdbk/Disabled'
 * '<S371>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Tracking Mode/Disabled'
 * '<S372>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Tracking Mode Sum/Passthrough'
 * '<S373>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Tsamp - Integral/TsSignalSpecification'
 * '<S374>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/Tsamp - Ngain/Passthrough'
 * '<S375>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/postSat Signal/Forward_Path'
 * '<S376>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/preInt Signal/Internal PreInt'
 * '<S377>' : 'metux_model_6dof_only_controller/Motor Position Controllers/PID Controller4/preSat Signal/Forward_Path'
 * '<S378>' : 'metux_model_6dof_only_controller/Needle Valve Soft Limits1/Saturation Dynamic'
 * '<S379>' : 'metux_model_6dof_only_controller/Needle Valve Soft Limits2/Saturation Dynamic'
 * '<S380>' : 'metux_model_6dof_only_controller/Needle Valve Soft Limits3/Saturation Dynamic'
 * '<S381>' : 'metux_model_6dof_only_controller/Needle Valve Soft Limits4/Saturation Dynamic'
 * '<S382>' : 'metux_model_6dof_only_controller/Pressure Controllers/Compare To Constant'
 * '<S383>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1'
 * '<S384>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2'
 * '<S385>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3'
 * '<S386>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4'
 * '<S387>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Anti-windup'
 * '<S388>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/D Gain'
 * '<S389>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/External Derivative'
 * '<S390>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Filter'
 * '<S391>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Filter ICs'
 * '<S392>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/I Gain'
 * '<S393>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Ideal P Gain'
 * '<S394>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Ideal P Gain Fdbk'
 * '<S395>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Integrator'
 * '<S396>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Integrator ICs'
 * '<S397>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/N Copy'
 * '<S398>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/N Gain'
 * '<S399>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/P Copy'
 * '<S400>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Parallel P Gain'
 * '<S401>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Reset Signal'
 * '<S402>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Saturation'
 * '<S403>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Saturation Fdbk'
 * '<S404>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Sum'
 * '<S405>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Sum Fdbk'
 * '<S406>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Tracking Mode'
 * '<S407>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Tracking Mode Sum'
 * '<S408>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Tsamp - Integral'
 * '<S409>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Tsamp - Ngain'
 * '<S410>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/postSat Signal'
 * '<S411>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/preInt Signal'
 * '<S412>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/preSat Signal'
 * '<S413>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Anti-windup/Disc. Clamping Parallel'
 * '<S414>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S415>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S416>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/D Gain/Internal Parameters'
 * '<S417>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/External Derivative/Error'
 * '<S418>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Filter/Disc. Forward Euler Filter'
 * '<S419>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Filter ICs/Internal IC - Filter'
 * '<S420>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/I Gain/Internal Parameters'
 * '<S421>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Ideal P Gain/Passthrough'
 * '<S422>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Ideal P Gain Fdbk/Disabled'
 * '<S423>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Integrator/Discrete'
 * '<S424>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Integrator ICs/Internal IC'
 * '<S425>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/N Copy/Disabled'
 * '<S426>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/N Gain/Internal Parameters'
 * '<S427>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/P Copy/Disabled'
 * '<S428>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Parallel P Gain/Internal Parameters'
 * '<S429>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Reset Signal/Disabled'
 * '<S430>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Saturation/Enabled'
 * '<S431>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Saturation Fdbk/Disabled'
 * '<S432>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Sum/Sum_PID'
 * '<S433>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Sum Fdbk/Disabled'
 * '<S434>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Tracking Mode/Disabled'
 * '<S435>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Tracking Mode Sum/Passthrough'
 * '<S436>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Tsamp - Integral/TsSignalSpecification'
 * '<S437>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/Tsamp - Ngain/Passthrough'
 * '<S438>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/postSat Signal/Forward_Path'
 * '<S439>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/preInt Signal/Internal PreInt'
 * '<S440>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller1/preSat Signal/Forward_Path'
 * '<S441>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Anti-windup'
 * '<S442>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/D Gain'
 * '<S443>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/External Derivative'
 * '<S444>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Filter'
 * '<S445>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Filter ICs'
 * '<S446>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/I Gain'
 * '<S447>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Ideal P Gain'
 * '<S448>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Ideal P Gain Fdbk'
 * '<S449>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Integrator'
 * '<S450>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Integrator ICs'
 * '<S451>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/N Copy'
 * '<S452>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/N Gain'
 * '<S453>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/P Copy'
 * '<S454>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Parallel P Gain'
 * '<S455>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Reset Signal'
 * '<S456>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Saturation'
 * '<S457>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Saturation Fdbk'
 * '<S458>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Sum'
 * '<S459>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Sum Fdbk'
 * '<S460>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Tracking Mode'
 * '<S461>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Tracking Mode Sum'
 * '<S462>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Tsamp - Integral'
 * '<S463>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Tsamp - Ngain'
 * '<S464>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/postSat Signal'
 * '<S465>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/preInt Signal'
 * '<S466>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/preSat Signal'
 * '<S467>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Anti-windup/Disc. Clamping Parallel'
 * '<S468>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S469>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S470>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/D Gain/Internal Parameters'
 * '<S471>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/External Derivative/Error'
 * '<S472>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Filter/Disc. Forward Euler Filter'
 * '<S473>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Filter ICs/Internal IC - Filter'
 * '<S474>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/I Gain/Internal Parameters'
 * '<S475>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Ideal P Gain/Passthrough'
 * '<S476>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Ideal P Gain Fdbk/Disabled'
 * '<S477>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Integrator/Discrete'
 * '<S478>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Integrator ICs/Internal IC'
 * '<S479>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/N Copy/Disabled'
 * '<S480>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/N Gain/Internal Parameters'
 * '<S481>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/P Copy/Disabled'
 * '<S482>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Parallel P Gain/Internal Parameters'
 * '<S483>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Reset Signal/Disabled'
 * '<S484>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Saturation/Enabled'
 * '<S485>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Saturation Fdbk/Disabled'
 * '<S486>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Sum/Sum_PID'
 * '<S487>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Sum Fdbk/Disabled'
 * '<S488>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Tracking Mode/Disabled'
 * '<S489>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Tracking Mode Sum/Passthrough'
 * '<S490>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Tsamp - Integral/TsSignalSpecification'
 * '<S491>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/Tsamp - Ngain/Passthrough'
 * '<S492>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/postSat Signal/Forward_Path'
 * '<S493>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/preInt Signal/Internal PreInt'
 * '<S494>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller2/preSat Signal/Forward_Path'
 * '<S495>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Anti-windup'
 * '<S496>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/D Gain'
 * '<S497>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/External Derivative'
 * '<S498>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Filter'
 * '<S499>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Filter ICs'
 * '<S500>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/I Gain'
 * '<S501>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Ideal P Gain'
 * '<S502>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Ideal P Gain Fdbk'
 * '<S503>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Integrator'
 * '<S504>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Integrator ICs'
 * '<S505>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/N Copy'
 * '<S506>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/N Gain'
 * '<S507>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/P Copy'
 * '<S508>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Parallel P Gain'
 * '<S509>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Reset Signal'
 * '<S510>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Saturation'
 * '<S511>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Saturation Fdbk'
 * '<S512>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Sum'
 * '<S513>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Sum Fdbk'
 * '<S514>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Tracking Mode'
 * '<S515>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Tracking Mode Sum'
 * '<S516>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Tsamp - Integral'
 * '<S517>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Tsamp - Ngain'
 * '<S518>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/postSat Signal'
 * '<S519>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/preInt Signal'
 * '<S520>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/preSat Signal'
 * '<S521>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Anti-windup/Disc. Clamping Parallel'
 * '<S522>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S523>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S524>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/D Gain/Internal Parameters'
 * '<S525>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/External Derivative/Error'
 * '<S526>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Filter/Disc. Forward Euler Filter'
 * '<S527>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Filter ICs/Internal IC - Filter'
 * '<S528>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/I Gain/Internal Parameters'
 * '<S529>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Ideal P Gain/Passthrough'
 * '<S530>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Ideal P Gain Fdbk/Disabled'
 * '<S531>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Integrator/Discrete'
 * '<S532>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Integrator ICs/Internal IC'
 * '<S533>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/N Copy/Disabled'
 * '<S534>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/N Gain/Internal Parameters'
 * '<S535>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/P Copy/Disabled'
 * '<S536>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Parallel P Gain/Internal Parameters'
 * '<S537>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Reset Signal/Disabled'
 * '<S538>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Saturation/Enabled'
 * '<S539>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Saturation Fdbk/Disabled'
 * '<S540>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Sum/Sum_PID'
 * '<S541>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Sum Fdbk/Disabled'
 * '<S542>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Tracking Mode/Disabled'
 * '<S543>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Tracking Mode Sum/Passthrough'
 * '<S544>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Tsamp - Integral/TsSignalSpecification'
 * '<S545>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/Tsamp - Ngain/Passthrough'
 * '<S546>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/postSat Signal/Forward_Path'
 * '<S547>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/preInt Signal/Internal PreInt'
 * '<S548>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller3/preSat Signal/Forward_Path'
 * '<S549>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Anti-windup'
 * '<S550>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/D Gain'
 * '<S551>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/External Derivative'
 * '<S552>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Filter'
 * '<S553>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Filter ICs'
 * '<S554>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/I Gain'
 * '<S555>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Ideal P Gain'
 * '<S556>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Ideal P Gain Fdbk'
 * '<S557>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Integrator'
 * '<S558>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Integrator ICs'
 * '<S559>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/N Copy'
 * '<S560>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/N Gain'
 * '<S561>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/P Copy'
 * '<S562>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Parallel P Gain'
 * '<S563>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Reset Signal'
 * '<S564>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Saturation'
 * '<S565>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Saturation Fdbk'
 * '<S566>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Sum'
 * '<S567>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Sum Fdbk'
 * '<S568>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Tracking Mode'
 * '<S569>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Tracking Mode Sum'
 * '<S570>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Tsamp - Integral'
 * '<S571>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Tsamp - Ngain'
 * '<S572>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/postSat Signal'
 * '<S573>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/preInt Signal'
 * '<S574>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/preSat Signal'
 * '<S575>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Anti-windup/Disc. Clamping Parallel'
 * '<S576>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S577>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S578>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/D Gain/Internal Parameters'
 * '<S579>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/External Derivative/Error'
 * '<S580>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Filter/Disc. Forward Euler Filter'
 * '<S581>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Filter ICs/Internal IC - Filter'
 * '<S582>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/I Gain/Internal Parameters'
 * '<S583>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Ideal P Gain/Passthrough'
 * '<S584>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Ideal P Gain Fdbk/Disabled'
 * '<S585>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Integrator/Discrete'
 * '<S586>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Integrator ICs/Internal IC'
 * '<S587>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/N Copy/Disabled'
 * '<S588>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/N Gain/Internal Parameters'
 * '<S589>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/P Copy/Disabled'
 * '<S590>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Parallel P Gain/Internal Parameters'
 * '<S591>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Reset Signal/Disabled'
 * '<S592>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Saturation/Enabled'
 * '<S593>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Saturation Fdbk/Disabled'
 * '<S594>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Sum/Sum_PID'
 * '<S595>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Sum Fdbk/Disabled'
 * '<S596>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Tracking Mode/Disabled'
 * '<S597>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Tracking Mode Sum/Passthrough'
 * '<S598>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Tsamp - Integral/TsSignalSpecification'
 * '<S599>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/Tsamp - Ngain/Passthrough'
 * '<S600>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/postSat Signal/Forward_Path'
 * '<S601>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/preInt Signal/Internal PreInt'
 * '<S602>' : 'metux_model_6dof_only_controller/Pressure Controllers/PID Controller4/preSat Signal/Forward_Path'
 * '<S603>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Direction Cosine Matrix to Rotation Angles'
 * '<S604>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Quaternions to  Direction Cosine Matrix'
 * '<S605>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Direction Cosine Matrix to Rotation Angles/AxisRotDefault'
 * '<S606>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Direction Cosine Matrix to Rotation Angles/AxisRotZeroR3'
 * '<S607>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Direction Cosine Matrix to Rotation Angles/Get DCM Values'
 * '<S608>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Direction Cosine Matrix to Rotation Angles/Validate DCM'
 * '<S609>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Direction Cosine Matrix to Rotation Angles/AxisRotDefault/Protect asincos input'
 * '<S610>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Direction Cosine Matrix to Rotation Angles/AxisRotDefault/Protect asincos input/If Action Subsystem'
 * '<S611>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Direction Cosine Matrix to Rotation Angles/AxisRotDefault/Protect asincos input/If Action Subsystem1'
 * '<S612>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Direction Cosine Matrix to Rotation Angles/AxisRotDefault/Protect asincos input/If Action Subsystem2'
 * '<S613>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Direction Cosine Matrix to Rotation Angles/AxisRotZeroR3/Protect asincos input'
 * '<S614>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Direction Cosine Matrix to Rotation Angles/AxisRotZeroR3/Protect asincos input/If Action Subsystem'
 * '<S615>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Direction Cosine Matrix to Rotation Angles/AxisRotZeroR3/Protect asincos input/If Action Subsystem1'
 * '<S616>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Direction Cosine Matrix to Rotation Angles/AxisRotZeroR3/Protect asincos input/If Action Subsystem2'
 * '<S617>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Direction Cosine Matrix to Rotation Angles/Validate DCM/If Warning//Error'
 * '<S618>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Direction Cosine Matrix to Rotation Angles/Validate DCM/If Warning//Error/Else If Not Orthogonal'
 * '<S619>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Direction Cosine Matrix to Rotation Angles/Validate DCM/If Warning//Error/Else No Action'
 * '<S620>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Direction Cosine Matrix to Rotation Angles/Validate DCM/If Warning//Error/If Not Proper'
 * '<S621>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Direction Cosine Matrix to Rotation Angles/Validate DCM/If Warning//Error/isNotOrthogonal'
 * '<S622>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Direction Cosine Matrix to Rotation Angles/Validate DCM/If Warning//Error/isNotProper'
 * '<S623>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Direction Cosine Matrix to Rotation Angles/Validate DCM/If Warning//Error/Else If Not Orthogonal/Error'
 * '<S624>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Direction Cosine Matrix to Rotation Angles/Validate DCM/If Warning//Error/Else If Not Orthogonal/None'
 * '<S625>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Direction Cosine Matrix to Rotation Angles/Validate DCM/If Warning//Error/Else If Not Orthogonal/Warning'
 * '<S626>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Direction Cosine Matrix to Rotation Angles/Validate DCM/If Warning//Error/If Not Proper/Error'
 * '<S627>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Direction Cosine Matrix to Rotation Angles/Validate DCM/If Warning//Error/If Not Proper/None'
 * '<S628>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Direction Cosine Matrix to Rotation Angles/Validate DCM/If Warning//Error/If Not Proper/Warning'
 * '<S629>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Direction Cosine Matrix to Rotation Angles/Validate DCM/If Warning//Error/isNotOrthogonal/transpose*dcm ~= eye(3)'
 * '<S630>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Direction Cosine Matrix to Rotation Angles/Validate DCM/If Warning//Error/isNotProper/Determinant of 3x3 Matrix'
 * '<S631>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Direction Cosine Matrix to Rotation Angles/Validate DCM/If Warning//Error/isNotProper/determinant does not equal 1'
 * '<S632>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Quaternions to  Direction Cosine Matrix/A11'
 * '<S633>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Quaternions to  Direction Cosine Matrix/A12'
 * '<S634>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Quaternions to  Direction Cosine Matrix/A13'
 * '<S635>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Quaternions to  Direction Cosine Matrix/A21'
 * '<S636>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Quaternions to  Direction Cosine Matrix/A22'
 * '<S637>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Quaternions to  Direction Cosine Matrix/A23'
 * '<S638>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Quaternions to  Direction Cosine Matrix/A31'
 * '<S639>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Quaternions to  Direction Cosine Matrix/A32'
 * '<S640>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Quaternions to  Direction Cosine Matrix/A33'
 * '<S641>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Quaternions to  Direction Cosine Matrix/Create 3x3 Matrix'
 * '<S642>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Quaternions to  Direction Cosine Matrix/Quaternion Normalize'
 * '<S643>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Quaternions to  Direction Cosine Matrix/Quaternion Normalize/Quaternion Modulus'
 * '<S644>' : 'metux_model_6dof_only_controller/Quaternions to Rotation Angles/Quaternions to  Direction Cosine Matrix/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S645>' : 'metux_model_6dof_only_controller/Velocity Calc/Discrete Derivative'
 * '<S646>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2'
 * '<S647>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Anti-windup'
 * '<S648>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/D Gain'
 * '<S649>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/External Derivative'
 * '<S650>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Filter'
 * '<S651>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Filter ICs'
 * '<S652>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/I Gain'
 * '<S653>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Ideal P Gain'
 * '<S654>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Ideal P Gain Fdbk'
 * '<S655>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Integrator'
 * '<S656>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Integrator ICs'
 * '<S657>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/N Copy'
 * '<S658>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/N Gain'
 * '<S659>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/P Copy'
 * '<S660>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Parallel P Gain'
 * '<S661>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Reset Signal'
 * '<S662>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Saturation'
 * '<S663>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Saturation Fdbk'
 * '<S664>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Sum'
 * '<S665>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Sum Fdbk'
 * '<S666>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Tracking Mode'
 * '<S667>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Tracking Mode Sum'
 * '<S668>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Tsamp - Integral'
 * '<S669>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Tsamp - Ngain'
 * '<S670>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/postSat Signal'
 * '<S671>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/preInt Signal'
 * '<S672>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/preSat Signal'
 * '<S673>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Anti-windup/Disc. Clamping Parallel'
 * '<S674>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S675>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S676>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/D Gain/Internal Parameters'
 * '<S677>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/External Derivative/Error'
 * '<S678>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Filter/Disc. Forward Euler Filter'
 * '<S679>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Filter ICs/Internal IC - Filter'
 * '<S680>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/I Gain/Internal Parameters'
 * '<S681>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Ideal P Gain/Passthrough'
 * '<S682>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Ideal P Gain Fdbk/Disabled'
 * '<S683>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Integrator/Discrete'
 * '<S684>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Integrator ICs/Internal IC'
 * '<S685>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/N Copy/Disabled'
 * '<S686>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/N Gain/Internal Parameters'
 * '<S687>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/P Copy/Disabled'
 * '<S688>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Parallel P Gain/Internal Parameters'
 * '<S689>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Reset Signal/Disabled'
 * '<S690>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Saturation/Enabled'
 * '<S691>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Saturation Fdbk/Disabled'
 * '<S692>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Sum/Sum_PID'
 * '<S693>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Sum Fdbk/Disabled'
 * '<S694>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Tracking Mode/Disabled'
 * '<S695>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Tracking Mode Sum/Passthrough'
 * '<S696>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Tsamp - Integral/TsSignalSpecification'
 * '<S697>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/Tsamp - Ngain/Passthrough'
 * '<S698>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/postSat Signal/Forward_Path'
 * '<S699>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/preInt Signal/Internal PreInt'
 * '<S700>' : 'metux_model_6dof_only_controller/Vertical Speed Controller/PID Controller2/preSat Signal/Forward_Path'
 */
#endif                                 /* metux_model_6dof_only_controller_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
