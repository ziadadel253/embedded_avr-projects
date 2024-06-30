#define KEYPAD_PRG 1

#define  F_CPU  8000000
#include "util/delay.h"

#include "StdTypes.h"
#include "DIO_Int.h"
#include "KEYPAD_Int.h"
#include "KEYPAD_CFG.h"


void KEYPAD_Init(void){
	
	u8 r;
	
	for(r=0;r<rows;r++)
	{
		DIO_WritePin(FIRST_OUTPUT+r,HIGH);
		
	}
}

u8 KEYPAD_GETKEYS(void){
	
	u8 r,c,key=NO_KEY;
	
	for(r=0;r<rows;r++)
	{
	DIO_WritePin(FIRST_OUTPUT+r,LOW);
	
	for(c=0;c<cols;c++)
	{
		if(DIO_ReadPin(FIRST_INPUT+c)==LOW)
		{
			key=KeysArr[r][c];
			_delay_ms(10);
			while(DIO_ReadPin(FIRST_INPUT+c)==LOW);
			_delay_ms(10);
		}
	}
		DIO_WritePin(FIRST_OUTPUT+r,HIGH);
}
return key;
}


u16 KEYPAD_CONVERTER(u16 num,u8 from,u8 to){
	u16 x ,binarynum=0;
	if(to==0)//decimal
	{
		switch(from){
			
			case 0:  //decimal
			return num;
			break;
			
			case 1://binary
			for (x = 0; num > 0; x++) {
				binarynum += num % 2;
				binarynum *=10;
				num = num / 2;
				return binarynum;
				break;
			}
			
			
		}
	}
	
	
}
