/*
PF8---BEEP
�ߵ�ƽ��ͨ
*/

#ifndef _BEEP_H
#define _BEEP_H

#include "sys.h"                  // Device header

#define BEEP PFout(8)	//λ������

void BEEP_Init(void);

#endif 
