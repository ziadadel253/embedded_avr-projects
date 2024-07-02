
#include "StdTypes.h"

#include "MemMap.h"
#include "DIO_Cfg.h"#include "DIO_Int.h"#include "DIO_private.h"

static void DIO_InitPin(DIO_Pin_t pin, DIO_Status_t status)
{
	DIO_Port_t port=pin/8;
	u8 pin_num=pin%8;
	
	
	switch( status)
	{
		case OUTPUT:
		switch(port)
		{
			case PA:
			SET_BIT(DDRA,pin_num);
			CLR_BIT(PORTA,pin_num);
			break;
			case PB:
			SET_BIT(DDRB,pin_num);
			CLR_BIT(PORTB,pin_num);
			break;
			case PC:
			SET_BIT(DDRC,pin_num);
			CLR_BIT(PORTC,pin_num);
			break;
			case PD:
			SET_BIT(DDRD,pin_num);
			CLR_BIT(PORTD,pin_num);
			break;
		}
		break;
		case INFREE:
		switch(port)
		{
			case PA:
			CLR_BIT(DDRA,pin_num);
			CLR_BIT(PORTA,pin_num);
			break;
			case PB:
			CLR_BIT(DDRB,pin_num);
			CLR_BIT(PORTB,pin_num);
			break;
			case PC:
			CLR_BIT(DDRC,pin_num);
			CLR_BIT(PORTC,pin_num);
			break;
			case PD:
			CLR_BIT(DDRD,pin_num);
			CLR_BIT(PORTD,pin_num);
			break;
		}
		break;
		case INPULL:
		switch(port)
		{
			case PA:
			CLR_BIT(DDRA,pin_num);
			SET_BIT(PORTA,pin_num);
			break;
			case PB:
			CLR_BIT(DDRB,pin_num);
			SET_BIT(PORTB,pin_num);
			break;
			case PC:
			CLR_BIT(DDRC,pin_num);
			SET_BIT(PORTC,pin_num);
			break;
			case PD:
			CLR_BIT(DDRD,pin_num);
			SET_BIT(PORTD,pin_num);
			break;
		}
		break;
	}

}

void DIO_WritePin(DIO_Pin_t pin,DIO_Voltage_t volt)
{
	DIO_Port_t port=pin/8;
	u8 pin_num=pin%8;
	
	
	
	if (volt==LOW)
	{
		switch(port)
		{
			case PA:
			CLR_BIT(PORTA,pin_num);
			break;
			case PB:
			CLR_BIT(PORTB,pin_num);
			break;
			case PC:
			CLR_BIT(PORTC,pin_num);
			break;
			case PD:
			CLR_BIT(PORTD,pin_num);
			break;
		}
	}
	else
	{
		switch(port)
		{
			case PA:
			SET_BIT(PORTA,pin_num);
			break;
			case PB:
			SET_BIT(PORTB,pin_num);
			break;
			case PC:
			SET_BIT(PORTC,pin_num);
			break;
			case PD:
			SET_BIT(PORTD,pin_num);
			break;
		}
	}
}



DIO_Voltage_t DIO_ReadPin(DIO_Pin_t pin)
{
	DIO_Port_t port=pin/8;
	u8 pin_num=pin%8;

	DIO_Voltage_t volt=LOW;
	switch(port)
	{
		case PA:
		volt=	GET_BIT(PINA,pin_num);
		break;
		case PB:
		volt=	GET_BIT(PINB,pin_num);
		break;
		case PC:
		volt=	GET_BIT(PINC,pin_num);
		break;
		case PD:
		volt=	GET_BIT(PIND,pin_num);
		break;
	}
	
	return volt;
}



void DIO_Init(void)
{
	DIO_Pin_t i;
	for (i=PINA0;i<TOTAL_PINS;i++)
	{
		DIO_InitPin(i,PinsStatusArr[i]);
	}
	
}

void DIO_WritePort(DIO_Port_t port,u8 data)
{
	
	switch(port)
	{
		case PA:
		PORTA=data;
		break;
		case PB:
		PORTB=data;
		break;
		case PC:
		PORTC=data;
		break;
		case PD:
		PORTD=data;
		break;
	}
}
void DIO_TogglePin(DIO_Pin_t pin)
{
	DIO_Port_t Port;
	u8 Pin_num;
	Port = pin/8;
	Pin_num = pin%8;
	switch(Port)
	{
		case PA:
		TOG_BIT(PORTA,Pin_num);
		break;
		case PB:
		TOG_BIT(PORTB,Pin_num);
		break;
		case PC:
		TOG_BIT(PORTC,Pin_num);
		break;
		case PD:
		TOG_BIT(PORTD,Pin_num);
		break;
	}
}