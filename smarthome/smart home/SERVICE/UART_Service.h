/*
 * UART_Service.h
 *
 * Created: 7/18/2024 1:20:58 AM
 *  Author: LENOVO
 */ 


#ifndef UART_SERVICE_H_
#define UART_SERVICE_H_



#define STACK_SIZE  10
#define STACK_SIZE2  10
typedef enum{
	STACK_OK,
	STACK_EMPTY,
	STACK_FULL
}stackStatus_t;

//typedef char  stack_data;




void pop(u16*pdata);



typedef struct{
	u16*dataArr;
	u16 sp;
	u16 size;

}stack_t;

//typedef stack_t* STACK_T;


stackStatus_t push(stack_t *s,u16 data);
stack_t* create_stack(u16 size);








void UART_SendString(u8*str);

void UART_ReceiveString(u8*str);

void UART_SendStringCheckSum(u8*str);

u8 UART_ReceiveStringCheckSum(u8*str);

void Uart_SendNumber(u32 num);

u32 UART_ReceiveNumber(void);

void UARTService_Init(void);

void UART_SendStringAsynch(u8*str[20]);
void UART_ReceiveStringAsynch(u8*str,stack_t*s);

#endif /* UART_SERVICE_H_ */