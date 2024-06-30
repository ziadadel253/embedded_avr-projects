
#define  F_CPU  8000000

#include "MemMap.h"
#include "util/delay.h"
#include "StdTypes.h"#include "DIO_Int.h"

#include "LCD_Int.h"
#include "LCD_Cfg.h"
#include "KEYPAD_Int.h"#include "ADC_Int.h"                                    typedef union {	       char *s;  struct{		 unsigned char x:4;	 unsigned char y:4;    }	 	 	 }segment;  void segment_display (char n ) {	int i,j;	const char segmentarr[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7c,0x07,0x7f,0x6f};//PORTA=segmentarr[n%10];for(j=0;j<n;j++){	if(i<10){		CLR_BIT(PORTC,7);	//SET_Bit(PORTC,6);	PORTA=segmentarr[n%10];	    _delay_ms(3);     		CLR_BIT(PORTC,6);	CLR_BIT(PORTC,7);		i++;}else{	i=0;		CLR_Bit(PORTC,6);	SET_Bit(PORTC,7);	PORTA=segmentarr[n/10];	_delay_ms(20);     _delay_ms(5); 		    //CLR_Bit(PORTC,7);   // CLR_Bit(PORTC,6);   				}}}int main(){
	DIO_Init();
	LCD_Init();
	
	u8 k,flag=0,num1=0,num2=0,ans=0,op,eflag=0,aflag=0,mflag=0;
	
	while(1){
		
		
		k= KEYPAD_GETKEYS();
		if(k!=NO_KEY)
		{
			if(eflag==1)
			{
				LCD_Clear();
				eflag=0;
				//aflag=1;
			}
			LCD_WriteChar(k);
			if(k>='0' && k<='9')
			{
				if(aflag==1)
				{
					aflag=0;
					ans=0;
					num1=0;
				}
				
				if(flag==0)
				{
					num1=num1*10+(k-'0');
					
					
				}
				
				//LCD_WriteChar(k);
				else
				{
					num2=num2*10+(k-'0');
					
				}
				
			}
			else{
				if(k=='c')
				{
					LCD_Clear();
					flag=0;
				}
				else if(k=='+')
				{
					op='+';
					flag=1;
					aflag=0;
				}
				else if(k=='-')
				{
					op='-';
					flag=1;
					aflag=0;
				}
				else if(k=='*')
				{
					op='*';
					flag=1;
					aflag=0;
				}
				
				else if(k=='/')
				{
					op='/';
					flag=1;
					aflag=0;
				}
				else if(k=='=')
				{
					if(flag==0)
					{
						LCD_SetCursor(1,0);
						LCD_WriteChar(op);
						LCD_WriteNumber(num1);
					}
					else{
						if(op=='+')
						{
							ans=num1+num2;
						}
						else if(op=='-')
						{
							if(num1<num2)
							{
								ans=num1-num2;
								ans=Max_u8+1-ans;
								mflag=1;
							}
							else{
								ans=num1-num2;
							}
						}
						else if(op=='*')
						{
							ans=num1*num2;
						}
						else if(op=='/')
						{
							if(num2==0)
							{
								LCD_Clear();
								LCD_WriteString("ERROR");
							}
							else{
								ans=num1/num2;
							}
						}
						LCD_SetCursor(1,0);
						if(mflag==1)
						{
							LCD_WriteChar('-');
							LCD_WriteNumber(ans);
							mflag=0;
						}
						else{
							LCD_WriteNumber(ans);
						}
						eflag=1;
						flag=0;
						aflag=1;
						num2=0;
						num1=ans;
						
						
					}
					
					
					
				}
			}
		}
	}
	return 0;
}



/*ISR(INT1_vect){		DIO_TogglePin(PINC0);	//SET_BIT(PORTB,7);	//SET_BIT(PORTC,2);} */
	
                                                       	
