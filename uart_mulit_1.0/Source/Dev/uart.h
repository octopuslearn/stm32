#ifndef __bsp_uart_H__
#define __bsp_uart_H__

#include "stm32f1xx.h"

#ifdef __cplusplus
 extern "C" {
#endif

	  
extern UART_HandleTypeDef huart1;	 
void MX_USART1_UART_Init(void);


#ifdef __cplusplus
}
#endif


#endif

/*****************************END OF FILE*********************************/
