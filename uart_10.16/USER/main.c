/*����֮���ɣ�



1.����ʱ��ʹ�ܳ���
//	RCC_AHB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//ʹ��USART1ʱ��---1.
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	//ʹ��GPIOAʱ��
	
	
2.����ģʽ���ó���ֻ�����˽��գ�û���÷���
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Rx;	
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�շ�ģʽ



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
