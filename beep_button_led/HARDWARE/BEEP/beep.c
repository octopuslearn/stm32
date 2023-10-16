/*
PF8---BEEP
高电平开，低电平关,下拉
*/
#include "beep.h"

void BEEP_Init()
{
/*此处错误，时钟初始化错误*/	
//	RCC_AHB1PeriphClockLPModeCmd(RCC_AHB1Periph_GPIOF, ENABLE);	//使能GPIOF时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;	
	
	
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOF, GPIO_Pin_8);	//关-低电平关
}



