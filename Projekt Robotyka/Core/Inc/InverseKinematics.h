/*
 * InverseKinematics.h
 *
 *  Created on: Feb 27, 2021
 *      Author: john
 */

#ifndef INC_INVERSEKINEMATICS_H_
#define INC_INVERSEKINEMATICS_H_


typedef struct
{
	float servo1;
	float servo2;
	float servo3;
}servo;

float Theta1(float angle);
float Theta2(float angle);
float Theta3(float angle);
void InverseKinematics(float X, float Y,servo *obiekt);




#endif /* INC_INVERSEKINEMATICS_H_ */
