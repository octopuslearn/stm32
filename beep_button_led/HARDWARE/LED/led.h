/*
LED0---PF9
LED1---PF10
����LED,�͵�ƽ�����ߵ�ƽ������
*/

#ifndef _LED_H
#define _LED_H

#include "sys.h"                  // Device header
#define LED0	PFout(9)	//λ������
#define LED1	PFout(10)

void LED_Init(void);


#endif 
