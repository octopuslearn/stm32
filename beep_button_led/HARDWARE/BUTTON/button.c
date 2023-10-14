/*
KEY_UP---WK_UP---PA0
KEY2---PE2
KEY1---PE3
KEY0---PE4
按下低电平，上拉
*/

#include "button.h"


void BUTTON_Init()
{
	RCC_AHB1PeriphClockLPModeCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	//按下低电平，上拉---弹起状态
	
	
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}


int BUTTON_Value()
{
	if(!KEY2 || !KEY1 || !KEY0)
	{
		if(!KEY2)	return 2;
		else if(!KEY1) return 1;
		else if(!KEY0) return 0;
		else{}
	}
}

