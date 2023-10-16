/*
PF8---BEEP
高电平导通
*/

#ifndef _BEEP_H
#define _BEEP_H

#include "sys.h"                  // Device header

#define BEEP PFout(8)	//位带操作

void BEEP_Init(void);

#endif 
