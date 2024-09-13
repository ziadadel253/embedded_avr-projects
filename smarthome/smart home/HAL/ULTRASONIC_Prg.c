#define  F_CPU  8000000

#include "MemMap.h"
#include "util/delay.h"
#include "StdTypes.h"#include "DIO_Int.h"
#include "DIO_private.h"
#include "LCD_Int.h"
#include "LCD_Cfg.h"
#include "KEYPAD_Int.h"#include "ADC_Int.h"#include "EX_Interrupt_Interface.h"
#include "Timers.h"#include "RGB.h"#include "Timers_Services.h"#include "ULTRASONIC_Int.h"
static volatile  u16 c=0,res=0,t1,t2,flag=0;void func22(void){		if(flag==0){		t1=ICR1;		flag=1;		Timer1_InputCaptureEdge(FALLING);	}	else if(flag==1)	{		t2=ICR1;		Timer1_ICU_InterruptDisable();		flag=2;			}	}



u16 distanceArr[4];
u16 distanceArrbuffer[4];
u8 k=0,flag1=0,i;

void ULTRASONIC_Init(void)
{
    	
	Timer1_ICU_SetCallBack(func22);

}


void ULTRASONIC_Runnable(void)
{
	    Timer1_InputCaptureEdge(RISING);
	    Timer1_ICU_InterruptEnable();
          

	/* start u1*/
	/* read u1*/
	/* start u2*/
		 if(k==0)
	{//TCNT1=0;
			DIO_WritePin(PINC0,HIGH);
			_delay_us(15);
			DIO_WritePin(PINC0,LOW);

	if (flag1==0)		
		{
			distanceArr[k]=(t2-t1)/58;
			flag1=1;
		}
		else
		{
			distanceArrbuffer[k]=(t2-t1)/58;
		}
		k++;
		flag=0;
		
	}
	
       	 else if( k==1)
			 {
		//		 TCNT1=0;


				 DIO_WritePin(PINC1,HIGH);
				 _delay_us(15);
				 DIO_WritePin(PINC1,LOW);

	if (flag1==0)
	{
		distanceArr[k]=(t2-t1)/58;
		flag1=1;
	}
	else
	{
		distanceArrbuffer[k]=(t2-t1)/58;
	}
	
				 k++;
				 flag=0;
				 
			 }
             else if( k==2)
             {
			//	 TCNT1=0;


	             DIO_WritePin(PINC2,HIGH);
	             _delay_us(15);
	             DIO_WritePin(PINC2,LOW);


	if (flag1==0)
	{
		distanceArr[k]=(t2-t1)/58;
		flag1=1;
	}
	else
	{
		distanceArrbuffer[k]=(t2-t1)/58;
	}
	
	             k++;
	             flag=0;
	             
             }
         else if(k==3)
          {

			  //TCNT1=0;
	    DIO_WritePin(PINC3,HIGH);
	   _delay_us(15);
	  DIO_WritePin(PINC3,LOW);


	  if (flag1==0)
	  {
		  distanceArr[k]=(t2-t1)/58;
		  flag1=1;
	  }
	  else
	  {
		  distanceArrbuffer[k]=(t2-t1)/58;
		  for(i=0;i<4;i++)
		  {
			  distanceArr[i] =  distanceArrbuffer[i];
		  }
	  }
          	  
	k=0;
	flag=0;


	
}

	
}

u16 ULTRASONIC_GetDistance(u8 u)
{
	return distanceArr[u];
	
}