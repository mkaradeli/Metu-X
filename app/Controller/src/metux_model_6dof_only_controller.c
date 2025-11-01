/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: metux_model_6dof_only_controller.c
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
#include "rtwtypes.h"
#include <math.h>
#include <string.h>
#include "metux_model_6dof_only_controller_private.h"
#define metux_model_6dof_only_co_period (0.001)

/* Block signals (default storage) */
B_metux_model_6dof_only_contr_T metux_model_6dof_only_control_B;

/* Block states (default storage) */
DW_metux_model_6dof_only_cont_T metux_model_6dof_only_contro_DW;

/* External inputs (root inport signals with default storage) */
ExtU_metux_model_6dof_only_co_T metux_model_6dof_only_control_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_metux_model_6dof_only_co_T metux_model_6dof_only_control_Y;

/* Real-time model */
static RT_MODEL_metux_model_6dof_onl_T metux_model_6dof_only_contro_M_;
RT_MODEL_metux_model_6dof_onl_T *const metux_model_6dof_only_contro_M =
  &metux_model_6dof_only_contro_M_;
real_T look1_pbinlca(real_T u0, const real_T bp0[], const real_T table[],
                     uint32_T prevIndex[], uint32_T maxIndex)
{
  real_T frac;
  real_T y;
  uint32_T bpIdx;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'on'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'on'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    bpIdx = 0U;
    frac = 0.0;
  } else if (u0 < bp0[maxIndex]) {
    uint32_T found;
    uint32_T iLeft;
    uint32_T iRght;

    /* Binary Search using Previous Index */
    bpIdx = prevIndex[0U];
    iLeft = 0U;
    iRght = maxIndex;
    found = 0U;
    while (found == 0U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx - 1U;
        bpIdx = ((bpIdx + iLeft) - 1U) >> 1U;
      } else if (u0 < bp0[bpIdx + 1U]) {
        found = 1U;
      } else {
        iLeft = bpIdx + 1U;
        bpIdx = ((bpIdx + iRght) + 1U) >> 1U;
      }
    }

    frac = (u0 - bp0[bpIdx]) / (bp0[bpIdx + 1U] - bp0[bpIdx]);
  } else {
    bpIdx = maxIndex;
    frac = 0.0;
  }

  prevIndex[0U] = bpIdx;

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'on'
     Overflow mode: 'wrapping'
   */
  if (bpIdx == maxIndex) {
    y = table[bpIdx];
  } else {
    real_T yL_0d0;
    yL_0d0 = table[bpIdx];
    y = (table[bpIdx + 1U] - yL_0d0) * frac + yL_0d0;
  }

  return y;
}

/* Model step function */
void metux_model_6dof_only_controller_step(void)
{
  real_T TmpSignalConversionAtDiscreteFI;
  real_T rtb_DeadZone;
  real_T rtb_DiscreteFIRFilter_idx_0;
  real_T rtb_Filter;
  real_T rtb_FilterCoefficient_a;
  real_T rtb_FilterCoefficient_h;
  real_T rtb_FilterCoefficient_ia;
  real_T rtb_FilterCoefficient_ih;
  real_T rtb_FilterCoefficient_j;
  real_T rtb_FilterCoefficient_pz;
  real_T rtb_Filter_j;
  real_T rtb_IntegralGain;
  real_T rtb_Product2_k;
  real_T rtb_Saturation_m;
  real_T rtb_Switch_di;
  real_T rtb_Switch_kt;
  int32_T i;
  int32_T j;
  int8_T tmp;
  int8_T tmp_0;
  boolean_T rtb_AND2;
  boolean_T rtb_FixPtRelationalOperator;
  boolean_T rtb_LogicalOperator;
  boolean_T rtb_LogicalOperator_f;

  /* Switch: '<S15>/Switch' incorporates:
   *  Inport: '<Root>/Right Motor Angle'
   */
  rtb_Product2_k = (metux_model_6dof_only_control_U.RightMotorAngle <= 1440.0);

  /* RelationalOperator: '<S6>/FixPt Relational Operator' incorporates:
   *  Inport: '<Root>/Activate'
   *  UnitDelay: '<S6>/Delay Input1'
   *
   * Block description for '<S6>/Delay Input1':
   *
   *  Store in Global RAM
   */
  rtb_FixPtRelationalOperator = ((int32_T)
    metux_model_6dof_only_control_U.Activate > (int32_T)
    metux_model_6dof_only_contro_DW.DelayInput1_DSTATE);

  /* Outputs for Enabled SubSystem: '<Root>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S9>/Activate'
   */
  if (rtb_FixPtRelationalOperator) {
    /* SignalConversion generated from: '<S9>/Controller Mode' incorporates:
     *  Inport: '<Root>/Controller Mode'
     */
    metux_model_6dof_only_control_B.ControllerMode =
      metux_model_6dof_only_control_U.ControllerMode;
  }

  /* End of Outputs for SubSystem: '<Root>/Enabled Subsystem' */

  /* Logic: '<Root>/AND2' incorporates:
   *  Constant: '<S4>/Constant'
   *  Inport: '<Root>/Activate'
   *  RelationalOperator: '<S4>/Compare'
   */
  rtb_AND2 = ((metux_model_6dof_only_control_B.ControllerMode == 1.0) &&
              metux_model_6dof_only_control_U.Activate);

  /* Outputs for Enabled SubSystem: '<Root>/Motor Position Controllers' incorporates:
   *  EnablePort: '<S14>/Enable'
   */
  if (rtb_AND2) {
    metux_model_6dof_only_contro_DW.MotorPositionControllers_MODE = true;

    /* RateLimiter: '<S14>/Rate Limiter' incorporates:
     *  Inport: '<Root>/Position Demand'
     */
    rtb_FilterCoefficient_ih = metux_model_6dof_only_control_U.PositionDemand -
      metux_model_6dof_only_contro_DW.PrevY_n;
    rtb_Saturation_m =
      metux_model_6dof_only_control_P.motorPositionContreller.rateLimitMax *
      metux_model_6dof_only_co_period;
    if (rtb_FilterCoefficient_ih > rtb_Saturation_m) {
      rtb_Saturation_m += metux_model_6dof_only_contro_DW.PrevY_n;
    } else {
      rtb_Saturation_m =
        metux_model_6dof_only_control_P.motorPositionContreller.rateLimitMin *
        metux_model_6dof_only_co_period;
      if (rtb_FilterCoefficient_ih < rtb_Saturation_m) {
        rtb_Saturation_m += metux_model_6dof_only_contro_DW.PrevY_n;
      } else {
        rtb_Saturation_m = metux_model_6dof_only_control_U.PositionDemand;
      }
    }

    metux_model_6dof_only_contro_DW.PrevY_n = rtb_Saturation_m;

    /* End of RateLimiter: '<S14>/Rate Limiter' */

    /* Sum: '<S14>/Sum1' incorporates:
     *  Inport: '<Root>/Front Motor Angle'
     */
    rtb_DeadZone = rtb_Saturation_m -
      metux_model_6dof_only_control_U.FrontMotorAngle;

    /* Gain: '<S201>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S193>/Filter'
     *  Gain: '<S191>/Derivative Gain'
     *  Sum: '<S193>/SumD'
     */
    rtb_FilterCoefficient_j =
      (metux_model_6dof_only_control_P.motorController.kD * rtb_DeadZone -
       metux_model_6dof_only_contro_DW.Filter_DSTATE_f) *
      metux_model_6dof_only_control_P.motorController.N;

    /* Sum: '<S207>/Sum' incorporates:
     *  DiscreteIntegrator: '<S198>/Integrator'
     *  Gain: '<S203>/Proportional Gain'
     */
    rtb_Filter = (metux_model_6dof_only_control_P.motorController.kP *
                  rtb_DeadZone +
                  metux_model_6dof_only_contro_DW.Integrator_DSTATE_a) +
      rtb_FilterCoefficient_j;

    /* Saturate: '<S205>/Saturation' incorporates:
     *  DeadZone: '<S190>/DeadZone'
     */
    if (rtb_Filter >
        metux_model_6dof_only_control_P.motorController.saturationMax) {
      /* Saturate: '<S205>/Saturation' */
      metux_model_6dof_only_control_B.Saturation =
        metux_model_6dof_only_control_P.motorController.saturationMax;
      rtb_Filter -=
        metux_model_6dof_only_control_P.motorController.saturationMax;
    } else {
      if (rtb_Filter <
          metux_model_6dof_only_control_P.motorController.saturationMin) {
        /* Saturate: '<S205>/Saturation' */
        metux_model_6dof_only_control_B.Saturation =
          metux_model_6dof_only_control_P.motorController.saturationMin;
      } else {
        /* Saturate: '<S205>/Saturation' */
        metux_model_6dof_only_control_B.Saturation = rtb_Filter;
      }

      if (rtb_Filter >=
          metux_model_6dof_only_control_P.motorController.saturationMin) {
        rtb_Filter = 0.0;
      } else {
        rtb_Filter -=
          metux_model_6dof_only_control_P.motorController.saturationMin;
      }
    }

    /* End of Saturate: '<S205>/Saturation' */

    /* Gain: '<S195>/Integral Gain' */
    rtb_DeadZone *= metux_model_6dof_only_control_P.motorController.kI;

    /* Switch: '<S188>/Switch1' incorporates:
     *  Constant: '<S188>/Clamping_zero'
     *  Constant: '<S188>/Constant'
     *  Constant: '<S188>/Constant2'
     *  RelationalOperator: '<S188>/fix for DT propagation issue'
     */
    if (rtb_Filter > 0.0) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    /* Switch: '<S188>/Switch2' incorporates:
     *  Constant: '<S188>/Clamping_zero'
     *  Constant: '<S188>/Constant3'
     *  Constant: '<S188>/Constant4'
     *  RelationalOperator: '<S188>/fix for DT propagation issue1'
     */
    if (rtb_DeadZone > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    /* Switch: '<S188>/Switch' incorporates:
     *  Constant: '<S188>/Clamping_zero'
     *  Constant: '<S188>/Constant1'
     *  Logic: '<S188>/AND3'
     *  RelationalOperator: '<S188>/Equal1'
     *  RelationalOperator: '<S188>/Relational Operator'
     *  Switch: '<S188>/Switch1'
     *  Switch: '<S188>/Switch2'
     */
    if ((rtb_Filter != 0.0) && (tmp == tmp_0)) {
      rtb_Switch_kt = 0.0;
    } else {
      rtb_Switch_kt = rtb_DeadZone;
    }

    /* End of Switch: '<S188>/Switch' */

    /* Sum: '<S14>/Sum2' incorporates:
     *  Inport: '<Root>/Left Motor Angle'
     */
    rtb_DeadZone = rtb_Saturation_m -
      metux_model_6dof_only_control_U.LeftMotorAngle;

    /* Gain: '<S255>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S247>/Filter'
     *  Gain: '<S245>/Derivative Gain'
     *  Sum: '<S247>/SumD'
     */
    rtb_FilterCoefficient_h =
      (metux_model_6dof_only_control_P.motorController.kD * rtb_DeadZone -
       metux_model_6dof_only_contro_DW.Filter_DSTATE_k) *
      metux_model_6dof_only_control_P.motorController.N;

    /* Sum: '<S261>/Sum' incorporates:
     *  DiscreteIntegrator: '<S252>/Integrator'
     *  Gain: '<S257>/Proportional Gain'
     */
    rtb_Filter_j = (metux_model_6dof_only_control_P.motorController.kP *
                    rtb_DeadZone +
                    metux_model_6dof_only_contro_DW.Integrator_DSTATE_k) +
      rtb_FilterCoefficient_h;

    /* Saturate: '<S259>/Saturation' incorporates:
     *  DeadZone: '<S244>/DeadZone'
     */
    if (rtb_Filter_j >
        metux_model_6dof_only_control_P.motorController.saturationMax) {
      /* Saturate: '<S259>/Saturation' */
      metux_model_6dof_only_control_B.Saturation_a =
        metux_model_6dof_only_control_P.motorController.saturationMax;
      rtb_Filter_j -=
        metux_model_6dof_only_control_P.motorController.saturationMax;
    } else {
      if (rtb_Filter_j <
          metux_model_6dof_only_control_P.motorController.saturationMin) {
        /* Saturate: '<S259>/Saturation' */
        metux_model_6dof_only_control_B.Saturation_a =
          metux_model_6dof_only_control_P.motorController.saturationMin;
      } else {
        /* Saturate: '<S259>/Saturation' */
        metux_model_6dof_only_control_B.Saturation_a = rtb_Filter_j;
      }

      if (rtb_Filter_j >=
          metux_model_6dof_only_control_P.motorController.saturationMin) {
        rtb_Filter_j = 0.0;
      } else {
        rtb_Filter_j -=
          metux_model_6dof_only_control_P.motorController.saturationMin;
      }
    }

    /* End of Saturate: '<S259>/Saturation' */

    /* Gain: '<S249>/Integral Gain' */
    rtb_DeadZone *= metux_model_6dof_only_control_P.motorController.kI;

    /* Switch: '<S242>/Switch1' incorporates:
     *  Constant: '<S242>/Clamping_zero'
     *  Constant: '<S242>/Constant'
     *  Constant: '<S242>/Constant2'
     *  RelationalOperator: '<S242>/fix for DT propagation issue'
     */
    if (rtb_Filter_j > 0.0) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    /* Switch: '<S242>/Switch2' incorporates:
     *  Constant: '<S242>/Clamping_zero'
     *  Constant: '<S242>/Constant3'
     *  Constant: '<S242>/Constant4'
     *  RelationalOperator: '<S242>/fix for DT propagation issue1'
     */
    if (rtb_DeadZone > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    /* Switch: '<S242>/Switch' incorporates:
     *  Constant: '<S242>/Clamping_zero'
     *  Constant: '<S242>/Constant1'
     *  Logic: '<S242>/AND3'
     *  RelationalOperator: '<S242>/Equal1'
     *  RelationalOperator: '<S242>/Relational Operator'
     *  Switch: '<S242>/Switch1'
     *  Switch: '<S242>/Switch2'
     */
    if ((rtb_Filter_j != 0.0) && (tmp == tmp_0)) {
      rtb_Switch_di = 0.0;
    } else {
      rtb_Switch_di = rtb_DeadZone;
    }

    /* End of Switch: '<S242>/Switch' */

    /* Sum: '<S14>/Sum3' incorporates:
     *  Inport: '<Root>/Back Motor Angle'
     */
    rtb_DeadZone = rtb_Saturation_m -
      metux_model_6dof_only_control_U.BackMotorAngle;

    /* Gain: '<S309>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S301>/Filter'
     *  Gain: '<S299>/Derivative Gain'
     *  Sum: '<S301>/SumD'
     */
    rtb_FilterCoefficient_pz =
      (metux_model_6dof_only_control_P.motorController.kD * rtb_DeadZone -
       metux_model_6dof_only_contro_DW.Filter_DSTATE_l) *
      metux_model_6dof_only_control_P.motorController.N;

    /* Sum: '<S315>/Sum' incorporates:
     *  DiscreteIntegrator: '<S306>/Integrator'
     *  Gain: '<S311>/Proportional Gain'
     */
    rtb_Filter_j = (metux_model_6dof_only_control_P.motorController.kP *
                    rtb_DeadZone +
                    metux_model_6dof_only_contro_DW.Integrator_DSTATE_do) +
      rtb_FilterCoefficient_pz;

    /* Saturate: '<S313>/Saturation' incorporates:
     *  DeadZone: '<S298>/DeadZone'
     */
    if (rtb_Filter_j >
        metux_model_6dof_only_control_P.motorController.saturationMax) {
      /* Saturate: '<S313>/Saturation' */
      metux_model_6dof_only_control_B.Saturation_h =
        metux_model_6dof_only_control_P.motorController.saturationMax;
      rtb_Filter_j -=
        metux_model_6dof_only_control_P.motorController.saturationMax;
    } else {
      if (rtb_Filter_j <
          metux_model_6dof_only_control_P.motorController.saturationMin) {
        /* Saturate: '<S313>/Saturation' */
        metux_model_6dof_only_control_B.Saturation_h =
          metux_model_6dof_only_control_P.motorController.saturationMin;
      } else {
        /* Saturate: '<S313>/Saturation' */
        metux_model_6dof_only_control_B.Saturation_h = rtb_Filter_j;
      }

      if (rtb_Filter_j >=
          metux_model_6dof_only_control_P.motorController.saturationMin) {
        rtb_Filter_j = 0.0;
      } else {
        rtb_Filter_j -=
          metux_model_6dof_only_control_P.motorController.saturationMin;
      }
    }

    /* End of Saturate: '<S313>/Saturation' */

    /* Gain: '<S303>/Integral Gain' */
    rtb_DeadZone *= metux_model_6dof_only_control_P.motorController.kI;

    /* Sum: '<S14>/Sum' incorporates:
     *  Inport: '<Root>/Right Motor Angle'
     */
    rtb_Saturation_m -= metux_model_6dof_only_control_U.RightMotorAngle;

    /* Gain: '<S363>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S355>/Filter'
     *  Gain: '<S353>/Derivative Gain'
     *  Sum: '<S355>/SumD'
     */
    rtb_FilterCoefficient_ih =
      (metux_model_6dof_only_control_P.motorPositionContreller.kD *
       rtb_Saturation_m - metux_model_6dof_only_contro_DW.Filter_DSTATE_lz) *
      metux_model_6dof_only_control_P.motorPositionContreller.N;

    /* Sum: '<S369>/Sum' incorporates:
     *  DiscreteIntegrator: '<S360>/Integrator'
     *  Gain: '<S365>/Proportional Gain'
     */
    rtb_Filter = (metux_model_6dof_only_control_P.motorPositionContreller.kP *
                  rtb_Saturation_m +
                  metux_model_6dof_only_contro_DW.Integrator_DSTATE_p) +
      rtb_FilterCoefficient_ih;

    /* Saturate: '<S367>/Saturation' incorporates:
     *  DeadZone: '<S352>/DeadZone'
     */
    if (rtb_Filter >
        metux_model_6dof_only_control_P.motorPositionContreller.saturationMax) {
      /* Saturate: '<S367>/Saturation' */
      metux_model_6dof_only_control_B.Saturation_n =
        metux_model_6dof_only_control_P.motorPositionContreller.saturationMax;
      rtb_Filter -=
        metux_model_6dof_only_control_P.motorPositionContreller.saturationMax;
    } else {
      if (rtb_Filter <
          metux_model_6dof_only_control_P.motorPositionContreller.saturationMin)
      {
        /* Saturate: '<S367>/Saturation' */
        metux_model_6dof_only_control_B.Saturation_n =
          metux_model_6dof_only_control_P.motorPositionContreller.saturationMin;
      } else {
        /* Saturate: '<S367>/Saturation' */
        metux_model_6dof_only_control_B.Saturation_n = rtb_Filter;
      }

      if (rtb_Filter >=
          metux_model_6dof_only_control_P.motorPositionContreller.saturationMin)
      {
        rtb_Filter = 0.0;
      } else {
        rtb_Filter -=
          metux_model_6dof_only_control_P.motorPositionContreller.saturationMin;
      }
    }

    /* End of Saturate: '<S367>/Saturation' */

    /* Gain: '<S357>/Integral Gain' */
    rtb_Saturation_m *=
      metux_model_6dof_only_control_P.motorPositionContreller.kI;

    /* Update for DiscreteIntegrator: '<S198>/Integrator' */
    metux_model_6dof_only_contro_DW.Integrator_DSTATE_a += 0.001 * rtb_Switch_kt;
    if (metux_model_6dof_only_contro_DW.Integrator_DSTATE_a >
        metux_model_6dof_only_control_P.motorController.saturationMax) {
      metux_model_6dof_only_contro_DW.Integrator_DSTATE_a =
        metux_model_6dof_only_control_P.motorController.saturationMax;
    } else if (metux_model_6dof_only_contro_DW.Integrator_DSTATE_a <
               metux_model_6dof_only_control_P.motorController.saturationMin) {
      metux_model_6dof_only_contro_DW.Integrator_DSTATE_a =
        metux_model_6dof_only_control_P.motorController.saturationMin;
    }

    /* End of Update for DiscreteIntegrator: '<S198>/Integrator' */

    /* Update for DiscreteIntegrator: '<S193>/Filter' */
    metux_model_6dof_only_contro_DW.Filter_DSTATE_f += 0.001 *
      rtb_FilterCoefficient_j;

    /* Update for DiscreteIntegrator: '<S252>/Integrator' */
    metux_model_6dof_only_contro_DW.Integrator_DSTATE_k += 0.001 * rtb_Switch_di;
    if (metux_model_6dof_only_contro_DW.Integrator_DSTATE_k >
        metux_model_6dof_only_control_P.motorController.saturationMax) {
      metux_model_6dof_only_contro_DW.Integrator_DSTATE_k =
        metux_model_6dof_only_control_P.motorController.saturationMax;
    } else if (metux_model_6dof_only_contro_DW.Integrator_DSTATE_k <
               metux_model_6dof_only_control_P.motorController.saturationMin) {
      metux_model_6dof_only_contro_DW.Integrator_DSTATE_k =
        metux_model_6dof_only_control_P.motorController.saturationMin;
    }

    /* End of Update for DiscreteIntegrator: '<S252>/Integrator' */

    /* Update for DiscreteIntegrator: '<S247>/Filter' */
    metux_model_6dof_only_contro_DW.Filter_DSTATE_k += 0.001 *
      rtb_FilterCoefficient_h;

    /* Switch: '<S296>/Switch1' incorporates:
     *  Constant: '<S296>/Clamping_zero'
     *  Constant: '<S296>/Constant'
     *  Constant: '<S296>/Constant2'
     *  RelationalOperator: '<S296>/fix for DT propagation issue'
     */
    if (rtb_Filter_j > 0.0) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    /* Switch: '<S296>/Switch2' incorporates:
     *  Constant: '<S296>/Clamping_zero'
     *  Constant: '<S296>/Constant3'
     *  Constant: '<S296>/Constant4'
     *  RelationalOperator: '<S296>/fix for DT propagation issue1'
     */
    if (rtb_DeadZone > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    /* Switch: '<S296>/Switch' incorporates:
     *  Constant: '<S296>/Clamping_zero'
     *  Constant: '<S296>/Constant1'
     *  Logic: '<S296>/AND3'
     *  RelationalOperator: '<S296>/Equal1'
     *  RelationalOperator: '<S296>/Relational Operator'
     *  Switch: '<S296>/Switch1'
     *  Switch: '<S296>/Switch2'
     */
    if ((rtb_Filter_j != 0.0) && (tmp == tmp_0)) {
      rtb_DeadZone = 0.0;
    }

    /* Update for DiscreteIntegrator: '<S306>/Integrator' incorporates:
     *  Switch: '<S296>/Switch'
     */
    metux_model_6dof_only_contro_DW.Integrator_DSTATE_do += 0.001 * rtb_DeadZone;
    if (metux_model_6dof_only_contro_DW.Integrator_DSTATE_do >
        metux_model_6dof_only_control_P.motorController.saturationMax) {
      metux_model_6dof_only_contro_DW.Integrator_DSTATE_do =
        metux_model_6dof_only_control_P.motorController.saturationMax;
    } else if (metux_model_6dof_only_contro_DW.Integrator_DSTATE_do <
               metux_model_6dof_only_control_P.motorController.saturationMin) {
      metux_model_6dof_only_contro_DW.Integrator_DSTATE_do =
        metux_model_6dof_only_control_P.motorController.saturationMin;
    }

    /* End of Update for DiscreteIntegrator: '<S306>/Integrator' */

    /* Update for DiscreteIntegrator: '<S301>/Filter' */
    metux_model_6dof_only_contro_DW.Filter_DSTATE_l += 0.001 *
      rtb_FilterCoefficient_pz;

    /* Switch: '<S350>/Switch1' incorporates:
     *  Constant: '<S350>/Clamping_zero'
     *  Constant: '<S350>/Constant'
     *  Constant: '<S350>/Constant2'
     *  RelationalOperator: '<S350>/fix for DT propagation issue'
     */
    if (rtb_Filter > 0.0) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    /* Switch: '<S350>/Switch2' incorporates:
     *  Constant: '<S350>/Clamping_zero'
     *  Constant: '<S350>/Constant3'
     *  Constant: '<S350>/Constant4'
     *  RelationalOperator: '<S350>/fix for DT propagation issue1'
     */
    if (rtb_Saturation_m > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    /* Switch: '<S350>/Switch' incorporates:
     *  Constant: '<S350>/Clamping_zero'
     *  Constant: '<S350>/Constant1'
     *  Logic: '<S350>/AND3'
     *  RelationalOperator: '<S350>/Equal1'
     *  RelationalOperator: '<S350>/Relational Operator'
     *  Switch: '<S350>/Switch1'
     *  Switch: '<S350>/Switch2'
     */
    if ((rtb_Filter != 0.0) && (tmp == tmp_0)) {
      rtb_Saturation_m = 0.0;
    }

    /* Update for DiscreteIntegrator: '<S360>/Integrator' incorporates:
     *  Switch: '<S350>/Switch'
     */
    metux_model_6dof_only_contro_DW.Integrator_DSTATE_p += 0.001 *
      rtb_Saturation_m;
    if (metux_model_6dof_only_contro_DW.Integrator_DSTATE_p >
        metux_model_6dof_only_control_P.motorPositionContreller.saturationMax) {
      metux_model_6dof_only_contro_DW.Integrator_DSTATE_p =
        metux_model_6dof_only_control_P.motorPositionContreller.saturationMax;
    } else if (metux_model_6dof_only_contro_DW.Integrator_DSTATE_p <
               metux_model_6dof_only_control_P.motorPositionContreller.saturationMin)
    {
      metux_model_6dof_only_contro_DW.Integrator_DSTATE_p =
        metux_model_6dof_only_control_P.motorPositionContreller.saturationMin;
    }

    /* End of Update for DiscreteIntegrator: '<S360>/Integrator' */

    /* Update for DiscreteIntegrator: '<S355>/Filter' */
    metux_model_6dof_only_contro_DW.Filter_DSTATE_lz += 0.001 *
      rtb_FilterCoefficient_ih;
  } else if (metux_model_6dof_only_contro_DW.MotorPositionControllers_MODE) {
    /* Disable for Saturate: '<S367>/Saturation' incorporates:
     *  Outport: '<S14>/Right Duty'
     */
    metux_model_6dof_only_control_B.Saturation_n = 0.0;

    /* Disable for Saturate: '<S205>/Saturation' incorporates:
     *  Outport: '<S14>/Front Duty'
     */
    metux_model_6dof_only_control_B.Saturation = 0.0;

    /* Disable for Saturate: '<S259>/Saturation' incorporates:
     *  Outport: '<S14>/Left Duty'
     */
    metux_model_6dof_only_control_B.Saturation_a = 0.0;

    /* Disable for Saturate: '<S313>/Saturation' incorporates:
     *  Outport: '<S14>/Back Duty'
     */
    metux_model_6dof_only_control_B.Saturation_h = 0.0;
    metux_model_6dof_only_contro_DW.MotorPositionControllers_MODE = false;
  }

  /* End of Outputs for SubSystem: '<Root>/Motor Position Controllers' */

  /* Logic: '<S151>/Logical Operator' incorporates:
   *  Constant: '<S151>/Time constant'
   *  Constant: '<S155>/Constant'
   *  RelationalOperator: '<S155>/Compare'
   *  Sum: '<S151>/Sum1'
   */
  rtb_LogicalOperator = (0.02 - metux_model_6dof_only_control_B.Probe[0] <= 0.0);

  /* DiscreteIntegrator: '<S157>/Integrator' incorporates:
   *  Inport: '<Root>/euler_measured'
   */
  if (metux_model_6dof_only_contro_DW.Integrator_IC_LOADING != 0) {
    metux_model_6dof_only_contro_DW.Integrator_DSTATE[0] =
      metux_model_6dof_only_control_U.euler_measured[0];
    metux_model_6dof_only_contro_DW.Integrator_DSTATE[1] =
      metux_model_6dof_only_control_U.euler_measured[1];
    metux_model_6dof_only_contro_DW.Integrator_DSTATE[2] =
      metux_model_6dof_only_control_U.euler_measured[2];
  }

  if (rtb_LogicalOperator ||
      (metux_model_6dof_only_contro_DW.Integrator_PrevResetState != 0)) {
    metux_model_6dof_only_contro_DW.Integrator_DSTATE[0] =
      metux_model_6dof_only_control_U.euler_measured[0];
    metux_model_6dof_only_contro_DW.Integrator_DSTATE[1] =
      metux_model_6dof_only_control_U.euler_measured[1];
    metux_model_6dof_only_contro_DW.Integrator_DSTATE[2] =
      metux_model_6dof_only_control_U.euler_measured[2];
  }

  /* Logic: '<S137>/Logical Operator' incorporates:
   *  Constant: '<S137>/Time constant'
   *  Constant: '<S141>/Constant'
   *  RelationalOperator: '<S141>/Compare'
   *  Sum: '<S137>/Sum1'
   */
  rtb_LogicalOperator_f = (0.02 - metux_model_6dof_only_control_B.Probe_b[0] <=
    0.0);

  /* Gain: '<Root>/Gain' incorporates:
   *  Bias: '<Root>/Add Constant'
   *  Inport: '<Root>/height_measured'
   */
  rtb_FilterCoefficient_j = (metux_model_6dof_only_control_U.height_measured -
    metux_model_6dof_only_control_P.lidar_height) * 0.001;

  /* DiscreteIntegrator: '<S143>/Integrator' */
  if (metux_model_6dof_only_contro_DW.Integrator_IC_LOADING_p != 0) {
    metux_model_6dof_only_contro_DW.Integrator_DSTATE_m =
      rtb_FilterCoefficient_j;
  }

  if (rtb_LogicalOperator_f ||
      (metux_model_6dof_only_contro_DW.Integrator_PrevResetState_h != 0)) {
    metux_model_6dof_only_contro_DW.Integrator_DSTATE_m =
      rtb_FilterCoefficient_j;
  }

  /* SampleTimeMath: '<S645>/TSamp' incorporates:
   *  DiscreteIntegrator: '<S143>/Integrator'
   *  DiscreteIntegrator: '<S157>/Integrator'
   *  Product: '<S22>/Product'
   *  Trigonometry: '<S22>/Cos2'
   *
   * About '<S645>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_Switch_kt = cos(metux_model_6dof_only_contro_DW.Integrator_DSTATE[0]) *
    cos(metux_model_6dof_only_contro_DW.Integrator_DSTATE[1]) *
    metux_model_6dof_only_contro_DW.Integrator_DSTATE_m * 1000.0;

  /* Sum: '<S645>/Diff' incorporates:
   *  UnitDelay: '<S645>/UD'
   *
   * Block description for '<S645>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S645>/UD':
   *
   *  Store in Global RAM
   */
  metux_model_6dof_only_control_Y.VelocityMeasured = rtb_Switch_kt -
    metux_model_6dof_only_contro_DW.UD_DSTATE;

  /* Outputs for Enabled SubSystem: '<Root>/Enabled Subsystem1' incorporates:
   *  EnablePort: '<S10>/Enable'
   */
  if (rtb_FixPtRelationalOperator) {
    /* SignalConversion generated from: '<S10>/Time' incorporates:
     *  Inport: '<Root>/Time'
     */
    metux_model_6dof_only_control_B.Time = metux_model_6dof_only_control_U.Time;
  }

  /* End of Outputs for SubSystem: '<Root>/Enabled Subsystem1' */

  /* Sum: '<Root>/Sum1' incorporates:
   *  Inport: '<Root>/Time'
   */
  rtb_Filter_j = metux_model_6dof_only_control_U.Time -
    metux_model_6dof_only_control_B.Time;

  /* Lookup_n-D: '<Root>/velocity demand lookup' incorporates:
   *  DiscreteIntegrator: '<S143>/Integrator'
   */
  rtb_FilterCoefficient_h = look1_pbinlca
    (metux_model_6dof_only_contro_DW.Integrator_DSTATE_m,
     metux_model_6dof_only_control_P.conops.VelocityDemand.height,
     metux_model_6dof_only_control_P.conops.VelocityDemand.value,
     &metux_model_6dof_only_contro_DW.m_bpIndex, 3U);

  /* MultiPortSwitch: '<Root>/Multiport Switch' */
  switch ((int32_T)metux_model_6dof_only_control_B.ControllerMode) {
   case 0:
    /* MultiPortSwitch: '<Root>/Multiport Switch' incorporates:
     *  Lookup_n-D: '<Root>/motor duty lookup'
     *  Sum: '<Root>/Sum1'
     */
    metux_model_6dof_only_control_Y.currentsetpoint = look1_pbinlca(rtb_Filter_j,
      metux_model_6dof_only_control_P.conops.motorDuty.time,
      metux_model_6dof_only_control_P.conops.motorDuty.value,
      &metux_model_6dof_only_contro_DW.m_bpIndex_mh, 2U);
    break;

   case 1:
    /* MultiPortSwitch: '<Root>/Multiport Switch' incorporates:
     *  Lookup_n-D: '<Root>/motor position demand lookup'
     *  Sum: '<Root>/Sum1'
     */
    metux_model_6dof_only_control_Y.currentsetpoint = look1_pbinlca(rtb_Filter_j,
      metux_model_6dof_only_control_P.conops.motorPosDemand.time,
      metux_model_6dof_only_control_P.conops.motorPosDemand.value,
      &metux_model_6dof_only_contro_DW.m_bpIndex_m, 3U);
    break;

   case 2:
    /* MultiPortSwitch: '<Root>/Multiport Switch' incorporates:
     *  Lookup_n-D: '<Root>/pressure demand lookup'
     *  Sum: '<Root>/Sum1'
     */
    metux_model_6dof_only_control_Y.currentsetpoint = look1_pbinlca(rtb_Filter_j,
      metux_model_6dof_only_control_P.conops.PressureDemand.time,
      metux_model_6dof_only_control_P.conops.PressureDemand.value,
      &metux_model_6dof_only_contro_DW.m_bpIndex_c, 3U);
    break;

   case 4:
   case 5:
    /* MultiPortSwitch: '<Root>/Multiport Switch' */
    metux_model_6dof_only_control_Y.currentsetpoint = rtb_FilterCoefficient_h;
    break;

   default:
    /* MultiPortSwitch: '<Root>/Multiport Switch' incorporates:
     *  Constant: '<Root>/Constant'
     */
    metux_model_6dof_only_control_Y.currentsetpoint = 0.0;
    break;
  }

  /* End of MultiPortSwitch: '<Root>/Multiport Switch' */

  /* SampleTimeMath: '<S7>/TSamp'
   *
   * About '<S7>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_FilterCoefficient_h *= 1000.0;

  /* Outputs for Enabled SubSystem: '<Root>/Vertical Speed Controller' incorporates:
   *  EnablePort: '<S23>/Enable'
   */
  /* Logic: '<Root>/AND' incorporates:
   *  Constant: '<S5>/Constant'
   *  Inport: '<Root>/Activate'
   *  RelationalOperator: '<S5>/Compare'
   */
  if ((metux_model_6dof_only_control_B.ControllerMode >= 4.0) &&
      metux_model_6dof_only_control_U.Activate) {
    if (!metux_model_6dof_only_contro_DW.VerticalSpeedController_MODE) {
      /* InitializeConditions for RateLimiter: '<S23>/Rate Limiter' */
      metux_model_6dof_only_contro_DW.PrevY = 0.0;

      /* InitializeConditions for DiscreteIntegrator: '<S683>/Integrator' */
      metux_model_6dof_only_contro_DW.Integrator_DSTATE_d = 0.0;

      /* InitializeConditions for DiscreteIntegrator: '<S678>/Filter' */
      metux_model_6dof_only_contro_DW.Filter_DSTATE = 0.0;
      metux_model_6dof_only_contro_DW.VerticalSpeedController_MODE = true;
    }

    /* RateLimiter: '<S23>/Rate Limiter' */
    rtb_FilterCoefficient_ih = metux_model_6dof_only_control_Y.currentsetpoint -
      metux_model_6dof_only_contro_DW.PrevY;
    rtb_Saturation_m =
      metux_model_6dof_only_control_P.AltitudeController.rateLimitMax *
      metux_model_6dof_only_co_period;
    if (rtb_FilterCoefficient_ih > rtb_Saturation_m) {
      rtb_Filter_j = rtb_Saturation_m + metux_model_6dof_only_contro_DW.PrevY;
    } else {
      rtb_Saturation_m =
        metux_model_6dof_only_control_P.AltitudeController.rateLimitMin *
        metux_model_6dof_only_co_period;
      if (rtb_FilterCoefficient_ih < rtb_Saturation_m) {
        rtb_Filter_j = rtb_Saturation_m + metux_model_6dof_only_contro_DW.PrevY;
      } else {
        rtb_Filter_j = metux_model_6dof_only_control_Y.currentsetpoint;
      }
    }

    metux_model_6dof_only_contro_DW.PrevY = rtb_Filter_j;

    /* End of RateLimiter: '<S23>/Rate Limiter' */

    /* Sum: '<S23>/Sum2' */
    rtb_Filter_j -= metux_model_6dof_only_control_Y.VelocityMeasured;

    /* Gain: '<S686>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S678>/Filter'
     *  Gain: '<S676>/Derivative Gain'
     *  Sum: '<S678>/SumD'
     */
    rtb_Filter = (metux_model_6dof_only_control_P.AltitudeController.kD *
                  rtb_Filter_j - metux_model_6dof_only_contro_DW.Filter_DSTATE) *
      metux_model_6dof_only_control_P.AltitudeController.N;

    /* Sum: '<S692>/Sum' incorporates:
     *  DiscreteIntegrator: '<S683>/Integrator'
     *  Gain: '<S688>/Proportional Gain'
     */
    rtb_Switch_di = (metux_model_6dof_only_control_P.AltitudeController.kP *
                     rtb_Filter_j +
                     metux_model_6dof_only_contro_DW.Integrator_DSTATE_d) +
      rtb_Filter;

    /* Saturate: '<S690>/Saturation' */
    if (rtb_Switch_di >
        metux_model_6dof_only_control_P.AltitudeController.saturationMax) {
      rtb_Saturation_m =
        metux_model_6dof_only_control_P.AltitudeController.saturationMax;
    } else if (rtb_Switch_di <
               metux_model_6dof_only_control_P.AltitudeController.saturationMin)
    {
      rtb_Saturation_m =
        metux_model_6dof_only_control_P.AltitudeController.saturationMin;
    } else {
      rtb_Saturation_m = rtb_Switch_di;
    }

    /* Sum: '<S23>/Sum' incorporates:
     *  Bias: '<S23>/Add Constant'
     *  Gain: '<S23>/Gain'
     *  Gain: '<S23>/Gain1'
     *  Saturate: '<S690>/Saturation'
     *  Sum: '<S7>/Diff'
     *  UnitDelay: '<S7>/UD'
     *
     * Block description for '<S7>/Diff':
     *
     *  Add in CPU
     *
     * Block description for '<S7>/UD':
     *
     *  Store in Global RAM
     */
    metux_model_6dof_only_control_B.BaseSignal = ((rtb_FilterCoefficient_h -
      metux_model_6dof_only_contro_DW.UD_DSTATE_e) * 0.1019367991845056 + 1.0) *
      metux_model_6dof_only_control_P.AltitudeController.kFF + rtb_Saturation_m;

    /* DeadZone: '<S675>/DeadZone' */
    if (rtb_Switch_di >
        metux_model_6dof_only_control_P.AltitudeController.saturationMax) {
      rtb_Switch_di -=
        metux_model_6dof_only_control_P.AltitudeController.saturationMax;
    } else if (rtb_Switch_di >=
               metux_model_6dof_only_control_P.AltitudeController.saturationMin)
    {
      rtb_Switch_di = 0.0;
    } else {
      rtb_Switch_di -=
        metux_model_6dof_only_control_P.AltitudeController.saturationMin;
    }

    /* End of DeadZone: '<S675>/DeadZone' */

    /* Gain: '<S680>/Integral Gain' */
    rtb_Filter_j *= metux_model_6dof_only_control_P.AltitudeController.kI;

    /* Switch: '<S673>/Switch1' incorporates:
     *  Constant: '<S673>/Clamping_zero'
     *  Constant: '<S673>/Constant'
     *  Constant: '<S673>/Constant2'
     *  RelationalOperator: '<S673>/fix for DT propagation issue'
     */
    if (rtb_Switch_di > 0.0) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    /* Switch: '<S673>/Switch2' incorporates:
     *  Constant: '<S673>/Clamping_zero'
     *  Constant: '<S673>/Constant3'
     *  Constant: '<S673>/Constant4'
     *  RelationalOperator: '<S673>/fix for DT propagation issue1'
     */
    if (rtb_Filter_j > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    /* Switch: '<S673>/Switch' incorporates:
     *  Constant: '<S673>/Clamping_zero'
     *  Constant: '<S673>/Constant1'
     *  Logic: '<S673>/AND3'
     *  RelationalOperator: '<S673>/Equal1'
     *  RelationalOperator: '<S673>/Relational Operator'
     *  Switch: '<S673>/Switch1'
     *  Switch: '<S673>/Switch2'
     */
    if ((rtb_Switch_di != 0.0) && (tmp == tmp_0)) {
      rtb_Filter_j = 0.0;
    }

    /* Update for DiscreteIntegrator: '<S683>/Integrator' incorporates:
     *  Switch: '<S673>/Switch'
     */
    metux_model_6dof_only_contro_DW.Integrator_DSTATE_d += 0.001 * rtb_Filter_j;
    if (metux_model_6dof_only_contro_DW.Integrator_DSTATE_d >
        metux_model_6dof_only_control_P.AltitudeController.saturationMax) {
      metux_model_6dof_only_contro_DW.Integrator_DSTATE_d =
        metux_model_6dof_only_control_P.AltitudeController.saturationMax;
    } else if (metux_model_6dof_only_contro_DW.Integrator_DSTATE_d <
               metux_model_6dof_only_control_P.AltitudeController.saturationMin)
    {
      metux_model_6dof_only_contro_DW.Integrator_DSTATE_d =
        metux_model_6dof_only_control_P.AltitudeController.saturationMin;
    }

    /* End of Update for DiscreteIntegrator: '<S683>/Integrator' */

    /* Update for DiscreteIntegrator: '<S678>/Filter' */
    metux_model_6dof_only_contro_DW.Filter_DSTATE += 0.001 * rtb_Filter;
  } else if (metux_model_6dof_only_contro_DW.VerticalSpeedController_MODE) {
    /* Disable for Sum: '<S23>/Sum' incorporates:
     *  Outport: '<S23>/Base Signal'
     */
    metux_model_6dof_only_control_B.BaseSignal = 0.0;
    metux_model_6dof_only_contro_DW.VerticalSpeedController_MODE = false;
  }

  /* End of Logic: '<Root>/AND' */
  /* End of Outputs for SubSystem: '<Root>/Vertical Speed Controller' */

  /* Outputs for Enabled SubSystem: '<Root>/Attitude Controller' incorporates:
   *  EnablePort: '<S1>/Enable'
   */
  /* Logic: '<Root>/AND1' incorporates:
   *  Constant: '<S2>/Constant'
   *  Constant: '<S3>/Constant'
   *  Inport: '<Root>/Activate'
   *  Logic: '<Root>/OR'
   *  RelationalOperator: '<S2>/Compare'
   *  RelationalOperator: '<S3>/Compare'
   */
  if (((metux_model_6dof_only_control_B.ControllerMode == 5.0) ||
       (metux_model_6dof_only_control_B.ControllerMode == 3.0)) &&
      metux_model_6dof_only_control_U.Activate) {
    if (!metux_model_6dof_only_contro_DW.AttitudeController_MODE) {
      /* InitializeConditions for DiscreteFir: '<S1>/Discrete FIR Filter' */
      metux_model_6dof_only_contro_DW.DiscreteFIRFilter_circBuf = 0;
      memset(&metux_model_6dof_only_contro_DW.DiscreteFIRFilter_states[0], 0,
             18U * sizeof(real_T));

      /* InitializeConditions for DiscreteIntegrator: '<S119>/Integrator' */
      metux_model_6dof_only_contro_DW.Integrator_DSTATE_ku = 0.0;

      /* InitializeConditions for DiscreteIntegrator: '<S114>/Filter' */
      metux_model_6dof_only_contro_DW.Filter_DSTATE_f2 = 0.0;

      /* InitializeConditions for DiscreteIntegrator: '<S65>/Integrator' */
      metux_model_6dof_only_contro_DW.Integrator_DSTATE_ky = 0.0;

      /* InitializeConditions for DiscreteIntegrator: '<S60>/Filter' */
      metux_model_6dof_only_contro_DW.Filter_DSTATE_ft = 0.0;
      metux_model_6dof_only_contro_DW.AttitudeController_MODE = true;
    }

    /* Gain: '<S26>/Gain' incorporates:
     *  DiscreteIntegrator: '<S157>/Integrator'
     *  SignalConversion generated from: '<Root>/Discrete FIR Filter1'
     */
    rtb_FilterCoefficient_ih = 57.295779513082323 *
      metux_model_6dof_only_contro_DW.Integrator_DSTATE[0];
    TmpSignalConversionAtDiscreteFI = 57.295779513082323 *
      metux_model_6dof_only_contro_DW.Integrator_DSTATE[1];

    /* DiscreteFir: '<S1>/Discrete FIR Filter' */
    rtb_DeadZone = rtb_FilterCoefficient_ih * 0.08;
    i = 1;
    for (j = metux_model_6dof_only_contro_DW.DiscreteFIRFilter_circBuf; j < 6; j
         ++) {
      rtb_DeadZone += metux_model_6dof_only_contro_DW.DiscreteFIRFilter_states[j]
        * metux_model_6dof_only_co_ConstP.DiscreteFIRFilter_Coefficients[i];
      i++;
    }

    for (j = 0; j < metux_model_6dof_only_contro_DW.DiscreteFIRFilter_circBuf; j
         ++) {
      rtb_DeadZone += metux_model_6dof_only_contro_DW.DiscreteFIRFilter_states[j]
        * metux_model_6dof_only_co_ConstP.DiscreteFIRFilter_Coefficients[i];
      i++;
    }

    rtb_DiscreteFIRFilter_idx_0 = rtb_DeadZone;
    rtb_DeadZone = TmpSignalConversionAtDiscreteFI * 0.08;
    i = 1;
    for (j = metux_model_6dof_only_contro_DW.DiscreteFIRFilter_circBuf; j < 6; j
         ++) {
      rtb_DeadZone += metux_model_6dof_only_contro_DW.DiscreteFIRFilter_states[j
        + 6] * metux_model_6dof_only_co_ConstP.DiscreteFIRFilter_Coefficients[i];
      i++;
    }

    for (j = 0; j < metux_model_6dof_only_contro_DW.DiscreteFIRFilter_circBuf; j
         ++) {
      rtb_DeadZone += metux_model_6dof_only_contro_DW.DiscreteFIRFilter_states[j
        + 6] * metux_model_6dof_only_co_ConstP.DiscreteFIRFilter_Coefficients[i];
      i++;
    }

    /* Gain: '<S122>/Filter Coefficient' incorporates:
     *  Constant: '<S1>/One'
     *  DiscreteFir: '<S1>/Discrete FIR Filter'
     *  DiscreteIntegrator: '<S114>/Filter'
     *  Gain: '<S112>/Derivative Gain'
     *  Sum: '<S114>/SumD'
     *  Sum: '<S1>/Sum1'
     */
    rtb_FilterCoefficient_a = ((0.0 - rtb_DeadZone) *
      metux_model_6dof_only_control_P.AttitudeController.kD -
      metux_model_6dof_only_contro_DW.Filter_DSTATE_f2) *
      metux_model_6dof_only_control_P.AttitudeController.N;

    /* Sum: '<S128>/Sum' incorporates:
     *  Constant: '<S1>/One'
     *  DiscreteFir: '<S1>/Discrete FIR Filter'
     *  DiscreteIntegrator: '<S119>/Integrator'
     *  Gain: '<S124>/Proportional Gain'
     *  Sum: '<S1>/Sum1'
     */
    rtb_FilterCoefficient_pz = ((0.0 - rtb_DeadZone) *
      metux_model_6dof_only_control_P.AttitudeController.kP +
      metux_model_6dof_only_contro_DW.Integrator_DSTATE_ku) +
      rtb_FilterCoefficient_a;

    /* DeadZone: '<S111>/DeadZone' */
    if (rtb_FilterCoefficient_pz >
        metux_model_6dof_only_control_P.AttitudeController.saturationMax) {
      rtb_Filter = rtb_FilterCoefficient_pz -
        metux_model_6dof_only_control_P.AttitudeController.saturationMax;
    } else if (rtb_FilterCoefficient_pz >=
               metux_model_6dof_only_control_P.AttitudeController.saturationMin)
    {
      rtb_Filter = 0.0;
    } else {
      rtb_Filter = rtb_FilterCoefficient_pz -
        metux_model_6dof_only_control_P.AttitudeController.saturationMin;
    }

    /* End of DeadZone: '<S111>/DeadZone' */

    /* Gain: '<S116>/Integral Gain' incorporates:
     *  Constant: '<S1>/One'
     *  DiscreteFir: '<S1>/Discrete FIR Filter'
     *  Sum: '<S1>/Sum1'
     */
    rtb_Saturation_m = (0.0 - rtb_DeadZone) *
      metux_model_6dof_only_control_P.AttitudeController.kI;

    /* Switch: '<S109>/Switch1' incorporates:
     *  Constant: '<S109>/Clamping_zero'
     *  Constant: '<S109>/Constant'
     *  Constant: '<S109>/Constant2'
     *  RelationalOperator: '<S109>/fix for DT propagation issue'
     */
    if (rtb_Filter > 0.0) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    /* Switch: '<S109>/Switch2' incorporates:
     *  Constant: '<S109>/Clamping_zero'
     *  Constant: '<S109>/Constant3'
     *  Constant: '<S109>/Constant4'
     *  RelationalOperator: '<S109>/fix for DT propagation issue1'
     */
    if (rtb_Saturation_m > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    /* Switch: '<S109>/Switch' incorporates:
     *  Constant: '<S109>/Clamping_zero'
     *  Constant: '<S109>/Constant1'
     *  Logic: '<S109>/AND3'
     *  RelationalOperator: '<S109>/Equal1'
     *  RelationalOperator: '<S109>/Relational Operator'
     *  Switch: '<S109>/Switch1'
     *  Switch: '<S109>/Switch2'
     */
    if ((rtb_Filter != 0.0) && (tmp == tmp_0)) {
      rtb_Filter = 0.0;
    } else {
      rtb_Filter = rtb_Saturation_m;
    }

    /* End of Switch: '<S109>/Switch' */

    /* Saturate: '<S126>/Saturation' */
    if (rtb_FilterCoefficient_pz >
        metux_model_6dof_only_control_P.AttitudeController.saturationMax) {
      rtb_FilterCoefficient_pz =
        metux_model_6dof_only_control_P.AttitudeController.saturationMax;
    } else if (rtb_FilterCoefficient_pz <
               metux_model_6dof_only_control_P.AttitudeController.saturationMin)
    {
      rtb_FilterCoefficient_pz =
        metux_model_6dof_only_control_P.AttitudeController.saturationMin;
    }

    /* End of Saturate: '<S126>/Saturation' */

    /* Saturate: '<S1>/Saturation4' incorporates:
     *  Gain: '<S1>/Gain'
     */
    if (-rtb_FilterCoefficient_pz >
        metux_model_6dof_only_control_P.AttitudeController.saturationMax) {
      /* Saturate: '<S1>/Saturation4' */
      metux_model_6dof_only_control_B.Saturation4 =
        metux_model_6dof_only_control_P.AttitudeController.saturationMax;
    } else if (-rtb_FilterCoefficient_pz <
               metux_model_6dof_only_control_P.AttitudeController.saturationMin)
    {
      /* Saturate: '<S1>/Saturation4' */
      metux_model_6dof_only_control_B.Saturation4 =
        metux_model_6dof_only_control_P.AttitudeController.saturationMin;
    } else {
      /* Saturate: '<S1>/Saturation4' */
      metux_model_6dof_only_control_B.Saturation4 = -rtb_FilterCoefficient_pz;
    }

    /* End of Saturate: '<S1>/Saturation4' */

    /* Saturate: '<S1>/Saturation3' */
    if (rtb_FilterCoefficient_pz >
        metux_model_6dof_only_control_P.AttitudeController.saturationMax) {
      /* Saturate: '<S1>/Saturation3' */
      metux_model_6dof_only_control_B.Saturation3 =
        metux_model_6dof_only_control_P.AttitudeController.saturationMax;
    } else if (rtb_FilterCoefficient_pz <
               metux_model_6dof_only_control_P.AttitudeController.saturationMin)
    {
      /* Saturate: '<S1>/Saturation3' */
      metux_model_6dof_only_control_B.Saturation3 =
        metux_model_6dof_only_control_P.AttitudeController.saturationMin;
    } else {
      /* Saturate: '<S1>/Saturation3' */
      metux_model_6dof_only_control_B.Saturation3 = rtb_FilterCoefficient_pz;
    }

    /* End of Saturate: '<S1>/Saturation3' */

    /* Gain: '<S68>/Filter Coefficient' incorporates:
     *  Constant: '<S1>/One'
     *  DiscreteIntegrator: '<S60>/Filter'
     *  Gain: '<S58>/Derivative Gain'
     *  Sum: '<S1>/Sum'
     *  Sum: '<S60>/SumD'
     */
    rtb_DeadZone = ((0.0 - rtb_DiscreteFIRFilter_idx_0) *
                    metux_model_6dof_only_control_P.AttitudeController.kD -
                    metux_model_6dof_only_contro_DW.Filter_DSTATE_ft) *
      metux_model_6dof_only_control_P.AttitudeController.N;

    /* Sum: '<S74>/Sum' incorporates:
     *  Constant: '<S1>/One'
     *  DiscreteIntegrator: '<S65>/Integrator'
     *  Gain: '<S70>/Proportional Gain'
     *  Sum: '<S1>/Sum'
     */
    rtb_Switch_di = ((0.0 - rtb_DiscreteFIRFilter_idx_0) *
                     metux_model_6dof_only_control_P.AttitudeController.kP +
                     metux_model_6dof_only_contro_DW.Integrator_DSTATE_ky) +
      rtb_DeadZone;

    /* DeadZone: '<S57>/DeadZone' */
    if (rtb_Switch_di >
        metux_model_6dof_only_control_P.AttitudeController.saturationMax) {
      rtb_Filter_j = rtb_Switch_di -
        metux_model_6dof_only_control_P.AttitudeController.saturationMax;
    } else if (rtb_Switch_di >=
               metux_model_6dof_only_control_P.AttitudeController.saturationMin)
    {
      rtb_Filter_j = 0.0;
    } else {
      rtb_Filter_j = rtb_Switch_di -
        metux_model_6dof_only_control_P.AttitudeController.saturationMin;
    }

    /* End of DeadZone: '<S57>/DeadZone' */

    /* Gain: '<S62>/Integral Gain' incorporates:
     *  Constant: '<S1>/One'
     *  Sum: '<S1>/Sum'
     */
    rtb_Saturation_m = (0.0 - rtb_DiscreteFIRFilter_idx_0) *
      metux_model_6dof_only_control_P.AttitudeController.kI;

    /* Saturate: '<S72>/Saturation' */
    if (rtb_Switch_di >
        metux_model_6dof_only_control_P.AttitudeController.saturationMax) {
      rtb_Switch_di =
        metux_model_6dof_only_control_P.AttitudeController.saturationMax;
    } else if (rtb_Switch_di <
               metux_model_6dof_only_control_P.AttitudeController.saturationMin)
    {
      rtb_Switch_di =
        metux_model_6dof_only_control_P.AttitudeController.saturationMin;
    }

    /* End of Saturate: '<S72>/Saturation' */

    /* Saturate: '<S1>/Saturation2' incorporates:
     *  Gain: '<S1>/Gain2'
     */
    if (-rtb_Switch_di >
        metux_model_6dof_only_control_P.AttitudeController.saturationMax) {
      /* Saturate: '<S1>/Saturation2' */
      metux_model_6dof_only_control_B.Saturation2 =
        metux_model_6dof_only_control_P.AttitudeController.saturationMax;
    } else if (-rtb_Switch_di <
               metux_model_6dof_only_control_P.AttitudeController.saturationMin)
    {
      /* Saturate: '<S1>/Saturation2' */
      metux_model_6dof_only_control_B.Saturation2 =
        metux_model_6dof_only_control_P.AttitudeController.saturationMin;
    } else {
      /* Saturate: '<S1>/Saturation2' */
      metux_model_6dof_only_control_B.Saturation2 = -rtb_Switch_di;
    }

    /* End of Saturate: '<S1>/Saturation2' */

    /* Saturate: '<S1>/Saturation1' */
    if (rtb_Switch_di >
        metux_model_6dof_only_control_P.AttitudeController.saturationMax) {
      /* Saturate: '<S1>/Saturation1' */
      metux_model_6dof_only_control_B.Saturation1 =
        metux_model_6dof_only_control_P.AttitudeController.saturationMax;
    } else if (rtb_Switch_di <
               metux_model_6dof_only_control_P.AttitudeController.saturationMin)
    {
      /* Saturate: '<S1>/Saturation1' */
      metux_model_6dof_only_control_B.Saturation1 =
        metux_model_6dof_only_control_P.AttitudeController.saturationMin;
    } else {
      /* Saturate: '<S1>/Saturation1' */
      metux_model_6dof_only_control_B.Saturation1 = rtb_Switch_di;
    }

    /* End of Saturate: '<S1>/Saturation1' */

    /* Update for DiscreteFir: '<S1>/Discrete FIR Filter' incorporates:
     *  DiscreteIntegrator: '<S157>/Integrator'
     *  Gain: '<S26>/Gain'
     */
    /* Update circular buffer index */
    metux_model_6dof_only_contro_DW.DiscreteFIRFilter_circBuf--;
    if (metux_model_6dof_only_contro_DW.DiscreteFIRFilter_circBuf < 0) {
      metux_model_6dof_only_contro_DW.DiscreteFIRFilter_circBuf = 5;
    }

    /* Update circular buffer */
    metux_model_6dof_only_contro_DW.DiscreteFIRFilter_states[metux_model_6dof_only_contro_DW.DiscreteFIRFilter_circBuf]
      = rtb_FilterCoefficient_ih;
    metux_model_6dof_only_contro_DW.DiscreteFIRFilter_states[metux_model_6dof_only_contro_DW.DiscreteFIRFilter_circBuf
      + 6] = TmpSignalConversionAtDiscreteFI;
    metux_model_6dof_only_contro_DW.DiscreteFIRFilter_states[metux_model_6dof_only_contro_DW.DiscreteFIRFilter_circBuf
      + 12] = 57.295779513082323 *
      metux_model_6dof_only_contro_DW.Integrator_DSTATE[2];

    /* End of Update for DiscreteFir: '<S1>/Discrete FIR Filter' */

    /* Update for DiscreteIntegrator: '<S119>/Integrator' */
    metux_model_6dof_only_contro_DW.Integrator_DSTATE_ku += 0.001 * rtb_Filter;

    /* Update for DiscreteIntegrator: '<S114>/Filter' */
    metux_model_6dof_only_contro_DW.Filter_DSTATE_f2 += 0.001 *
      rtb_FilterCoefficient_a;

    /* Switch: '<S55>/Switch1' incorporates:
     *  Constant: '<S55>/Clamping_zero'
     *  Constant: '<S55>/Constant'
     *  Constant: '<S55>/Constant2'
     *  RelationalOperator: '<S55>/fix for DT propagation issue'
     */
    if (rtb_Filter_j > 0.0) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    /* Switch: '<S55>/Switch2' incorporates:
     *  Constant: '<S55>/Clamping_zero'
     *  Constant: '<S55>/Constant3'
     *  Constant: '<S55>/Constant4'
     *  RelationalOperator: '<S55>/fix for DT propagation issue1'
     */
    if (rtb_Saturation_m > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    /* Switch: '<S55>/Switch' incorporates:
     *  Constant: '<S55>/Clamping_zero'
     *  Constant: '<S55>/Constant1'
     *  Logic: '<S55>/AND3'
     *  RelationalOperator: '<S55>/Equal1'
     *  RelationalOperator: '<S55>/Relational Operator'
     *  Switch: '<S55>/Switch1'
     *  Switch: '<S55>/Switch2'
     */
    if ((rtb_Filter_j != 0.0) && (tmp == tmp_0)) {
      rtb_Saturation_m = 0.0;
    }

    /* Update for DiscreteIntegrator: '<S65>/Integrator' incorporates:
     *  Switch: '<S55>/Switch'
     */
    metux_model_6dof_only_contro_DW.Integrator_DSTATE_ky += 0.001 *
      rtb_Saturation_m;

    /* Update for DiscreteIntegrator: '<S60>/Filter' */
    metux_model_6dof_only_contro_DW.Filter_DSTATE_ft += 0.001 * rtb_DeadZone;
  } else if (metux_model_6dof_only_contro_DW.AttitudeController_MODE) {
    /* Disable for Saturate: '<S1>/Saturation1' incorporates:
     *  Outport: '<S1>/right'
     */
    metux_model_6dof_only_control_B.Saturation1 = 0.0;

    /* Disable for Saturate: '<S1>/Saturation4' incorporates:
     *  Outport: '<S1>/front'
     */
    metux_model_6dof_only_control_B.Saturation4 = 0.0;

    /* Disable for Saturate: '<S1>/Saturation2' incorporates:
     *  Outport: '<S1>/left'
     */
    metux_model_6dof_only_control_B.Saturation2 = 0.0;

    /* Disable for Saturate: '<S1>/Saturation3' incorporates:
     *  Outport: '<S1>/back'
     */
    metux_model_6dof_only_control_B.Saturation3 = 0.0;
    metux_model_6dof_only_contro_DW.AttitudeController_MODE = false;
  }

  /* End of Logic: '<Root>/AND1' */
  /* End of Outputs for SubSystem: '<Root>/Attitude Controller' */

  /* Sum: '<Root>/Sum' */
  rtb_Filter_j = metux_model_6dof_only_control_B.BaseSignal +
    metux_model_6dof_only_control_B.Saturation1;

  /* Saturate: '<Root>/Saturation' */
  if (rtb_Filter_j > 300.0) {
    metux_model_6dof_only_control_Y.PressureDemand[0] = 300.0;
  } else if (rtb_Filter_j < 0.0) {
    metux_model_6dof_only_control_Y.PressureDemand[0] = 0.0;
  } else {
    metux_model_6dof_only_control_Y.PressureDemand[0] = rtb_Filter_j;
  }

  /* Sum: '<Root>/Sum' */
  rtb_Filter_j = metux_model_6dof_only_control_B.BaseSignal +
    metux_model_6dof_only_control_B.Saturation4;

  /* Saturate: '<Root>/Saturation' */
  if (rtb_Filter_j > 300.0) {
    metux_model_6dof_only_control_Y.PressureDemand[1] = 300.0;
  } else if (rtb_Filter_j < 0.0) {
    metux_model_6dof_only_control_Y.PressureDemand[1] = 0.0;
  } else {
    metux_model_6dof_only_control_Y.PressureDemand[1] = rtb_Filter_j;
  }

  /* Sum: '<Root>/Sum' */
  rtb_Filter_j = metux_model_6dof_only_control_B.BaseSignal +
    metux_model_6dof_only_control_B.Saturation2;

  /* Saturate: '<Root>/Saturation' */
  if (rtb_Filter_j > 300.0) {
    metux_model_6dof_only_control_Y.PressureDemand[2] = 300.0;
  } else if (rtb_Filter_j < 0.0) {
    metux_model_6dof_only_control_Y.PressureDemand[2] = 0.0;
  } else {
    metux_model_6dof_only_control_Y.PressureDemand[2] = rtb_Filter_j;
  }

  /* Sum: '<Root>/Sum' */
  rtb_Filter_j = metux_model_6dof_only_control_B.BaseSignal +
    metux_model_6dof_only_control_B.Saturation3;

  /* Saturate: '<Root>/Saturation' */
  if (rtb_Filter_j > 300.0) {
    metux_model_6dof_only_control_Y.PressureDemand[3] = 300.0;
  } else if (rtb_Filter_j < 0.0) {
    metux_model_6dof_only_control_Y.PressureDemand[3] = 0.0;
  } else {
    metux_model_6dof_only_control_Y.PressureDemand[3] = rtb_Filter_j;
  }

  /* DiscreteFir: '<Root>/Discrete FIR Filter1' incorporates:
   *  Inport: '<Root>/N1 pressure'
   *  Inport: '<Root>/N2 pressure'
   *  Inport: '<Root>/N3 pressure'
   *  Inport: '<Root>/N4 pressure'
   */
  rtb_DeadZone = metux_model_6dof_only_control_U.N1pressure *
    metux_model_6dof_only_control_P.filter.pressure[0];
  i = 1;
  for (j = metux_model_6dof_only_contro_DW.DiscreteFIRFilter1_circBuf; j < 6; j
       ++) {
    rtb_DeadZone += metux_model_6dof_only_contro_DW.DiscreteFIRFilter1_states[j]
      * metux_model_6dof_only_control_P.filter.pressure[i];
    i++;
  }

  for (j = 0; j < metux_model_6dof_only_contro_DW.DiscreteFIRFilter1_circBuf; j
       ++) {
    rtb_DeadZone += metux_model_6dof_only_contro_DW.DiscreteFIRFilter1_states[j]
      * metux_model_6dof_only_control_P.filter.pressure[i];
    i++;
  }

  rtb_Filter = rtb_DeadZone;
  rtb_DeadZone = metux_model_6dof_only_control_U.N2pressure *
    metux_model_6dof_only_control_P.filter.pressure[0];
  i = 1;
  for (j = metux_model_6dof_only_contro_DW.DiscreteFIRFilter1_circBuf; j < 6; j
       ++) {
    rtb_DeadZone += metux_model_6dof_only_contro_DW.DiscreteFIRFilter1_states[j
      + 6] * metux_model_6dof_only_control_P.filter.pressure[i];
    i++;
  }

  for (j = 0; j < metux_model_6dof_only_contro_DW.DiscreteFIRFilter1_circBuf; j
       ++) {
    rtb_DeadZone += metux_model_6dof_only_contro_DW.DiscreteFIRFilter1_states[j
      + 6] * metux_model_6dof_only_control_P.filter.pressure[i];
    i++;
  }

  rtb_Switch_di = rtb_DeadZone;
  rtb_DeadZone = metux_model_6dof_only_control_U.N3pressure *
    metux_model_6dof_only_control_P.filter.pressure[0];
  i = 1;
  for (j = metux_model_6dof_only_contro_DW.DiscreteFIRFilter1_circBuf; j < 6; j
       ++) {
    rtb_DeadZone += metux_model_6dof_only_contro_DW.DiscreteFIRFilter1_states[j
      + 12] * metux_model_6dof_only_control_P.filter.pressure[i];
    i++;
  }

  for (j = 0; j < metux_model_6dof_only_contro_DW.DiscreteFIRFilter1_circBuf; j
       ++) {
    rtb_DeadZone += metux_model_6dof_only_contro_DW.DiscreteFIRFilter1_states[j
      + 12] * metux_model_6dof_only_control_P.filter.pressure[i];
    i++;
  }

  rtb_FilterCoefficient_pz = rtb_DeadZone;
  rtb_DeadZone = metux_model_6dof_only_control_U.N4pressure *
    metux_model_6dof_only_control_P.filter.pressure[0];
  i = 1;
  for (j = metux_model_6dof_only_contro_DW.DiscreteFIRFilter1_circBuf; j < 6; j
       ++) {
    rtb_DeadZone += metux_model_6dof_only_contro_DW.DiscreteFIRFilter1_states[j
      + 18] * metux_model_6dof_only_control_P.filter.pressure[i];
    i++;
  }

  for (j = 0; j < metux_model_6dof_only_contro_DW.DiscreteFIRFilter1_circBuf; j
       ++) {
    rtb_DeadZone += metux_model_6dof_only_contro_DW.DiscreteFIRFilter1_states[j
      + 18] * metux_model_6dof_only_control_P.filter.pressure[i];
    i++;
  }

  /* Outputs for Enabled SubSystem: '<Root>/Pressure Controllers' incorporates:
   *  EnablePort: '<S19>/Enable'
   */
  /* Update for Inport: '<Root>/Activate' */
  if (metux_model_6dof_only_control_U.Activate) {
    metux_model_6dof_only_contro_DW.PressureControllers_MODE = true;

    /* RelationalOperator: '<S382>/Compare' incorporates:
     *  Constant: '<S382>/Constant'
     */
    rtb_FixPtRelationalOperator =
      (metux_model_6dof_only_control_B.ControllerMode == 2.0);

    /* Switch: '<S19>/Switch4' */
    if (rtb_FixPtRelationalOperator) {
      rtb_Filter_j = metux_model_6dof_only_control_Y.currentsetpoint;
    } else {
      rtb_Filter_j = metux_model_6dof_only_control_Y.PressureDemand[0];
    }

    /* End of Switch: '<S19>/Switch4' */

    /* RateLimiter: '<S19>/Rate Limiter' incorporates:
     *  RateLimiter: '<S19>/Rate Limiter1'
     *  RateLimiter: '<S19>/Rate Limiter2'
     *  RateLimiter: '<S19>/Rate Limiter3'
     */
    rtb_FilterCoefficient_ih = rtb_Filter_j -
      metux_model_6dof_only_contro_DW.PrevY_i;
    rtb_Saturation_m =
      metux_model_6dof_only_control_P.motorController.rateLimitMax *
      metux_model_6dof_only_co_period;
    if (rtb_FilterCoefficient_ih > rtb_Saturation_m) {
      rtb_Filter_j = rtb_Saturation_m + metux_model_6dof_only_contro_DW.PrevY_i;
    } else {
      rtb_FilterCoefficient_ia =
        metux_model_6dof_only_control_P.motorController.rateLimitMin *
        metux_model_6dof_only_co_period;
      if (rtb_FilterCoefficient_ih < rtb_FilterCoefficient_ia) {
        rtb_Filter_j = rtb_FilterCoefficient_ia +
          metux_model_6dof_only_contro_DW.PrevY_i;
      }
    }

    metux_model_6dof_only_contro_DW.PrevY_i = rtb_Filter_j;

    /* End of RateLimiter: '<S19>/Rate Limiter' */

    /* Sum: '<S19>/Sum' */
    rtb_Filter_j -= rtb_Filter;

    /* Gain: '<S588>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S580>/Filter'
     *  Gain: '<S578>/Derivative Gain'
     *  Sum: '<S580>/SumD'
     */
    TmpSignalConversionAtDiscreteFI =
      (metux_model_6dof_only_control_P.motorController.kD * rtb_Filter_j -
       metux_model_6dof_only_contro_DW.Filter_DSTATE_b) *
      metux_model_6dof_only_control_P.motorController.N;

    /* Sum: '<S594>/Sum' incorporates:
     *  DiscreteIntegrator: '<S585>/Integrator'
     *  Gain: '<S590>/Proportional Gain'
     */
    rtb_Filter = (metux_model_6dof_only_control_P.motorController.kP *
                  rtb_Filter_j +
                  metux_model_6dof_only_contro_DW.Integrator_DSTATE_o) +
      TmpSignalConversionAtDiscreteFI;

    /* Switch: '<S19>/Switch' incorporates:
     *  DataTypeConversion: '<S19>/Cast To Boolean'
     */
    if (metux_model_6dof_only_control_B.ControllerMode != 0.0) {
      /* Saturate: '<S592>/Saturation' */
      if (rtb_Filter >
          metux_model_6dof_only_control_P.motorController.saturationMax) {
        /* Switch: '<S19>/Switch' */
        metux_model_6dof_only_control_B.Switch =
          metux_model_6dof_only_control_P.motorController.saturationMax;
      } else if (rtb_Filter <
                 metux_model_6dof_only_control_P.motorController.saturationMin)
      {
        /* Switch: '<S19>/Switch' */
        metux_model_6dof_only_control_B.Switch =
          metux_model_6dof_only_control_P.motorController.saturationMin;
      } else {
        /* Switch: '<S19>/Switch' */
        metux_model_6dof_only_control_B.Switch = rtb_Filter;
      }

      /* End of Saturate: '<S592>/Saturation' */
    } else {
      /* Switch: '<S19>/Switch' */
      metux_model_6dof_only_control_B.Switch =
        metux_model_6dof_only_control_Y.currentsetpoint;
    }

    /* End of Switch: '<S19>/Switch' */

    /* DeadZone: '<S577>/DeadZone' */
    if (rtb_Filter >
        metux_model_6dof_only_control_P.motorController.saturationMax) {
      rtb_Filter -=
        metux_model_6dof_only_control_P.motorController.saturationMax;
    } else if (rtb_Filter >=
               metux_model_6dof_only_control_P.motorController.saturationMin) {
      rtb_Filter = 0.0;
    } else {
      rtb_Filter -=
        metux_model_6dof_only_control_P.motorController.saturationMin;
    }

    /* End of DeadZone: '<S577>/DeadZone' */

    /* Gain: '<S582>/Integral Gain' */
    rtb_Filter_j *= metux_model_6dof_only_control_P.motorController.kI;

    /* Switch: '<S575>/Switch1' incorporates:
     *  Constant: '<S575>/Clamping_zero'
     *  Constant: '<S575>/Constant'
     *  Constant: '<S575>/Constant2'
     *  RelationalOperator: '<S575>/fix for DT propagation issue'
     */
    if (rtb_Filter > 0.0) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    /* Switch: '<S575>/Switch2' incorporates:
     *  Constant: '<S575>/Clamping_zero'
     *  Constant: '<S575>/Constant3'
     *  Constant: '<S575>/Constant4'
     *  RelationalOperator: '<S575>/fix for DT propagation issue1'
     */
    if (rtb_Filter_j > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    /* Switch: '<S575>/Switch' incorporates:
     *  Constant: '<S575>/Clamping_zero'
     *  Constant: '<S575>/Constant1'
     *  Logic: '<S575>/AND3'
     *  RelationalOperator: '<S575>/Equal1'
     *  RelationalOperator: '<S575>/Relational Operator'
     *  Switch: '<S575>/Switch1'
     *  Switch: '<S575>/Switch2'
     */
    if ((rtb_Filter != 0.0) && (tmp == tmp_0)) {
      rtb_FilterCoefficient_a = 0.0;
    } else {
      rtb_FilterCoefficient_a = rtb_Filter_j;
    }

    /* End of Switch: '<S575>/Switch' */

    /* Switch: '<S19>/Switch5' */
    if (rtb_FixPtRelationalOperator) {
      rtb_Filter_j = metux_model_6dof_only_control_Y.currentsetpoint;
    } else {
      rtb_Filter_j = metux_model_6dof_only_control_Y.PressureDemand[1];
    }

    /* End of Switch: '<S19>/Switch5' */

    /* RateLimiter: '<S19>/Rate Limiter1' */
    rtb_FilterCoefficient_ih = rtb_Filter_j -
      metux_model_6dof_only_contro_DW.PrevY_m;
    if (rtb_FilterCoefficient_ih > rtb_Saturation_m) {
      rtb_Filter_j = rtb_Saturation_m + metux_model_6dof_only_contro_DW.PrevY_m;
    } else {
      rtb_FilterCoefficient_ia =
        metux_model_6dof_only_control_P.motorController.rateLimitMin *
        metux_model_6dof_only_co_period;
      if (rtb_FilterCoefficient_ih < rtb_FilterCoefficient_ia) {
        rtb_Filter_j = rtb_FilterCoefficient_ia +
          metux_model_6dof_only_contro_DW.PrevY_m;
      }
    }

    metux_model_6dof_only_contro_DW.PrevY_m = rtb_Filter_j;

    /* Sum: '<S19>/Sum1' */
    rtb_Filter_j -= rtb_Switch_di;

    /* Gain: '<S426>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S418>/Filter'
     *  Gain: '<S416>/Derivative Gain'
     *  Sum: '<S418>/SumD'
     */
    rtb_DiscreteFIRFilter_idx_0 =
      (metux_model_6dof_only_control_P.motorController.kD * rtb_Filter_j -
       metux_model_6dof_only_contro_DW.Filter_DSTATE_h) *
      metux_model_6dof_only_control_P.motorController.N;

    /* Sum: '<S432>/Sum' incorporates:
     *  DiscreteIntegrator: '<S423>/Integrator'
     *  Gain: '<S428>/Proportional Gain'
     */
    rtb_Switch_di = (metux_model_6dof_only_control_P.motorController.kP *
                     rtb_Filter_j +
                     metux_model_6dof_only_contro_DW.Integrator_DSTATE_c) +
      rtb_DiscreteFIRFilter_idx_0;

    /* Switch: '<S19>/Switch1' incorporates:
     *  DataTypeConversion: '<S19>/Cast To Boolean'
     */
    if (metux_model_6dof_only_control_B.ControllerMode != 0.0) {
      /* Saturate: '<S430>/Saturation' */
      if (rtb_Switch_di >
          metux_model_6dof_only_control_P.motorController.saturationMax) {
        /* Switch: '<S19>/Switch1' */
        metux_model_6dof_only_control_B.Switch1 =
          metux_model_6dof_only_control_P.motorController.saturationMax;
      } else if (rtb_Switch_di <
                 metux_model_6dof_only_control_P.motorController.saturationMin)
      {
        /* Switch: '<S19>/Switch1' */
        metux_model_6dof_only_control_B.Switch1 =
          metux_model_6dof_only_control_P.motorController.saturationMin;
      } else {
        /* Switch: '<S19>/Switch1' */
        metux_model_6dof_only_control_B.Switch1 = rtb_Switch_di;
      }

      /* End of Saturate: '<S430>/Saturation' */
    } else {
      /* Switch: '<S19>/Switch1' */
      metux_model_6dof_only_control_B.Switch1 =
        metux_model_6dof_only_control_Y.currentsetpoint;
    }

    /* End of Switch: '<S19>/Switch1' */

    /* DeadZone: '<S415>/DeadZone' */
    if (rtb_Switch_di >
        metux_model_6dof_only_control_P.motorController.saturationMax) {
      rtb_Switch_di -=
        metux_model_6dof_only_control_P.motorController.saturationMax;
    } else if (rtb_Switch_di >=
               metux_model_6dof_only_control_P.motorController.saturationMin) {
      rtb_Switch_di = 0.0;
    } else {
      rtb_Switch_di -=
        metux_model_6dof_only_control_P.motorController.saturationMin;
    }

    /* End of DeadZone: '<S415>/DeadZone' */

    /* Gain: '<S420>/Integral Gain' */
    rtb_Filter_j *= metux_model_6dof_only_control_P.motorController.kI;

    /* Switch: '<S19>/Switch6' */
    if (rtb_FixPtRelationalOperator) {
      rtb_Filter = metux_model_6dof_only_control_Y.currentsetpoint;
    } else {
      rtb_Filter = metux_model_6dof_only_control_Y.PressureDemand[2];
    }

    /* End of Switch: '<S19>/Switch6' */

    /* RateLimiter: '<S19>/Rate Limiter2' */
    rtb_FilterCoefficient_ih = rtb_Filter -
      metux_model_6dof_only_contro_DW.PrevY_a;
    if (rtb_FilterCoefficient_ih > rtb_Saturation_m) {
      rtb_Filter = rtb_Saturation_m + metux_model_6dof_only_contro_DW.PrevY_a;
    } else {
      rtb_FilterCoefficient_ia =
        metux_model_6dof_only_control_P.motorController.rateLimitMin *
        metux_model_6dof_only_co_period;
      if (rtb_FilterCoefficient_ih < rtb_FilterCoefficient_ia) {
        rtb_Filter = rtb_FilterCoefficient_ia +
          metux_model_6dof_only_contro_DW.PrevY_a;
      }
    }

    metux_model_6dof_only_contro_DW.PrevY_a = rtb_Filter;

    /* Sum: '<S19>/Sum2' */
    rtb_Filter -= rtb_FilterCoefficient_pz;

    /* Gain: '<S480>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S472>/Filter'
     *  Gain: '<S470>/Derivative Gain'
     *  Sum: '<S472>/SumD'
     */
    rtb_FilterCoefficient_ia =
      (metux_model_6dof_only_control_P.motorController.kD * rtb_Filter -
       metux_model_6dof_only_contro_DW.Filter_DSTATE_p) *
      metux_model_6dof_only_control_P.motorController.N;

    /* Sum: '<S486>/Sum' incorporates:
     *  DiscreteIntegrator: '<S477>/Integrator'
     *  Gain: '<S482>/Proportional Gain'
     */
    rtb_FilterCoefficient_pz =
      (metux_model_6dof_only_control_P.motorController.kP * rtb_Filter +
       metux_model_6dof_only_contro_DW.Integrator_DSTATE_j) +
      rtb_FilterCoefficient_ia;

    /* Switch: '<S19>/Switch2' incorporates:
     *  DataTypeConversion: '<S19>/Cast To Boolean'
     */
    if (metux_model_6dof_only_control_B.ControllerMode != 0.0) {
      /* Saturate: '<S484>/Saturation' */
      if (rtb_FilterCoefficient_pz >
          metux_model_6dof_only_control_P.motorController.saturationMax) {
        /* Switch: '<S19>/Switch2' */
        metux_model_6dof_only_control_B.Switch2 =
          metux_model_6dof_only_control_P.motorController.saturationMax;
      } else if (rtb_FilterCoefficient_pz <
                 metux_model_6dof_only_control_P.motorController.saturationMin)
      {
        /* Switch: '<S19>/Switch2' */
        metux_model_6dof_only_control_B.Switch2 =
          metux_model_6dof_only_control_P.motorController.saturationMin;
      } else {
        /* Switch: '<S19>/Switch2' */
        metux_model_6dof_only_control_B.Switch2 = rtb_FilterCoefficient_pz;
      }

      /* End of Saturate: '<S484>/Saturation' */
    } else {
      /* Switch: '<S19>/Switch2' */
      metux_model_6dof_only_control_B.Switch2 =
        metux_model_6dof_only_control_Y.currentsetpoint;
    }

    /* End of Switch: '<S19>/Switch2' */

    /* DeadZone: '<S469>/DeadZone' */
    if (rtb_FilterCoefficient_pz >
        metux_model_6dof_only_control_P.motorController.saturationMax) {
      rtb_FilterCoefficient_pz -=
        metux_model_6dof_only_control_P.motorController.saturationMax;
    } else if (rtb_FilterCoefficient_pz >=
               metux_model_6dof_only_control_P.motorController.saturationMin) {
      rtb_FilterCoefficient_pz = 0.0;
    } else {
      rtb_FilterCoefficient_pz -=
        metux_model_6dof_only_control_P.motorController.saturationMin;
    }

    /* End of DeadZone: '<S469>/DeadZone' */

    /* Gain: '<S474>/Integral Gain' */
    rtb_Filter *= metux_model_6dof_only_control_P.motorController.kI;

    /* Switch: '<S19>/Switch7' */
    if (rtb_FixPtRelationalOperator) {
      rtb_IntegralGain = metux_model_6dof_only_control_Y.currentsetpoint;
    } else {
      rtb_IntegralGain = metux_model_6dof_only_control_Y.PressureDemand[3];
    }

    /* End of Switch: '<S19>/Switch7' */

    /* RateLimiter: '<S19>/Rate Limiter3' */
    rtb_FilterCoefficient_ih = rtb_IntegralGain -
      metux_model_6dof_only_contro_DW.PrevY_g;
    if (rtb_FilterCoefficient_ih > rtb_Saturation_m) {
      rtb_IntegralGain = rtb_Saturation_m +
        metux_model_6dof_only_contro_DW.PrevY_g;
    } else {
      rtb_Saturation_m =
        metux_model_6dof_only_control_P.motorController.rateLimitMin *
        metux_model_6dof_only_co_period;
      if (rtb_FilterCoefficient_ih < rtb_Saturation_m) {
        rtb_IntegralGain = rtb_Saturation_m +
          metux_model_6dof_only_contro_DW.PrevY_g;
      }
    }

    metux_model_6dof_only_contro_DW.PrevY_g = rtb_IntegralGain;

    /* Sum: '<S19>/Sum3' incorporates:
     *  DiscreteFir: '<Root>/Discrete FIR Filter1'
     */
    rtb_IntegralGain -= rtb_DeadZone;

    /* Gain: '<S534>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S526>/Filter'
     *  Gain: '<S524>/Derivative Gain'
     *  Sum: '<S526>/SumD'
     */
    rtb_Saturation_m = (metux_model_6dof_only_control_P.motorController.kD *
                        rtb_IntegralGain -
                        metux_model_6dof_only_contro_DW.Filter_DSTATE_j) *
      metux_model_6dof_only_control_P.motorController.N;

    /* Sum: '<S540>/Sum' incorporates:
     *  DiscreteIntegrator: '<S531>/Integrator'
     *  Gain: '<S536>/Proportional Gain'
     */
    rtb_DeadZone = (metux_model_6dof_only_control_P.motorController.kP *
                    rtb_IntegralGain +
                    metux_model_6dof_only_contro_DW.Integrator_DSTATE_n) +
      rtb_Saturation_m;

    /* Switch: '<S19>/Switch3' incorporates:
     *  DataTypeConversion: '<S19>/Cast To Boolean'
     */
    if (metux_model_6dof_only_control_B.ControllerMode != 0.0) {
      /* Saturate: '<S538>/Saturation' */
      if (rtb_DeadZone >
          metux_model_6dof_only_control_P.motorController.saturationMax) {
        /* Switch: '<S19>/Switch3' */
        metux_model_6dof_only_control_B.Switch3 =
          metux_model_6dof_only_control_P.motorController.saturationMax;
      } else if (rtb_DeadZone <
                 metux_model_6dof_only_control_P.motorController.saturationMin)
      {
        /* Switch: '<S19>/Switch3' */
        metux_model_6dof_only_control_B.Switch3 =
          metux_model_6dof_only_control_P.motorController.saturationMin;
      } else {
        /* Switch: '<S19>/Switch3' */
        metux_model_6dof_only_control_B.Switch3 = rtb_DeadZone;
      }

      /* End of Saturate: '<S538>/Saturation' */
    } else {
      /* Switch: '<S19>/Switch3' */
      metux_model_6dof_only_control_B.Switch3 =
        metux_model_6dof_only_control_Y.currentsetpoint;
    }

    /* End of Switch: '<S19>/Switch3' */

    /* DeadZone: '<S523>/DeadZone' */
    if (rtb_DeadZone >
        metux_model_6dof_only_control_P.motorController.saturationMax) {
      rtb_DeadZone -=
        metux_model_6dof_only_control_P.motorController.saturationMax;
    } else if (rtb_DeadZone >=
               metux_model_6dof_only_control_P.motorController.saturationMin) {
      rtb_DeadZone = 0.0;
    } else {
      rtb_DeadZone -=
        metux_model_6dof_only_control_P.motorController.saturationMin;
    }

    /* End of DeadZone: '<S523>/DeadZone' */

    /* Gain: '<S528>/Integral Gain' */
    rtb_IntegralGain *= metux_model_6dof_only_control_P.motorController.kI;

    /* Update for DiscreteIntegrator: '<S585>/Integrator' */
    metux_model_6dof_only_contro_DW.Integrator_DSTATE_o += 0.001 *
      rtb_FilterCoefficient_a;
    if (metux_model_6dof_only_contro_DW.Integrator_DSTATE_o >
        metux_model_6dof_only_control_P.motorController.saturationMax) {
      metux_model_6dof_only_contro_DW.Integrator_DSTATE_o =
        metux_model_6dof_only_control_P.motorController.saturationMax;
    } else if (metux_model_6dof_only_contro_DW.Integrator_DSTATE_o <
               metux_model_6dof_only_control_P.motorController.saturationMin) {
      metux_model_6dof_only_contro_DW.Integrator_DSTATE_o =
        metux_model_6dof_only_control_P.motorController.saturationMin;
    }

    /* End of Update for DiscreteIntegrator: '<S585>/Integrator' */

    /* Update for DiscreteIntegrator: '<S580>/Filter' */
    metux_model_6dof_only_contro_DW.Filter_DSTATE_b += 0.001 *
      TmpSignalConversionAtDiscreteFI;

    /* Switch: '<S413>/Switch1' incorporates:
     *  Constant: '<S413>/Clamping_zero'
     *  Constant: '<S413>/Constant'
     *  Constant: '<S413>/Constant2'
     *  RelationalOperator: '<S413>/fix for DT propagation issue'
     */
    if (rtb_Switch_di > 0.0) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    /* Switch: '<S413>/Switch2' incorporates:
     *  Constant: '<S413>/Clamping_zero'
     *  Constant: '<S413>/Constant3'
     *  Constant: '<S413>/Constant4'
     *  RelationalOperator: '<S413>/fix for DT propagation issue1'
     */
    if (rtb_Filter_j > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    /* Switch: '<S413>/Switch' incorporates:
     *  Constant: '<S413>/Clamping_zero'
     *  Constant: '<S413>/Constant1'
     *  Logic: '<S413>/AND3'
     *  RelationalOperator: '<S413>/Equal1'
     *  RelationalOperator: '<S413>/Relational Operator'
     *  Switch: '<S413>/Switch1'
     *  Switch: '<S413>/Switch2'
     */
    if ((rtb_Switch_di != 0.0) && (tmp == tmp_0)) {
      rtb_Filter_j = 0.0;
    }

    /* Update for DiscreteIntegrator: '<S423>/Integrator' incorporates:
     *  Switch: '<S413>/Switch'
     */
    metux_model_6dof_only_contro_DW.Integrator_DSTATE_c += 0.001 * rtb_Filter_j;
    if (metux_model_6dof_only_contro_DW.Integrator_DSTATE_c >
        metux_model_6dof_only_control_P.motorController.saturationMax) {
      metux_model_6dof_only_contro_DW.Integrator_DSTATE_c =
        metux_model_6dof_only_control_P.motorController.saturationMax;
    } else if (metux_model_6dof_only_contro_DW.Integrator_DSTATE_c <
               metux_model_6dof_only_control_P.motorController.saturationMin) {
      metux_model_6dof_only_contro_DW.Integrator_DSTATE_c =
        metux_model_6dof_only_control_P.motorController.saturationMin;
    }

    /* End of Update for DiscreteIntegrator: '<S423>/Integrator' */

    /* Update for DiscreteIntegrator: '<S418>/Filter' */
    metux_model_6dof_only_contro_DW.Filter_DSTATE_h += 0.001 *
      rtb_DiscreteFIRFilter_idx_0;

    /* Switch: '<S467>/Switch1' incorporates:
     *  Constant: '<S467>/Clamping_zero'
     *  Constant: '<S467>/Constant'
     *  Constant: '<S467>/Constant2'
     *  RelationalOperator: '<S467>/fix for DT propagation issue'
     */
    if (rtb_FilterCoefficient_pz > 0.0) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    /* Switch: '<S467>/Switch2' incorporates:
     *  Constant: '<S467>/Clamping_zero'
     *  Constant: '<S467>/Constant3'
     *  Constant: '<S467>/Constant4'
     *  RelationalOperator: '<S467>/fix for DT propagation issue1'
     */
    if (rtb_Filter > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    /* Switch: '<S467>/Switch' incorporates:
     *  Constant: '<S467>/Clamping_zero'
     *  Constant: '<S467>/Constant1'
     *  Logic: '<S467>/AND3'
     *  RelationalOperator: '<S467>/Equal1'
     *  RelationalOperator: '<S467>/Relational Operator'
     *  Switch: '<S467>/Switch1'
     *  Switch: '<S467>/Switch2'
     */
    if ((rtb_FilterCoefficient_pz != 0.0) && (tmp == tmp_0)) {
      rtb_Filter = 0.0;
    }

    /* Update for DiscreteIntegrator: '<S477>/Integrator' incorporates:
     *  Switch: '<S467>/Switch'
     */
    metux_model_6dof_only_contro_DW.Integrator_DSTATE_j += 0.001 * rtb_Filter;
    if (metux_model_6dof_only_contro_DW.Integrator_DSTATE_j >
        metux_model_6dof_only_control_P.motorController.saturationMax) {
      metux_model_6dof_only_contro_DW.Integrator_DSTATE_j =
        metux_model_6dof_only_control_P.motorController.saturationMax;
    } else if (metux_model_6dof_only_contro_DW.Integrator_DSTATE_j <
               metux_model_6dof_only_control_P.motorController.saturationMin) {
      metux_model_6dof_only_contro_DW.Integrator_DSTATE_j =
        metux_model_6dof_only_control_P.motorController.saturationMin;
    }

    /* End of Update for DiscreteIntegrator: '<S477>/Integrator' */

    /* Update for DiscreteIntegrator: '<S472>/Filter' */
    metux_model_6dof_only_contro_DW.Filter_DSTATE_p += 0.001 *
      rtb_FilterCoefficient_ia;

    /* Switch: '<S521>/Switch1' incorporates:
     *  Constant: '<S521>/Clamping_zero'
     *  Constant: '<S521>/Constant'
     *  Constant: '<S521>/Constant2'
     *  RelationalOperator: '<S521>/fix for DT propagation issue'
     */
    if (rtb_DeadZone > 0.0) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    /* Switch: '<S521>/Switch2' incorporates:
     *  Constant: '<S521>/Clamping_zero'
     *  Constant: '<S521>/Constant3'
     *  Constant: '<S521>/Constant4'
     *  RelationalOperator: '<S521>/fix for DT propagation issue1'
     */
    if (rtb_IntegralGain > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    /* Switch: '<S521>/Switch' incorporates:
     *  Constant: '<S521>/Clamping_zero'
     *  Constant: '<S521>/Constant1'
     *  Logic: '<S521>/AND3'
     *  RelationalOperator: '<S521>/Equal1'
     *  RelationalOperator: '<S521>/Relational Operator'
     *  Switch: '<S521>/Switch1'
     *  Switch: '<S521>/Switch2'
     */
    if ((rtb_DeadZone != 0.0) && (tmp == tmp_0)) {
      rtb_IntegralGain = 0.0;
    }

    /* Update for DiscreteIntegrator: '<S531>/Integrator' incorporates:
     *  Switch: '<S521>/Switch'
     */
    metux_model_6dof_only_contro_DW.Integrator_DSTATE_n += 0.001 *
      rtb_IntegralGain;
    if (metux_model_6dof_only_contro_DW.Integrator_DSTATE_n >
        metux_model_6dof_only_control_P.motorController.saturationMax) {
      metux_model_6dof_only_contro_DW.Integrator_DSTATE_n =
        metux_model_6dof_only_control_P.motorController.saturationMax;
    } else if (metux_model_6dof_only_contro_DW.Integrator_DSTATE_n <
               metux_model_6dof_only_control_P.motorController.saturationMin) {
      metux_model_6dof_only_contro_DW.Integrator_DSTATE_n =
        metux_model_6dof_only_control_P.motorController.saturationMin;
    }

    /* End of Update for DiscreteIntegrator: '<S531>/Integrator' */

    /* Update for DiscreteIntegrator: '<S526>/Filter' */
    metux_model_6dof_only_contro_DW.Filter_DSTATE_j += 0.001 * rtb_Saturation_m;
  } else if (metux_model_6dof_only_contro_DW.PressureControllers_MODE) {
    /* Disable for Switch: '<S19>/Switch' incorporates:
     *  Outport: '<S19>/Right Duty'
     */
    metux_model_6dof_only_control_B.Switch = 0.0;

    /* Disable for Switch: '<S19>/Switch1' incorporates:
     *  Outport: '<S19>/Front Duty'
     */
    metux_model_6dof_only_control_B.Switch1 = 0.0;

    /* Disable for Switch: '<S19>/Switch2' incorporates:
     *  Outport: '<S19>/Left Duty'
     */
    metux_model_6dof_only_control_B.Switch2 = 0.0;

    /* Disable for Switch: '<S19>/Switch3' incorporates:
     *  Outport: '<S19>/Back Duty'
     */
    metux_model_6dof_only_control_B.Switch3 = 0.0;
    metux_model_6dof_only_contro_DW.PressureControllers_MODE = false;
  }

  /* End of Outputs for SubSystem: '<Root>/Pressure Controllers' */

  /* Switch: '<Root>/Switch' */
  if (rtb_AND2) {
    rtb_Filter = metux_model_6dof_only_control_B.Saturation_n;
    rtb_Switch_di = metux_model_6dof_only_control_B.Saturation;
    rtb_FilterCoefficient_pz = metux_model_6dof_only_control_B.Saturation_a;
    rtb_Filter_j = metux_model_6dof_only_control_B.Saturation_h;
  } else {
    rtb_Filter = metux_model_6dof_only_control_B.Switch;
    rtb_Switch_di = metux_model_6dof_only_control_B.Switch1;
    rtb_FilterCoefficient_pz = metux_model_6dof_only_control_B.Switch2;
    rtb_Filter_j = metux_model_6dof_only_control_B.Switch3;
  }

  /* End of Switch: '<Root>/Switch' */

  /* Outputs for Enabled SubSystem: '<Root>/E-STOP Override' incorporates:
   *  EnablePort: '<S8>/Enable'
   */
  /* Logic: '<Root>/NOT' incorporates:
   *  Inport: '<Root>/E-STOP'
   */
  if (!metux_model_6dof_only_control_U.ESTOP) {
    metux_model_6dof_only_contro_DW.ESTOPOverride_MODE = true;

    /* SignalConversion generated from: '<S8>/Right Duty' */
    metux_model_6dof_only_control_B.RightDuty = rtb_Filter;

    /* SignalConversion generated from: '<S8>/Front Duty' */
    metux_model_6dof_only_control_B.FrontDuty = rtb_Switch_di;

    /* SignalConversion generated from: '<S8>/Left Duty' */
    metux_model_6dof_only_control_B.LeftDuty = rtb_FilterCoefficient_pz;

    /* SignalConversion generated from: '<S8>/Back Duty' */
    metux_model_6dof_only_control_B.BackDuty = rtb_Filter_j;
  } else if (metux_model_6dof_only_contro_DW.ESTOPOverride_MODE) {
    /* Disable for SignalConversion generated from: '<S8>/Right Duty' incorporates:
     *  Outport: '<S8>/u'
     */
    metux_model_6dof_only_control_B.RightDuty = 0.0;

    /* Disable for SignalConversion generated from: '<S8>/Front Duty' incorporates:
     *  Outport: '<S8>/Out2'
     */
    metux_model_6dof_only_control_B.FrontDuty = 0.0;

    /* Disable for SignalConversion generated from: '<S8>/Left Duty' incorporates:
     *  Outport: '<S8>/Out3'
     */
    metux_model_6dof_only_control_B.LeftDuty = 0.0;

    /* Disable for SignalConversion generated from: '<S8>/Back Duty' incorporates:
     *  Outport: '<S8>/Out4'
     */
    metux_model_6dof_only_control_B.BackDuty = 0.0;
    metux_model_6dof_only_contro_DW.ESTOPOverride_MODE = false;
  }

  /* End of Logic: '<Root>/NOT' */
  /* End of Outputs for SubSystem: '<Root>/E-STOP Override' */

  /* Switch: '<S378>/Switch2' incorporates:
   *  Inport: '<Root>/Right Motor Angle'
   *  RelationalOperator: '<S378>/LowerRelop1'
   *  Switch: '<S15>/Switch1'
   */
  if (metux_model_6dof_only_control_B.RightDuty > rtb_Product2_k) {
    /* Outport: '<Root>/Right Duty' */
    metux_model_6dof_only_control_Y.RightDuty = rtb_Product2_k;
  } else {
    if (metux_model_6dof_only_control_U.RightMotorAngle > 2.0) {
      /* Switch: '<S15>/Switch1' incorporates:
       *  Constant: '<S15>/Constant1'
       */
      i = -1;
    } else {
      /* Switch: '<S15>/Switch1' incorporates:
       *  Constant: '<S15>/Constant4'
       */
      i = 0;
    }

    /* Switch: '<S378>/Switch' incorporates:
     *  RelationalOperator: '<S378>/UpperRelop'
     */
    if (metux_model_6dof_only_control_B.RightDuty < i) {
      /* Outport: '<Root>/Right Duty' */
      metux_model_6dof_only_control_Y.RightDuty = i;
    } else {
      /* Outport: '<Root>/Right Duty' */
      metux_model_6dof_only_control_Y.RightDuty =
        metux_model_6dof_only_control_B.RightDuty;
    }

    /* End of Switch: '<S378>/Switch' */
  }

  /* End of Switch: '<S378>/Switch2' */

  /* Switch: '<S16>/Switch' incorporates:
   *  Inport: '<Root>/Front Motor Angle'
   */
  rtb_Saturation_m = (metux_model_6dof_only_control_U.FrontMotorAngle <= 1440.0);

  /* Switch: '<S379>/Switch2' incorporates:
   *  Inport: '<Root>/Front Motor Angle'
   *  RelationalOperator: '<S379>/LowerRelop1'
   *  Switch: '<S16>/Switch1'
   */
  if (metux_model_6dof_only_control_B.FrontDuty > rtb_Saturation_m) {
    /* Outport: '<Root>/Front Duty' */
    metux_model_6dof_only_control_Y.FrontDuty = rtb_Saturation_m;
  } else {
    if (metux_model_6dof_only_control_U.FrontMotorAngle > 2.0) {
      /* Switch: '<S16>/Switch1' incorporates:
       *  Constant: '<S16>/Constant1'
       */
      i = -1;
    } else {
      /* Switch: '<S16>/Switch1' incorporates:
       *  Constant: '<S16>/Constant4'
       */
      i = 0;
    }

    /* Switch: '<S379>/Switch' incorporates:
     *  RelationalOperator: '<S379>/UpperRelop'
     */
    if (metux_model_6dof_only_control_B.FrontDuty < i) {
      /* Outport: '<Root>/Front Duty' */
      metux_model_6dof_only_control_Y.FrontDuty = i;
    } else {
      /* Outport: '<Root>/Front Duty' */
      metux_model_6dof_only_control_Y.FrontDuty =
        metux_model_6dof_only_control_B.FrontDuty;
    }

    /* End of Switch: '<S379>/Switch' */
  }

  /* End of Switch: '<S379>/Switch2' */

  /* Switch: '<S17>/Switch' incorporates:
   *  Inport: '<Root>/Left Motor Angle'
   */
  rtb_Saturation_m = (metux_model_6dof_only_control_U.LeftMotorAngle <= 1440.0);

  /* Switch: '<S380>/Switch2' incorporates:
   *  Inport: '<Root>/Left Motor Angle'
   *  RelationalOperator: '<S380>/LowerRelop1'
   *  Switch: '<S17>/Switch1'
   */
  if (metux_model_6dof_only_control_B.LeftDuty > rtb_Saturation_m) {
    /* Outport: '<Root>/Left Duty' */
    metux_model_6dof_only_control_Y.LeftDuty = rtb_Saturation_m;
  } else {
    if (metux_model_6dof_only_control_U.LeftMotorAngle > 2.0) {
      /* Switch: '<S17>/Switch1' incorporates:
       *  Constant: '<S17>/Constant1'
       */
      i = -1;
    } else {
      /* Switch: '<S17>/Switch1' incorporates:
       *  Constant: '<S17>/Constant4'
       */
      i = 0;
    }

    /* Switch: '<S380>/Switch' incorporates:
     *  RelationalOperator: '<S380>/UpperRelop'
     */
    if (metux_model_6dof_only_control_B.LeftDuty < i) {
      /* Outport: '<Root>/Left Duty' */
      metux_model_6dof_only_control_Y.LeftDuty = i;
    } else {
      /* Outport: '<Root>/Left Duty' */
      metux_model_6dof_only_control_Y.LeftDuty =
        metux_model_6dof_only_control_B.LeftDuty;
    }

    /* End of Switch: '<S380>/Switch' */
  }

  /* End of Switch: '<S380>/Switch2' */

  /* Switch: '<S18>/Switch' incorporates:
   *  Inport: '<Root>/Back Motor Angle'
   */
  rtb_Saturation_m = (metux_model_6dof_only_control_U.BackMotorAngle <= 1440.0);

  /* Switch: '<S381>/Switch2' incorporates:
   *  Inport: '<Root>/Back Motor Angle'
   *  RelationalOperator: '<S381>/LowerRelop1'
   *  Switch: '<S18>/Switch1'
   */
  if (metux_model_6dof_only_control_B.BackDuty > rtb_Saturation_m) {
    /* Outport: '<Root>/Back Duty' */
    metux_model_6dof_only_control_Y.BackDuty = rtb_Saturation_m;
  } else {
    if (metux_model_6dof_only_control_U.BackMotorAngle > 2.0) {
      /* Switch: '<S18>/Switch1' incorporates:
       *  Constant: '<S18>/Constant1'
       */
      i = -1;
    } else {
      /* Switch: '<S18>/Switch1' incorporates:
       *  Constant: '<S18>/Constant4'
       */
      i = 0;
    }

    /* Switch: '<S381>/Switch' incorporates:
     *  RelationalOperator: '<S381>/UpperRelop'
     */
    if (metux_model_6dof_only_control_B.BackDuty < i) {
      /* Outport: '<Root>/Back Duty' */
      metux_model_6dof_only_control_Y.BackDuty = i;
    } else {
      /* Outport: '<Root>/Back Duty' */
      metux_model_6dof_only_control_Y.BackDuty =
        metux_model_6dof_only_control_B.BackDuty;
    }

    /* End of Switch: '<S381>/Switch' */
  }

  /* End of Switch: '<S381>/Switch2' */

  /* Outport: '<Root>/height_filtered' incorporates:
   *  DiscreteIntegrator: '<S143>/Integrator'
   */
  metux_model_6dof_only_control_Y.height_filtered =
    metux_model_6dof_only_contro_DW.Integrator_DSTATE_m;

  /* Logic: '<S144>/Logical Operator' incorporates:
   *  Constant: '<S144>/Time constant'
   *  Constant: '<S148>/Constant'
   *  RelationalOperator: '<S148>/Compare'
   *  Sum: '<S144>/Sum1'
   */
  rtb_AND2 = (0.02 - metux_model_6dof_only_control_B.Probe_h[0] <= 0.0);

  /* Sqrt: '<S643>/sqrt' incorporates:
   *  Inport: '<Root>/quaternion'
   *  Product: '<S644>/Product'
   *  Product: '<S644>/Product1'
   *  Product: '<S644>/Product2'
   *  Product: '<S644>/Product3'
   *  Sum: '<S644>/Sum'
   */
  rtb_Saturation_m = sqrt(((metux_model_6dof_only_control_U.quaternion[0] *
    metux_model_6dof_only_control_U.quaternion[0] +
    metux_model_6dof_only_control_U.quaternion[1] *
    metux_model_6dof_only_control_U.quaternion[1]) +
    metux_model_6dof_only_control_U.quaternion[2] *
    metux_model_6dof_only_control_U.quaternion[2]) +
    metux_model_6dof_only_control_U.quaternion[3] *
    metux_model_6dof_only_control_U.quaternion[3]);

  /* Product: '<S642>/Product' incorporates:
   *  Inport: '<Root>/quaternion'
   */
  rtb_Filter_j = metux_model_6dof_only_control_U.quaternion[0] /
    rtb_Saturation_m;

  /* Product: '<S642>/Product1' incorporates:
   *  Inport: '<Root>/quaternion'
   */
  rtb_Filter = metux_model_6dof_only_control_U.quaternion[1] / rtb_Saturation_m;

  /* Product: '<S642>/Product2' incorporates:
   *  Inport: '<Root>/quaternion'
   */
  rtb_Product2_k = metux_model_6dof_only_control_U.quaternion[2] /
    rtb_Saturation_m;

  /* Product: '<S642>/Product3' incorporates:
   *  Inport: '<Root>/quaternion'
   */
  rtb_Saturation_m = metux_model_6dof_only_control_U.quaternion[3] /
    rtb_Saturation_m;

  /* Gain: '<S634>/Gain' incorporates:
   *  Product: '<S634>/Product1'
   *  Product: '<S634>/Product2'
   *  Sum: '<S634>/Sum'
   */
  rtb_DeadZone = (rtb_Filter * rtb_Saturation_m - rtb_Filter_j * rtb_Product2_k)
    * 2.0;

  /* If: '<S603>/If' incorporates:
   *  Concatenate: '<S641>/Vector Concatenate'
   *  Gain: '<S607>/Gain1'
   *  Selector: '<S607>/Selector1'
   */
  if ((-rtb_DeadZone >= 1.0) || (-rtb_DeadZone <= -1.0)) {
    /* Outputs for IfAction SubSystem: '<S603>/AxisRotZeroR3' incorporates:
     *  ActionPort: '<S606>/Action Port'
     */
    /* Fcn: '<S606>/Fcn1' incorporates:
     *  Gain: '<S607>/Gain3'
     *  Gain: '<S635>/Gain'
     *  Product: '<S635>/Product2'
     *  Product: '<S635>/Product3'
     *  Product: '<S636>/Product'
     *  Product: '<S636>/Product1'
     *  Product: '<S636>/Product2'
     *  Product: '<S636>/Product3'
     *  Sum: '<S635>/Sum'
     *  Sum: '<S636>/Sum'
     */
    rtb_Switch_di = atan2(-((rtb_Filter * rtb_Product2_k - rtb_Saturation_m *
      rtb_Filter_j) * 2.0), ((rtb_Filter_j * rtb_Filter_j - rtb_Filter *
      rtb_Filter) + rtb_Product2_k * rtb_Product2_k) - rtb_Saturation_m *
                          rtb_Saturation_m);

    /* If: '<S613>/If' incorporates:
     *  Constant: '<S614>/Constant'
     *  Constant: '<S615>/Constant'
     *  Fcn: '<S606>/Fcn2'
     */
    if (-rtb_DeadZone > 1.0) {
      /* Outputs for IfAction SubSystem: '<S613>/If Action Subsystem' incorporates:
       *  ActionPort: '<S614>/Action Port'
       */
      rtb_Saturation_m = 1.0;

      /* End of Outputs for SubSystem: '<S613>/If Action Subsystem' */
    } else if (-rtb_DeadZone < -1.0) {
      /* Outputs for IfAction SubSystem: '<S613>/If Action Subsystem1' incorporates:
       *  ActionPort: '<S615>/Action Port'
       */
      rtb_Saturation_m = 1.0;

      /* End of Outputs for SubSystem: '<S613>/If Action Subsystem1' */
    } else {
      rtb_Saturation_m = -rtb_DeadZone;
    }

    rtb_DeadZone = asin(rtb_Saturation_m);

    /* End of If: '<S613>/If' */

    /* Fcn: '<S606>/Fcn3' */
    rtb_Product2_k = 0.0;

    /* End of Outputs for SubSystem: '<S603>/AxisRotZeroR3' */
  } else {
    /* Product: '<S632>/Product3' incorporates:
     *  Product: '<S640>/Product3'
     */
    rtb_FilterCoefficient_pz = rtb_Filter_j * rtb_Filter_j;

    /* Product: '<S632>/Product2' incorporates:
     *  Product: '<S640>/Product2'
     */
    rtb_FilterCoefficient_ih = rtb_Filter * rtb_Filter;

    /* Product: '<S632>/Product1' incorporates:
     *  Product: '<S640>/Product1'
     */
    TmpSignalConversionAtDiscreteFI = rtb_Product2_k * rtb_Product2_k;

    /* Product: '<S632>/Product' incorporates:
     *  Product: '<S640>/Product'
     */
    rtb_FilterCoefficient_a = rtb_Saturation_m * rtb_Saturation_m;

    /* Outputs for IfAction SubSystem: '<S603>/AxisRotDefault' incorporates:
     *  ActionPort: '<S605>/Action Port'
     */
    /* Fcn: '<S605>/Fcn1' incorporates:
     *  Gain: '<S633>/Gain'
     *  Product: '<S632>/Product'
     *  Product: '<S632>/Product1'
     *  Product: '<S632>/Product2'
     *  Product: '<S632>/Product3'
     *  Product: '<S633>/Product2'
     *  Product: '<S633>/Product3'
     *  Sum: '<S632>/Sum'
     *  Sum: '<S633>/Sum'
     */
    rtb_Switch_di = atan2((rtb_Saturation_m * rtb_Filter_j + rtb_Filter *
      rtb_Product2_k) * 2.0, ((rtb_FilterCoefficient_pz +
      rtb_FilterCoefficient_ih) - TmpSignalConversionAtDiscreteFI) -
                          rtb_FilterCoefficient_a);

    /* Fcn: '<S605>/Fcn2' */
    rtb_DeadZone = asin(-rtb_DeadZone);

    /* Fcn: '<S605>/Fcn3' incorporates:
     *  Gain: '<S637>/Gain'
     *  Product: '<S637>/Product1'
     *  Product: '<S637>/Product2'
     *  Sum: '<S637>/Sum'
     *  Sum: '<S640>/Sum'
     */
    rtb_Product2_k = atan2((rtb_Filter_j * rtb_Filter + rtb_Product2_k *
      rtb_Saturation_m) * 2.0, ((rtb_FilterCoefficient_pz -
      rtb_FilterCoefficient_ih) - TmpSignalConversionAtDiscreteFI) +
      rtb_FilterCoefficient_a);

    /* End of Outputs for SubSystem: '<S603>/AxisRotDefault' */
  }

  /* End of If: '<S603>/If' */

  /* DiscreteIntegrator: '<S150>/Integrator' */
  if (metux_model_6dof_only_contro_DW.Integrator_IC_LOADING_e != 0) {
    metux_model_6dof_only_contro_DW.Integrator_DSTATE_e[0] = rtb_Switch_di;
    metux_model_6dof_only_contro_DW.Integrator_DSTATE_e[1] = rtb_DeadZone;
    metux_model_6dof_only_contro_DW.Integrator_DSTATE_e[2] = rtb_Product2_k;
  }

  if (rtb_AND2 || (metux_model_6dof_only_contro_DW.Integrator_PrevResetState_n
                   != 0)) {
    metux_model_6dof_only_contro_DW.Integrator_DSTATE_e[0] = rtb_Switch_di;
    metux_model_6dof_only_contro_DW.Integrator_DSTATE_e[1] = rtb_DeadZone;
    metux_model_6dof_only_contro_DW.Integrator_DSTATE_e[2] = rtb_Product2_k;
  }

  /* Outport: '<Root>/euler calculated' incorporates:
   *  DiscreteIntegrator: '<S150>/Integrator'
   *  Gain: '<S21>/Gain'
   */
  metux_model_6dof_only_control_Y.eulercalculated[0] = 57.295779513082323 *
    metux_model_6dof_only_contro_DW.Integrator_DSTATE_e[0];
  metux_model_6dof_only_control_Y.eulercalculated[1] = 57.295779513082323 *
    metux_model_6dof_only_contro_DW.Integrator_DSTATE_e[1];
  metux_model_6dof_only_control_Y.eulercalculated[2] = 57.295779513082323 *
    metux_model_6dof_only_contro_DW.Integrator_DSTATE_e[2];

  /* Update for UnitDelay: '<S6>/Delay Input1' incorporates:
   *  Inport: '<Root>/Activate'
   *
   * Block description for '<S6>/Delay Input1':
   *
   *  Store in Global RAM
   */
  metux_model_6dof_only_contro_DW.DelayInput1_DSTATE =
    metux_model_6dof_only_control_U.Activate;

  /* Update for DiscreteIntegrator: '<S157>/Integrator' */
  metux_model_6dof_only_contro_DW.Integrator_IC_LOADING = 0U;

  /* Product: '<S13>/1//T' incorporates:
   *  Constant: '<S151>/Time constant'
   *  MinMax: '<S151>/Max'
   */
  rtb_Saturation_m = 1.0 / fmax(metux_model_6dof_only_control_B.Probe[0], 0.02);

  /* Update for DiscreteIntegrator: '<S157>/Integrator' incorporates:
   *  Inport: '<Root>/euler_measured'
   *  Product: '<S13>/1//T'
   *  Sum: '<S13>/Sum1'
   */
  metux_model_6dof_only_contro_DW.Integrator_DSTATE[0] +=
    (metux_model_6dof_only_control_U.euler_measured[0] -
     metux_model_6dof_only_contro_DW.Integrator_DSTATE[0]) * rtb_Saturation_m *
    0.001;
  metux_model_6dof_only_contro_DW.Integrator_DSTATE[1] +=
    (metux_model_6dof_only_control_U.euler_measured[1] -
     metux_model_6dof_only_contro_DW.Integrator_DSTATE[1]) * rtb_Saturation_m *
    0.001;
  metux_model_6dof_only_contro_DW.Integrator_DSTATE[2] +=
    (metux_model_6dof_only_control_U.euler_measured[2] -
     metux_model_6dof_only_contro_DW.Integrator_DSTATE[2]) * rtb_Saturation_m *
    0.001;
  metux_model_6dof_only_contro_DW.Integrator_PrevResetState = (int8_T)
    rtb_LogicalOperator;

  /* Update for DiscreteIntegrator: '<S143>/Integrator' incorporates:
   *  Constant: '<S137>/Time constant'
   *  MinMax: '<S137>/Max'
   *  Product: '<S11>/1//T'
   *  Sum: '<S11>/Sum1'
   */
  metux_model_6dof_only_contro_DW.Integrator_IC_LOADING_p = 0U;
  metux_model_6dof_only_contro_DW.Integrator_DSTATE_m += 1.0 / fmax
    (metux_model_6dof_only_control_B.Probe_b[0], 0.02) *
    (rtb_FilterCoefficient_j -
     metux_model_6dof_only_contro_DW.Integrator_DSTATE_m) * 0.001;
  metux_model_6dof_only_contro_DW.Integrator_PrevResetState_h = (int8_T)
    rtb_LogicalOperator_f;

  /* Update for UnitDelay: '<S645>/UD'
   *
   * Block description for '<S645>/UD':
   *
   *  Store in Global RAM
   */
  metux_model_6dof_only_contro_DW.UD_DSTATE = rtb_Switch_kt;

  /* Update for UnitDelay: '<S7>/UD'
   *
   * Block description for '<S7>/UD':
   *
   *  Store in Global RAM
   */
  metux_model_6dof_only_contro_DW.UD_DSTATE_e = rtb_FilterCoefficient_h;

  /* Update for DiscreteFir: '<Root>/Discrete FIR Filter1' incorporates:
   *  Inport: '<Root>/N1 pressure'
   *  Inport: '<Root>/N2 pressure'
   *  Inport: '<Root>/N3 pressure'
   *  Inport: '<Root>/N4 pressure'
   */
  /* Update circular buffer index */
  metux_model_6dof_only_contro_DW.DiscreteFIRFilter1_circBuf--;
  if (metux_model_6dof_only_contro_DW.DiscreteFIRFilter1_circBuf < 0) {
    metux_model_6dof_only_contro_DW.DiscreteFIRFilter1_circBuf = 5;
  }

  /* Update circular buffer */
  metux_model_6dof_only_contro_DW.DiscreteFIRFilter1_states[metux_model_6dof_only_contro_DW.DiscreteFIRFilter1_circBuf]
    = metux_model_6dof_only_control_U.N1pressure;
  metux_model_6dof_only_contro_DW.DiscreteFIRFilter1_states[metux_model_6dof_only_contro_DW.DiscreteFIRFilter1_circBuf
    + 6] = metux_model_6dof_only_control_U.N2pressure;
  metux_model_6dof_only_contro_DW.DiscreteFIRFilter1_states[metux_model_6dof_only_contro_DW.DiscreteFIRFilter1_circBuf
    + 12] = metux_model_6dof_only_control_U.N3pressure;
  metux_model_6dof_only_contro_DW.DiscreteFIRFilter1_states[metux_model_6dof_only_contro_DW.DiscreteFIRFilter1_circBuf
    + 18] = metux_model_6dof_only_control_U.N4pressure;

  /* End of Update for DiscreteFir: '<Root>/Discrete FIR Filter1' */

  /* Update for DiscreteIntegrator: '<S150>/Integrator' */
  metux_model_6dof_only_contro_DW.Integrator_IC_LOADING_e = 0U;

  /* Product: '<S12>/1//T' incorporates:
   *  Constant: '<S144>/Time constant'
   *  MinMax: '<S144>/Max'
   */
  rtb_Saturation_m = 1.0 / fmax(metux_model_6dof_only_control_B.Probe_h[0], 0.02);

  /* Update for DiscreteIntegrator: '<S150>/Integrator' incorporates:
   *  Product: '<S12>/1//T'
   *  Sum: '<S12>/Sum1'
   */
  metux_model_6dof_only_contro_DW.Integrator_DSTATE_e[0] += (rtb_Switch_di -
    metux_model_6dof_only_contro_DW.Integrator_DSTATE_e[0]) * rtb_Saturation_m *
    0.001;
  metux_model_6dof_only_contro_DW.Integrator_DSTATE_e[1] += (rtb_DeadZone -
    metux_model_6dof_only_contro_DW.Integrator_DSTATE_e[1]) * rtb_Saturation_m *
    0.001;
  metux_model_6dof_only_contro_DW.Integrator_DSTATE_e[2] += (rtb_Product2_k -
    metux_model_6dof_only_contro_DW.Integrator_DSTATE_e[2]) * rtb_Saturation_m *
    0.001;
  metux_model_6dof_only_contro_DW.Integrator_PrevResetState_n = (int8_T)rtb_AND2;
}

/* Model initialize function */
void metux_model_6dof_only_controller_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(metux_model_6dof_only_contro_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &metux_model_6dof_only_control_B), 0,
                sizeof(B_metux_model_6dof_only_contr_T));

  /* states (dwork) */
  (void) memset((void *)&metux_model_6dof_only_contro_DW, 0,
                sizeof(DW_metux_model_6dof_only_cont_T));

  /* external inputs */
  (void)memset(&metux_model_6dof_only_control_U, 0, sizeof
               (ExtU_metux_model_6dof_only_co_T));

  /* external outputs */
  (void)memset(&metux_model_6dof_only_control_Y, 0, sizeof
               (ExtY_metux_model_6dof_only_co_T));

  /* Start for Probe: '<S151>/Probe' */
  metux_model_6dof_only_control_B.Probe[0] = 0.001;
  metux_model_6dof_only_control_B.Probe[1] = 0.0;

  /* Start for Probe: '<S137>/Probe' */
  metux_model_6dof_only_control_B.Probe_b[0] = 0.001;
  metux_model_6dof_only_control_B.Probe_b[1] = 0.0;

  /* Start for Probe: '<S144>/Probe' */
  metux_model_6dof_only_control_B.Probe_h[0] = 0.001;
  metux_model_6dof_only_control_B.Probe_h[1] = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S157>/Integrator' */
  metux_model_6dof_only_contro_DW.Integrator_PrevResetState = 0;
  metux_model_6dof_only_contro_DW.Integrator_IC_LOADING = 1U;

  /* InitializeConditions for DiscreteIntegrator: '<S143>/Integrator' */
  metux_model_6dof_only_contro_DW.Integrator_PrevResetState_h = 0;
  metux_model_6dof_only_contro_DW.Integrator_IC_LOADING_p = 1U;

  /* InitializeConditions for UnitDelay: '<S645>/UD'
   *
   * Block description for '<S645>/UD':
   *
   *  Store in Global RAM
   */
  metux_model_6dof_only_contro_DW.UD_DSTATE = (10.0 -
    metux_model_6dof_only_control_P.lidar_height / 1000.0) /
    metux_model_6dof_only_control_P.AltitudeController.dT;

  /* InitializeConditions for DiscreteFir: '<Root>/Discrete FIR Filter1' */
  metux_model_6dof_only_contro_DW.DiscreteFIRFilter1_circBuf = 0;
  memset(&metux_model_6dof_only_contro_DW.DiscreteFIRFilter1_states[0], 0, 24U *
         sizeof(real_T));

  /* InitializeConditions for DiscreteIntegrator: '<S150>/Integrator' */
  metux_model_6dof_only_contro_DW.Integrator_PrevResetState_n = 0;
  metux_model_6dof_only_contro_DW.Integrator_IC_LOADING_e = 1U;

  /* SystemInitialize for Enabled SubSystem: '<Root>/Motor Position Controllers' */
  /* InitializeConditions for RateLimiter: '<S14>/Rate Limiter' */
  metux_model_6dof_only_contro_DW.PrevY_n = 0.0;

  /* End of SystemInitialize for SubSystem: '<Root>/Motor Position Controllers' */

  /* SystemInitialize for Enabled SubSystem: '<Root>/Vertical Speed Controller' */
  /* InitializeConditions for RateLimiter: '<S23>/Rate Limiter' */
  metux_model_6dof_only_contro_DW.PrevY = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S683>/Integrator' */
  metux_model_6dof_only_contro_DW.Integrator_DSTATE_d = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S678>/Filter' */
  metux_model_6dof_only_contro_DW.Filter_DSTATE = 0.0;

  /* End of SystemInitialize for SubSystem: '<Root>/Vertical Speed Controller' */

  /* SystemInitialize for Enabled SubSystem: '<Root>/Attitude Controller' */
  /* InitializeConditions for DiscreteFir: '<S1>/Discrete FIR Filter' */
  metux_model_6dof_only_contro_DW.DiscreteFIRFilter_circBuf = 0;
  memset(&metux_model_6dof_only_contro_DW.DiscreteFIRFilter_states[0], 0, 18U *
         sizeof(real_T));

  /* InitializeConditions for DiscreteIntegrator: '<S119>/Integrator' */
  metux_model_6dof_only_contro_DW.Integrator_DSTATE_ku = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S114>/Filter' */
  metux_model_6dof_only_contro_DW.Filter_DSTATE_f2 = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S65>/Integrator' */
  metux_model_6dof_only_contro_DW.Integrator_DSTATE_ky = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S60>/Filter' */
  metux_model_6dof_only_contro_DW.Filter_DSTATE_ft = 0.0;

  /* End of SystemInitialize for SubSystem: '<Root>/Attitude Controller' */

  /* SystemInitialize for Enabled SubSystem: '<Root>/Pressure Controllers' */
  /* InitializeConditions for RateLimiter: '<S19>/Rate Limiter' */
  metux_model_6dof_only_contro_DW.PrevY_i = 0.0;

  /* InitializeConditions for RateLimiter: '<S19>/Rate Limiter1' */
  metux_model_6dof_only_contro_DW.PrevY_m = 0.0;

  /* InitializeConditions for RateLimiter: '<S19>/Rate Limiter2' */
  metux_model_6dof_only_contro_DW.PrevY_a = 0.0;

  /* InitializeConditions for RateLimiter: '<S19>/Rate Limiter3' */
  metux_model_6dof_only_contro_DW.PrevY_g = 0.0;

  /* End of SystemInitialize for SubSystem: '<Root>/Pressure Controllers' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
