#ifndef __led_H_
#define __led_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "stm32f1xx.h"

#define led0_Pin GPIO_PIN_0			//À´×Ômain.h
#define led0_GPIO_Port GPIOA
#define led1_Pin GPIO_PIN_1
#define led1_GPIO_Port GPIOA

void led_init(void);
int led_togopin(void);

#ifdef __cplusplus
}
#endif	
	
#endif

