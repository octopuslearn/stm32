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

void USART1_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
/*ע�⣺�˴�����ʱ��ʹ�ܳ���*/
//	RCC_AHB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//ʹ��USART1ʱ��---1.
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	//ʹ��GPIOAʱ��
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);	//���Ÿ���---2.
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);	
	
	
	//GPIO��ʼ��---3.
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	//�������
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	//���ڲ�����ʼ��---4.
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;											//������
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
/*ע�⣺�˴�ֻ�����˽��գ���û�����÷���*/	
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Rx;	
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�շ�ģʽ
	USART_InitStructure.USART_Parity = USART_Parity_No;									//����żУ��λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;								//1λֹͣλ
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;							//�ֳ�8λ
	USART_Init(USART1, &USART_InitStructure);		
	

	//��ʼ��NVIC
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	//ָ��ʹ��ͨ��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//ʹ��ָ��ͨ��
	NVIC_Init(&NVIC_InitStructure);	//��ʼ��NVIC

	//ʹ�ܴ��ڣ����ô����ж�
	USART_Cmd(USART1, ENABLE);	//ʹ�ܴ���---6.
	USART_ITConfig(USART1 ,USART_IT_RXNE, ENABLE);	//���ڽ��շǿ��ж�
}	


void USART1_IRQHandler(void)
{	
	u8 data;
	if(USART_GetITStatus(USART1, USART_IT_RXNE))	//ȷ���������ڽ��շǿ��жϴ���
	{
		data = USART_ReceiveData(USART1);
		USART_SendData(USART1, data);
	}
}

