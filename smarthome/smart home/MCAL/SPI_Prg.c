#include "StdTypes.h"
#include "MemMap.h"
#include "SPI_Int.h"




void SPI_Init(void)
{
	/* master or slave */
	if (MODE==MASTER)
	{
		SET_BIT(SPCR,MSTR);
	}
	else
	{
		CLR_BIT(SPCR,MSTR);
	}
	/*clock*/
	
	/* enable spi*/
	SET_BIT(SPCR,SPE);
}


u8 SPI_SendReceive(u8 data)
{
	SPDR=data;
	while(!GET_BIT(SPSR,SPIF));
	return SPDR;
}


void SPI_SendNoBlock(u8 data)
{
	SPDR=data;
}

u8 SPI_ReceivePerodic(u8*pdata)
{
	if (GET_BIT(SPSR,SPIF))
	{
		*pdata=SPDR;
		return 1;
	}
	return 0;
}



u8 SPI_SendReceiveTimeOut(u8 datain,u8*dataout,u32 time)
{
	u8 c=0;
	SPDR=datain;
	while((!GET_BIT(SPSR,SPIF))&&c<time)
	{
		_delay_us(1);
		c++;
	}
	if (GET_BIT(SPSR,SPIF))
	{
		*dataout=SPDR;
		return 1;
	}
	else
	{
		return 0;
	}
	
}
void SPI_Enterrupt_Enable(void)
{
	/***SPI Interrupt Enable***/
	SET_BIT(SPCR,SPIE);
}