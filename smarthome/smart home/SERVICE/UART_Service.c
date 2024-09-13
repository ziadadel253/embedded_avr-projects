
#include "StdTypes.h"
#include "UART_Int.h"
#include "LCD_Int.h"
#include "LCD_Cfg.h"
#include "UART_Service.h"


void UART_SendString(u8*str)
{
	u8 i;
	for(i=0;str[i];i++)
	{
		UART_Send(str[i]);
	}
	
}

void UART_ReceiveString(u8*str)
{
	u8 i=0;
	str[i]=UART_Receive();
	for(;str[i]!=0xd;)
	{
		i++;
		str[i]=UART_Receive();
	}
	str[i]=0;
}


void UART_SendStringCheckSum(u8*str)
{
u8 len,i;
u16 sum=0;

for(i=0;str[i];i++)
{	
    sum+=str[i];	
 
}

len=i;
UART_Send(len);

for(i=0;str[i];i++)
{
	UART_Send(str[i]);
	
}

UART_Send((u8)sum);
UART_Send((u8)(sum>>8));

}

u8 UART_ReceiveStringCheckSum(u8*str)
{
	u8 len,i,b0,b1;
	u16 sumcalc=0,sumrec=0;
	
	len=UART_Receive();
	
	for(i=0;i<len;i++)
	{
		str[i]=UART_Receive();
		sumcalc+=str[i];
	}
	b0=UART_Receive();
	b1=UART_Receive();
	sumrec=(u16)b0|((u16)b1<<8);
	
	if(sumcalc==sumrec)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}


void Uart_SendNumber(u32 num)
{
	u8*p=&num;
	
	UART_Send(p[0]);
	UART_Send(p[1]);
	UART_Send(p[2]);
	UART_Send(p[3]);
}

u32 UART_ReceiveNumber(void)
{
	u32 num;
	u8*p=&num;
	
	p[0]=UART_Receive();
	p[1]=UART_Receive();
	p[2]=UART_Receive();
	p[3]=UART_Receive();
	
	return num;
}

u8 check_indian(void)
{
	u32 num=1;
	u8 *ptr=&num;
	if(*ptr==1)
	{
		return 1 ;//little
	}
	else
	{
		return 0; //big
	}
}


u32 endian_convert(u32 num)
{
	
	u8*p=&num;
	u8 temp;
	
	temp=p[0];
	p[0]=p[3];
	p[3]=temp;
	temp=p[1];
	p[1]=p[2];
	p[2]=temp;
	
}

static int stack[STACK_SIZE];
static int sp;

static int stack2[STACK_SIZE2];
static int sp2;

u8 data[20];
static u8 Flag=0;
static u8 i=0;

u8*TX_Str[20];
static u8 c=0;
static void TX_Func(void)
{
	static u8 i=0,j=1;
	if(TX_Str[i][j]!=0)
	{
		UART_SendNoBlock(TX_Str[i][j]);
		j++;
	}
	
	else{	
		
		j=0;
		i++;
		c--;	
		Flag=0;
		if(c>0){
		UART_SendNoBlock(TX_Str[i][j]);
		j++;
		}
	}
	
}


void UART_SendStringAsynch(u8*str[20])
{
	static u8 i=0,j=0;

	c++;
	TX_Str[i]=str;
	UART_SendNoBlock(TX_Str[j][0]);
	i++;
	
	
}

static void RX_Func(void)
{
	
	data[i]=UART_ReceiveNoBlock();
	i++;
	Flag++;
}

void UART_ReceiveStringAsynch(u8*str,stack_t*s)
{
	u8 j=0;
	for(j=0;j<i;j++)
	{
		str[j]=data[j];
		push(s,data[j]);
	}
	str[j]=0;
	i=0;
	
}

stackStatus_t push(stack_t *s,u16 data)
{
	stackStatus_t status;
	if(s->sp==s->size)
	{
		status= STACK_FULL;
	}
	else
	{
		s->dataArr[s->sp++]=data;
		//sp++;
		status= STACK_OK;
	}
	return status;
}




void UARTService_Init(void)
{
	UART_TX_SetCallBack(TX_Func);
	UART_RX_SetCallBack(RX_Func);
	UART_TX_InterruptEnable();
	UART_RX_InterruptEnable();
}

stack_t* create_stack(u16 size)
{
	stack_t *s=malloc(sizeof(stack_t));

	s->dataArr=malloc(size*sizeof(int));
	s->sp=0;
	s->size=size;
	return s;
}

void pop(u16*pdata)
{
	stackStatus_t status;
	if(sp==0)
	{
		LCD_WriteNumber(5);
		status=STACK_EMPTY;
	}
	else
	{
		//sp--;
		*pdata=data[--sp];
		status=STACK_OK;
	  LCD_WriteChar(*pdata);
	}

	return status;
}