/*
PF8---BEEP
�ߵ�ƽ�����͵�ƽ��,����
*/
#include "beep.h"

void BEEP_Init()
{
/*�˴�����ʱ�ӳ�ʼ������*/	
//	RCC_AHB1PeriphClockLPModeCmd(RCC_AHB1Periph_GPIOF, ENABLE);	//ʹ��GPIOFʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;	
	
	
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOF, GPIO_Pin_8);	//��-�͵�ƽ��
}



