	/***！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
	原因是优先级设置HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);		 //此时就不可以了
	               HAL_NVIC_SetPriority(EXTI2_IRQn, 1, 0);//和串口一样，可以使用
	！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！*/



#ifndef __bsp_key_H__
#define __bsp_key_H__

#include "stm32f1xx.h"


#ifdef __cplusplus
 extern "C" {
#endif
	 
#define key0_Pin GPIO_PIN_2
#define key0_GPIO_Port GPIOA
#define key0_EXTI_IRQn EXTI2_IRQn
	 
#define KEY_UP  0
#define KEY_DOWN  1


#define key0 HAL_GPIO_ReadPin(key0_GPIO_Port, key0_Pin)
	 
void MX_GPIO_key_Init(void);
	 
#ifdef __cplusplus
}
#endif


#endif
