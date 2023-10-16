/*
KEY_UP---WK_UP---PA0
KEY2---PE2
KEY1---PE3
KEY0---PE4
按下低电平，上拉
*/

#ifndef _BUTTON_H
#define _BUTTON_H

#include "sys.h"                  // Device header
 #include "delay.h"
 
#define KEY2 PEin(2)
#define KEY1 PEin(3)
#define KEY0 PEin(4)

void BUTTON_Init(void);
u8 BUTTON_Value(u8 mode);

#endif 
