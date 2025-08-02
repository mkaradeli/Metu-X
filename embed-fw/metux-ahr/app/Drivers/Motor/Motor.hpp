/*
 * Motor.hpp
 *
 *  Created on: Aug 2, 2025
 *      Author: alica
 */

#ifndef DRIVERS_MOTOR_MOTOR_HPP_
#define DRIVERS_MOTOR_MOTOR_HPP_

#define MAX_MOTOR_COUNT 4

#include <stdint.h>
#include "gpio.h"
#include "tim.h"

const uint16_t ADC_MAX = 65535;
const uint16_t HALF_ADC_MAX = ADC_MAX/2;
class Motor {
	public:
		Motor(GPIO_TypeDef* leftPort, uint16_t leftPin, GPIO_TypeDef* rightPort, uint16_t rightPin, TIM_HandleTypeDef* pwmTimer, uint8_t pwmChannel);
		void updatePosition(uint16_t prev_raw, uint16_t raw);
		float getPositionDegree();
		float getPositionRadian();

		void setDirectionClockwise();
		void setDirectionCounterClockwise();
		void releaseMotor();
		void setSpeed(uint16_t duty_cycle);

	private:
		GPIO_TypeDef* left_port;
		uint16_t left_pin;
		GPIO_TypeDef* right_port;
		uint16_t right_pin;

		TIM_HandleTypeDef* PWM_Timer;
		uint8_t PWM_Channel;

		float position_degree = 0;
		int32_t delta_raw = 0;
};


#endif /* DRIVERS_MOTOR_MOTOR_HPP_ */
