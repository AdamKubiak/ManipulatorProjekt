#include "InverseKinematics.h"
#include "math.h"
#include "stdlib.h"



const float  a2 = 6; // joint length 1
const float  a4 = 5;// joint length 2

int Theta1(int angle)
{
	if(angle<0)
			  angle = abs(angle);
	int  value;
	  int minC=1600;
	  int maxC=7800;
	  int minA=0;
	  int maxA=180;
	  value = ((maxC-minC)/(maxA-minA))*(angle-minA)+minC;
	  return value;
}

int Theta2(int angle)
{
	int  value;
	  int minC=1600;
	  int maxC=7800;
	  int minA=-90;
	  int maxA=90;
	  value = ((maxC-minC)/(maxA-minA))*(angle-minA)+minC;

	  return value;
}

int Theta3(int angle)
{
	int  value;
	  int minC=1600;
	  int maxC=7600;
	  int minA=0;
	  int maxA=180;
	  value = ((maxC-minC)/(maxA-minA))*(angle-minA)+minC;

	  return value;
}

void InverseKinematics(float X, float Y,servo *obiekt)//odwrotna kinematyka dla przypadku gdy pierwsze servo porusza się od 0 do 180
{
	float r,phi1,phi2,phi3, T1,T2;


	  r = sqrt((X*X)+(Y*Y));
	  phi1 = acos(((a4*a4)-(a2*a2)-(r*r))/(-2.0*a2*r));
	  phi2 = atan(Y/X);
	  T1 = phi2-phi1;
	  phi3 = acos(((r*r)-(a2*a2)-(a4*a4))/(-2.0*a2*a4));
	  T2 = 3.14159-phi3;
	  obiekt->servo1 = T1;
	  obiekt->servo2 = T2;

}
//void InverseKinematics(float X, float Y,servo *obiekt)//odwrotna kinematyka dla przypadku gdy pierwsze servo porusza się od -90 do 90
//{
//	float r,phi1,phi2,phi3, T1,T2;
//
//
//	  r = sqrt((X*X)+(Y*Y));
//	  phi1 = acos(((a4*a4)-(a2*a2)-(r*r))/(-2.0*a2*r));
//	  phi2 = atan(Y/X);
//	  T1 = phi2-phi1;
//	  phi3 = acos(((r*r)-(a2*a2)-(a4*a4))/(-2.0*a2*a4));
//	  T2 = 3.14159-phi3;
//	  obiekt->servo1 = T1;
//	  obiekt->servo2 = T2;
//
//}
