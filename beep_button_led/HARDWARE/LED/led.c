/*
LED0---PF9
LED1---PF10
����LED,�ߵ�ƽ��
*/

#include "led.h"


void LED_Init()
{
	RCC_AHB1PeriphClockLPModeCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	//����LED,�ߵ�ƽ��,����---��
	
	
	GPIO_Init(GPIOF, &GPIO_InitStructure);
}
