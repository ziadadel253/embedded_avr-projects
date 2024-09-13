
#include "RGB.h"
#include "Timers.h"

u8 Set_Color[4][3]={{255,255,255},{0,0,0},{0,255,255},{255,255,0}};
	
void RGB_Color(color clr)
{
	switch (clr)
	{
		case black:
		OCR1A=Set_Color[0][0];
		OCR0=Set_Color[0][1];
		OCR1B=Set_Color[0][2];
		break;
		case white:
		OCR1A=Set_Color[1][0];
		OCR0=Set_Color[1][1];
		OCR1B=Set_Color[1][2];
		break;
		case red:
		OCR1A=Set_Color[2][0];
		OCR0=Set_Color[2][1];
		OCR1B=Set_Color[2][2];
		break;
		case green:
		OCR1A=Set_Color[3][0];
		OCR0=Set_Color[3][1];
		OCR1B=Set_Color[3][2];
		break;
		
	}
}