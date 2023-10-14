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
 
#define KEY2 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)
#define KEY1 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)
#define KEY0 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)

void BUTTON_Init(void);
int BUTTON_Value();

#endif 
