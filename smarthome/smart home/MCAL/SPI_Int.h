/*
 * SPI_Int.h
 *
 * Created: 7/27/2024 9:29:04 PM
 *  Author: LENOVO
 */ 


#ifndef SPI_INT_H_
#define SPI_INT_H_


#define  MASTER 1
#define  SLAVE   0



#define   MODE  MASTER



void SPI_Init(void);
u8 SPI_SendReceive(u8 data);
void SPI_SendNoBlock(u8 data);
u8 SPI_ReceivePerodic(u8*pdata);
void SPI_Enterrupt_Enable(void);

#endif /* SPI_INT_H_ */