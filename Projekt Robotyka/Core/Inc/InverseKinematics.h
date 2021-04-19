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

int Theta1(int angle);
int Theta2(int angle);
int Theta3(int angle);
void InverseKinematics(float X, float Y,servo *obiekt);




#endif /* INC_INVERSEKINEMATICS_H_ */
