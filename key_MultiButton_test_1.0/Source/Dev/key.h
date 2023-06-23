/*********************以下为原版git修改而来，只不过去掉了**************************/
/***原版git void button_init(struct Button* handle, uint8_t(*pin_level)(uint8_t), uint8_t active_level, uint8_t button_id)
修改版      void button_init(struct Button* handle, uint8_t(*pin_level)(), uint8_t active_level);
去掉了一个参数********************************************************************/




#ifndef __bsp_key_H__
#define __bsp_key_H__

#include "stm32f1xx.h"


#ifdef __cplusplus
 extern "C" {
#endif

#define __HAL_RCC_key0_CLK_ENABLE()   __HAL_RCC_GPIOA_CLK_ENABLE()	 
#define key0_Pin 											GPIO_PIN_2
#define key0_GPIO_Port 								GPIOA
#define KEY0_DOWN  									  0
#define key0_EXTI_IRQn 								EXTI2_IRQn

#define __HAL_RCC_key1_CLK_ENABLE()   __HAL_RCC_GPIOA_CLK_ENABLE()	 
#define key1_Pin 											GPIO_PIN_3
#define key1_GPIO_Port 								GPIOA
#define KEY1_DOWN 0
	 
#define __HAL_RCC_key2_CLK_ENABLE()   __HAL_RCC_GPIOA_CLK_ENABLE()	 
#define key2_Pin 											GPIO_PIN_4
#define key2_GPIO_Port								GPIOA
#define KEY2_DOWN 										0	 
	 


#define HAL_key0_ReadPin			HAL_GPIO_ReadPin(key0_GPIO_Port, key0_Pin)

	 
void MX_GPIO_key_Init(void);
	 
#ifdef __cplusplus
}
#endif


#endif

