#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "stm32f4xx.h"


void servo_Init(TIM_HandleTypeDef *htim);
//void servo_Write(TIM_HandleTypeDef *htim,int CHANNEL, int angle);

#endif /* INC_SERVO_H_ */
