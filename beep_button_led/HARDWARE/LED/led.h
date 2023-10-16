/*
LED0---PF9
LED1---PF10
共阳LED,低电平亮，高电平灭，上拉
*/

#ifndef _LED_H
#define _LED_H

#include "sys.h"                  // Device header
#define LED0	PFout(9)	//位带操作
#define LED1	PFout(10)

void LED_Init(void);


#endif 
