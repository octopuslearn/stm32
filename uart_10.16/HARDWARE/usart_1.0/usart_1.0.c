/*错误之理由：



1.串口时钟使能出错
//	RCC_AHB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//使能USART1时钟---1.
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	//使能GPIOA时钟
	
	
2.串口模式设置出错，只设置了接收，没设置发送
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Rx;	
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//收发模式



*/




/*PA9--- USART1_TX
* PA10---USART1_RX
*/

#include "usart_1.0.h"

void USART1_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
/*注意：此处串口时钟使能出错*/
//	RCC_AHB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//使能USART1时钟---1.
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	//使能GPIOA时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);	//引脚复用---2.
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);	
	
	
	//GPIO初始化---3.
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	//复用输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	//串口参数初始化---4.
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;											//波特率
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
/*注意：此处只设置了接收，而没有设置发送*/	
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Rx;	
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//收发模式
	USART_InitStructure.USART_Parity = USART_Parity_No;									//无奇偶校验位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;								//1位停止位
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;							//字长8位
	USART_Init(USART1, &USART_InitStructure);		
	

	//初始化NVIC
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			//子优先级
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	//指定使能通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//使能指定通道
	NVIC_Init(&NVIC_InitStructure);	//初始化NVIC

	//使能串口，设置串口中断
	USART_Cmd(USART1, ENABLE);	//使能串口---6.
	USART_ITConfig(USART1 ,USART_IT_RXNE, ENABLE);	//串口接收非空中断
}	


void USART1_IRQHandler(void)
{	
	u8 data;
	if(USART_GetITStatus(USART1, USART_IT_RXNE))	//确定触发串口接收非空中断触发
	{
		data = USART_ReceiveData(USART1);
		USART_SendData(USART1, data);
	}
}

