/*
KEY_UP---WK_UP---PA0
按下高电平，下拉

KEY2---PE2
KEY1---PE3
KEY0---PE4
按下低电平，上拉
*/

#include "button.h"


void BUTTON_Init()
{
/*此处错误，时钟初始化错误*/	
//	RCC_AHB1PeriphClockLPModeCmd(RCC_AHB1Periph_GPIOE, ENABLE);
/*此处错误，GPIOE初始化错误*/
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	//按下低电平，上拉---弹起状态
	
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	
	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;	//按下高电平，下拉---弹起状态
	
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

//如此报错..\HARDWARE\BUTTON\button.c(38): warning: #940-D: missing return statement at end of non-void function "BUTTON_Value"
//编译器在编译时不会管if else 中的return。如果程序最后没有return语句，则编译器认为错误。
u8 BUTTON_Value()
{
/*以下，支持连续按下*/
/*	
	if(KEY2==0 || KEY1==0 || KEY0==0)	//有按键按下
	{
		delay_ms(20);	//消抖
		if(KEY2==0)	return 3;
		else if(KEY1==0) return 2;
		else if(KEY0==0) return 1;
		else{}
	}
	return 0;	//无按键按下
*/	






	
/*以下，不支持连续按下*/
	static u8 key_up = 1;	//按键松开标志，弹起-1，按下-0
	if(key_up==1 && (KEY2==0 || KEY1==0 || KEY0==0))	//有按键按下
	{
		key_up = 0;		//标记这次已经按下
		delay_ms(50);	//消抖
		if(KEY2==0)	return 3;
		else if(KEY1==0) return 2;
		else if(KEY0==0) return 1;
	}
	else if(KEY2==1 && KEY1==1 && KEY0==1)	//没有按键按下
	{
		key_up = 1;	
	}
	return 0;	//无效值
	
	
	
	
	



/*以下，不支持连续按下*/
/*以下，有误	???暂且不知道原因
	else if(KEY2==1 && KEY1==1 && KEY0==1)	//没有按键按下
	{
		key_up = 1;	
		return 0;	//无效值
	}
return 0;不能写在这，否则按下led的按键蜂鸣器也会响
*/
/*
	static u8 key_up = 1;	//按键松开标志，弹起-1，按下-0
	if(key_up==1 && (KEY2==0 || KEY1==0 || KEY0==0))	//有按键按下
	{
		key_up = 0;		//标记这次已经按下
		delay_ms(50);	//消抖
		if(KEY2==0)	return 3;
		else if(KEY1==0) return 2;
		else if(KEY0==0) return 1;
	}
	else if(KEY2==1 && KEY1==1 && KEY0==1)	//没有按键按下
	{
		key_up = 1;	
		return 0;	//无效值
	}
*/
//*/	

}

