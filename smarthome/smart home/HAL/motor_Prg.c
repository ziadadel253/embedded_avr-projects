#include "StdTypes.h"

#include "DIO_Int.h"

#include "MOTOR_Int.h"
#include "MOTOR_Cfg.h"


void MOTOR_Stop(MOTOR_t m)
{
	switch(m)
	{
		case M1:
		DIO_WritePin(M1_IN1,LOW);
		DIO_WritePin(M1_IN2,LOW);
		break;
		case M2:
		DIO_WritePin(M2_IN1,LOW);
		DIO_WritePin(M2_IN2,LOW);
		break;
		
	}
}
void MOTOR_CW(MOTOR_t m)
{
	switch(m)
	{
		case M1:
		DIO_WritePin(M1_IN1,LOW);
		DIO_WritePin(M1_IN2,HIGH);
		break;
		case M2:
		DIO_WritePin(M2_IN1,LOW);
		DIO_WritePin(M2_IN2,HIGH);
		break;
		
	}
	
	
}
void MOTOR_CCW(MOTOR_t m)
{
	switch(m)
	{
		case M1:
		DIO_WritePin(M1_IN1,HIGH);
		DIO_WritePin(M1_IN2,LOW);
		break;
		case M2:
		DIO_WritePin(M2_IN1,HIGH);
		DIO_WritePin(M2_IN2,LOW);
		break;
		
	}
}