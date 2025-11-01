/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: metux_model_6dof_only_controller_data.c
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

#include "metux_model_6dof_only_controller.h"

/* Block parameters (default storage) */
P_metux_model_6dof_only_contr_T metux_model_6dof_only_control_P = {
  /* Variable: conops
   * Referenced by:
   *   '<Root>/motor duty lookup'
   *   '<Root>/motor position demand lookup'
   *   '<Root>/pressure demand lookup'
   *   '<Root>/velocity demand lookup'
   */
  {
    {
      { 0.0, 1.0, 2.0 },

      { 0.0, 0.3, 0.3 }
    },

    {
      { 0.0, 0.095, 0.1, 1.0 },

      { 0.0, 0.0, 100.0, 100.0 }
    },

    {
      { 0.0, 0.099, 0.1, 2.0 },

      { 0.0, 0.0, 50.0, 50.0 }
    },

    {
      { 0.0, 4.0, 6.5, 10.0 },

      { 0.0, 0.0, -6.0, -10.0 }
    }
  },

  /* Variable: filter
   * Referenced by: '<Root>/Discrete FIR Filter1'
   */
  {
    { 0.05, 0.12, 0.19, 0.28, 0.19, 0.12, 0.05 },

    { 0.05, 0.12, 0.19, 0.28, 0.19, 0.12, 0.05 },

    { 0.05, 0.12, 0.19, 0.28, 0.19, 0.12, 0.05 }
  },

  /* Variable: AltitudeController
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
  {
    75.0,
    0.0,
    0.5,
    70.0,
    1.0,
    0.001,
    1.0e+15,
    -1.0e+15,
    300.0,
    -50.0
  },

  /* Variable: motorController
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
  {
    0.0,
    0.0,
    0.01,
    1.0,
    0.001,
    778.0,
    -778.0,
    1.0,
    -1.0
  },

  /* Variable: motorPositionContreller
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
  {
    0.0,
    0.0,
    0.0,
    1.0,
    0.001,
    1.0e+15,
    -1.0e+15,
    1.0,
    -1.0
  },

  /* Variable: AttitudeController
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
  {
    0.005,
    0.0,
    0.004,
    1.0,
    0.001,
    300.0,
    -300.0
  },

  /* Variable: lidar_height
   * Referenced by:
   *   '<Root>/Add Constant'
   *   '<S645>/UD'
   */
  300.0
};

/* Constant parameters (default storage) */
const ConstP_metux_model_6dof_only__T metux_model_6dof_only_co_ConstP = {
  /* Expression: [0.08 0.13 0.19 0.2 0.19 0.13 0.08]
   * Referenced by: '<S1>/Discrete FIR Filter'
   */
  { 0.08, 0.13, 0.19, 0.2, 0.19, 0.13, 0.08 }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
