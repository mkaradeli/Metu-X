/*
 * Motor.cpp
 *
 *  Created on: Aug 2, 2025
 *      Author: alica
 */
#include "Motor.hpp"
#include <math.h>

Motor::Motor(GPIO_TypeDef* leftPort, uint16_t leftPin, GPIO_TypeDef* rightPort, uint16_t rightPin, TIM_HandleTypeDef* pwmTimer, uint8_t pwmChannel) {
	this->left_port = leftPort;
	this->left_pin = leftPin;
	this->right_port = rightPort;
	this->right_pin = rightPin;
	this->PWM_Timer = pwmTimer;
	this->PWM_Channel = pwmChannel;
}

void Motor::updatePosition(uint16_t prev_raw, uint16_t raw){
	this->delta_raw = raw - prev_raw;

	if (this->delta_raw > HALF_ADC_MAX){
		this->delta_raw -= ADC_MAX;
	}
	else if (this->delta_raw < -HALF_ADC_MAX){
		this->delta_raw += ADC_MAX;
	}

	position_degree += this->delta_raw*360.0f / ADC_MAX;
}

float Motor::getPositionDegree(){
	return this->position_degree;
}

float Motor::getPositionRadian(){
	return this->position_degree * (M_PI / 180.0f);
}

/*** Set Speed of Motor. Resolution is 12 bit ***/
void Motor::setSpeed(uint16_t duty_cycle){
	__HAL_TIM_SET_COMPARE(this->PWM_Timer, this->PWM_Channel, duty_cycle);
}

void Motor::setDirectionClockwise(){
	HAL_GPIO_WritePin(this->left_port, this->left_pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(this->right_port, this->right_pin, GPIO_PIN_RESET);
}

void Motor::setDirectionCounterClockwise(){
	HAL_GPIO_WritePin(this->left_port, this->left_pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(this->right_port, this->right_pin, GPIO_PIN_SET);
}

void Motor::releaseMotor(){
	HAL_GPIO_WritePin(this->left_port, this->left_pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(this->right_port, this->right_pin, GPIO_PIN_RESET);
}
