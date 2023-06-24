	/*********************以下为原版git修改而来，只不过去掉了**************************/
/***原版git void button_init(struct Button* handle, uint8_t(*pin_level)(uint8_t), uint8_t active_level, uint8_t button_id)
修改版      void button_init(struct Button* handle, uint8_t(*pin_level)(), uint8_t active_level);
去掉了一个参数********************************************************************/
	
	
	
	/***！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
	原因是优先级设置HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);		 //此时就不可以了
	HAL_NVIC_SetPriority(EXTI2_IRQn, 1, 0);//和串口一样，可以使用
	！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！****/



#include "config.h"
#include "key.h"


struct Button button1;			//申请一个按键结构
void Callback_button1_Handler(void *btn);//回调函数
uint8_t HAL_key1_ReadPin(void);

struct Button button2;			//申请一个按键结构
void Callback_button2_Handler(void *btn);//回调函数
uint8_t HAL_key2_ReadPin(void);

void MX_GPIO_key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
  /* GPIO Ports Clock Enable */
	__HAL_RCC_key0_CLK_ENABLE();
	__HAL_RCC_key1_CLK_ENABLE();
	__HAL_RCC_key2_CLK_ENABLE();
	
  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = key0_Pin;
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
	
	
	GPIO_InitStruct.Pin = key1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = key2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


	
	
	button_init(&button1, HAL_key1_ReadPin, KEY1_DOWN);			//初始化按键对象
	/*注册按键事件*/
	button_attach(&button1, PRESS_UP, 					Callback_button1_Handler);					//按键弹起，每次松开都触发	
	button_attach(&button1, PRESS_DOWN,			 	  Callback_button1_Handler);			//按键按下，每次按下都触发
	button_attach(&button1, PRESS_REPEAT,			 	Callback_button1_Handler);			//重复按下触发，变量repeat计数连击次数
	button_attach(&button1, SINGLE_CLICK, 			Callback_button1_Handler);			//单击按键事件
	button_attach(&button1, DOUBLE_CLICK, 			Callback_button1_Handler);			//双击按键事件	
	button_attach(&button1, LONG_PRESS_START, 	Callback_button1_Handler);	//达到长按时间阈值时触发一次
	button_attach(&button1, LONG_PRESS_HOLD, 		Callback_button1_Handler);	//长按期间一直触发
	button_start(&button1);																//启动按键
	

	button_init(&button2, HAL_key2_ReadPin, KEY2_DOWN);			//初始化按键对象
		/*注册按键事件*/
	button_attach(&button2, PRESS_UP, 					Callback_button2_Handler);					//按键弹起，每次松开都触发
	button_attach(&button2, PRESS_DOWN, 			  Callback_button2_Handler);			//按键按下，每次按下都触发
	button_attach(&button2, PRESS_REPEAT,			 	Callback_button1_Handler);			//重复按下触发，变量repeat计数连击次数	
	button_attach(&button2, SINGLE_CLICK, 			Callback_button2_Handler);			//单击按键事件
	button_attach(&button2, DOUBLE_CLICK, 			Callback_button2_Handler);			//双击按键事件	
	button_attach(&button2, LONG_PRESS_START, 	Callback_button2_Handler);	//达到长按时间阈值时触发一次
	button_attach(&button2, LONG_PRESS_HOLD, 		Callback_button2_Handler);	//长按期间一直触发
	button_start(&button2);																//启动按键

}

uint8_t HAL_key1_ReadPin(void)
{
	return HAL_GPIO_ReadPin(key1_GPIO_Port, key1_Pin);
}

void Callback_button1_Handler(void *btn)
{
	switch(get_button_event((struct Button*)btn))
	{
		case PRESS_DOWN:
			printf("KEY1:PRESS_DOWN\n");
		break;
		
		case PRESS_UP:
			printf("KEY1:PRESS_UP\n");
		break;
		
		case PRESS_REPEAT:
			printf("KEY1:PRESS_REPEAT\n");
		break;
		
		case SINGLE_CLICK:
			printf("KEY1:SINGLE_CLICK\n");
		break;
		
		case DOUBLE_CLICK:
			printf("KEY1:DOUBLE_CLICK\n");
		break;
	 
		case LONG_PRESS_START:
			printf("KEY1:LONG_PRESS_START\n");
		break;
		
		case LONG_PRESS_HOLD:
			printf("KEY1:LONG_PRESS_HOLD\n");
		break;
		
		default:break;
	}
}




uint8_t HAL_key2_ReadPin(void)
{
	return HAL_GPIO_ReadPin(key2_GPIO_Port, key2_Pin);
}

void Callback_button2_Handler(void *btn)
{
	switch(get_button_event((struct Button*)btn))
	{
		case PRESS_DOWN:
			printf("KEY2:PRESS_DOWN\n");
		break;
		
		case PRESS_UP:
			printf("KEY2:PRESS_UP\n");
		break;
		
		case PRESS_REPEAT:
			printf("KEY2:PRESS_REPEAT\n");
		break;
		
		case SINGLE_CLICK:
			printf("KEY2:SINGLE_CLICK\n");
		break;
		
		case DOUBLE_CLICK:
			printf("KEY2:DOUBLE_CLICK\n");
		break;
	 
		case LONG_PRESS_START:
			printf("KEY2:LONG_PRESS_START\n");
		break;
		
		case LONG_PRESS_HOLD:
			printf("KEY2:LONG_PRESS_HOLD\n");
		break;
		
		default:break;
	}
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
			if(HAL_key0_ReadPin == KEY0_DOWN)
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
//    if(HAL_GPIO_ReadPin(key0_GPIO_Port,key0_Pin) == KEY0_DOWN)
//    {
//		printf("KEY0(PA2) Press down\n");
//  
//    }
//    __HAL_GPIO_EXTI_CLEAR_IT(key0_Pin);
//  }	

}


	/***！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
	原因是优先级设置HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);		 //此时就不可以了
	               HAL_NVIC_SetPriority(EXTI2_IRQn, 1, 0);//和串口一样，可以使用
	！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！*/

