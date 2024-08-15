
#include "StdTypes.h"
#include "ADC_Int.h"
#include "Sensors_Int.h"
#include "Sensors_Cfg.h"


u16 SENSOR_ReadTemp(void)
{
	u16 volt =ADC_ReadVolt(LM35_CH);
	u16 temp;
	temp=volt;
	return temp;
	
}

u16 SENSOR_ReadPressure(void)
{
	u16 volt =ADC_ReadVolt(CH_7);
	
	u16 pressure;
	
	pressure=volt;
	
	return pressure;
		
}