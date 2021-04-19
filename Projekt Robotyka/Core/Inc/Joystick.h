

#ifndef INC_JOYSTICK_H_
#define INC_JOYSTICK_H_

#include "InverseKinematics.h"


typedef struct
{
	uint16_t position[2];

}joystick;

void joystick_Start(ADC_HandleTypeDef *hadc, joystick *obiekt)
{
	HAL_ADC_Start_DMA(hadc, obiekt->position , 2);
}

void joystick_Stop(ADC_HandleTypeDef *hadc)
{
	HAL_ADC_Stop_DMA(hadc);
}

int voltageToAngleX(const joystick obiekt)
{

		int  value;
		  int minC=1600;
		  int maxC=7800;
		  int minA=4;
		  int maxA=4095;
		  value = 1600+(obiekt.position[0]*1.514);;



		  return value;

}
int voltageToAngleY(const joystick obiekt)
{

		int  value;
		  int minC=1600;
		  int maxC=7800;
		  int minA=4;
		  int maxA=4095;
		  value = 1600+(obiekt.position[1]*1.514);



		  return value;

}

void joystick_Control(TIM_HandleTypeDef *htim,const joystick obiekt)
{


	__HAL_TIM_SET_COMPARE(htim,TIM_CHANNEL_2,voltageToAngleX(obiekt));
	__HAL_TIM_SET_COMPARE(htim,TIM_CHANNEL_3,voltageToAngleY(obiekt));
}

#endif /* INC_JOYSTICK_H_ */
