/*
 * motor_Int.h
 *
 * Created: 7/22/2024 3:46:56 PM
 *  Author: LENOVO
 */ 


#ifndef MOTOR_INT_H_
#define MOTOR_INT_H_



typedef enum{
	M1=0,
	M2,
	M3,
	M4
}MOTOR_t;



void MOTOR_Stop(MOTOR_t m);

void MOTOR_CW(MOTOR_t m);

void MOTOR_CCW(MOTOR_t m);


#endif /* MOTOR_INT_H_ */