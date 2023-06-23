#ifndef __bsp_led_H__
#define __bsp_led_H__

#include "stm32f1xx.h"

#ifdef __cplusplus
 extern "C" {
#endif

#define led0_Pin GPIO_PIN_0
#define led0_GPIO_Port GPIOA
#define led1_Pin GPIO_PIN_1
#define led1_GPIO_Port GPIOA


void MX_GPIO_Init(void);
int led_toggle(void);
int led0_toggle(void);
int led1_toggle(void);



#ifdef __cplusplus
}
#endif


#endif

/*****************************END OF FILE*********************************/
