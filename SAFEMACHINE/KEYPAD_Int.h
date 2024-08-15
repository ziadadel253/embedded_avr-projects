/*
 * KEYPAD_Int.h
 *
 * Created: 4/28/2024 8:24:06 PM
 *  Author: LENOVO
 */ 


#ifndef KEYPAD_INT_H_
#define KEYPAD_INT_H_

void KEYPAD_Init(void);

u8 KEYPAD_GETKEYS(void);

u16 KEYPAD_CONVERTER(u16 num,u8 from,u8 to);

#define NO_KEY 'T'

typedef enum{
	DEC,
	BIN,
	HEX
	
	}converter_type;


#endif /* KEYPAD_INT_H_ */