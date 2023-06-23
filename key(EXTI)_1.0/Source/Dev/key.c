	/***！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
	原因是优先级设置HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);		 //此时就不可以了
	               HAL_NVIC_SetPriority(EXTI2_IRQn, 1, 0);//和串口一样，可以使用
	！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！*/



#include "config.h"
#include "key.h"

void MX_GPIO_key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
  /* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	__HAL_RCC_GPIOD_CLK_ENABLE();
	
  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = key0_Pin;
  /***
  注意此处，触发方式选择正确，GPIO_InitStruct.Mode = GPIO_MODE_IT_上升沿;
  ***/
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(key0_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
	
	/***！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
	原因是优先级设置HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);		 //此时就不可以了
	               HAL_NVIC_SetPriority(EXTI2_IRQn, 1, 0);//和串口一样，可以使用
	！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！*/
  HAL_NVIC_SetPriority(EXTI2_IRQn, 2, 0);  //和教程保持一致
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

}

/*中断服务函数*/
void EXTI2_IRQHandler(void)
{
	/*公共处理函数*/
  HAL_GPIO_EXTI_IRQHandler(key0_Pin);

}

/*中断回调函数*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	HAL_Delay(20);			//消抖
	switch(GPIO_Pin)
	{
		case key0_Pin:
			if(key0 == KEY_UP)
			{
				printf("uuu\n");
			}
			break;
		default:break;
	}
	__HAL_GPIO_EXTI_CLEAR_IT(key0_Pin);
	/* HAL 库默认先清中断再处理回调，退出时再清一次中断，避免按键抖动误触发 */
	/* HAL 库默认先清中断再处理回调，退出回调时清一次中断，避免误触*/

	
//	if(GPIO_Pin == key0_Pin)
//  {
//    HAL_Delay(20);//延时一小段时间，消除抖动(实际测试还是会有bug),尽量避免在中断中使用延时函数，本示例只是演示用。演示过程如果发现卡机，请确定systick的中断优先级是否最高 
//    if(HAL_GPIO_ReadPin(key0_GPIO_Port,key0_Pin) == KEY_UP)
//    {
//		printf("KEY0(PA2) Press down\n");
//  
//    }
//    __HAL_GPIO_EXTI_CLEAR_IT(key0_Pin);
//  }	

}

