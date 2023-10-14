#include "led.h"

void LED_Init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//是能GPIO时钟
	
	
	
	GPIO_InitTypeDef GPIO_InitStructure;	//初始化结构体
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOF, &GPIO_InitStructure);	//初始化GPIO
	
	
    GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);//LED灭
}

