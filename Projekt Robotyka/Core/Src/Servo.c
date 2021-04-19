#include "Servo.h"
#include "stm32f4xx.h"


void servo_Init(TIM_HandleTypeDef *htim)
{
	HAL_TIM_PWM_Start(htim, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(htim, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(htim, TIM_CHANNEL_4);

}


