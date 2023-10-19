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

int main()
{
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	USART1_Init();
	while(1);
}
