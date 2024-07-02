#include "StdTypes.h"
#include "MemMap.h"
#include "ADC_Int.h"

#define  F_CPU  8000000
#include "util/delay.h"


void ADC_Init(ADC_VREF_t vref,ADC_Prescaler_t scaler)
{
	/* vref*/
	switch(vref)
	{
		case VREF_AREF:
		CLR_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		case VREF_VCC:
		SET_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		case VREF_256:
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
		break;
	}
	
	/*prescaler*/
	ADCSRA=ADCSRA&0xf8;//0b11111000
	ADCSRA=ADCSRA|scaler;
	/*pins*/
	/*enable ADC*/
	SET_BIT(ADCSRA,ADEN);
	
}

u16 ADC_Read(ADC_Channel_t ch)
{
	u16 adc;
	/*select channel*/
	
	ADMUX =ADMUX&0xE0;
	ADMUX|=ch;
	
	
	/*start conversion*/
	SET_BIT(ADCSRA,ADSC);
	/*wait until conversion end*/
	while(GET_BIT(ADCSRA,ADSC));
	/* get reading*/
	//adc=ADCH<<8|ADCL;
	return ADC;
}

u16 ADC_ReadVolt(ADC_Channel_t ch)
{
	u16 volt;
	
	u16 adc=ADC_Read(ch);
	
	volt=((u32)500*adc)/1023;
	
	return volt;
	
}
