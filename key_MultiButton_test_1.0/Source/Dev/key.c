	/*********************����Ϊԭ��git�޸Ķ�����ֻ����ȥ����**************************/
/***ԭ��git void button_init(struct Button* handle, uint8_t(*pin_level)(uint8_t), uint8_t active_level, uint8_t button_id)
�޸İ�      void button_init(struct Button* handle, uint8_t(*pin_level)(), uint8_t active_level);
ȥ����һ������********************************************************************/
	
	
	
	/***������������������������������������������������������������
	ԭ�������ȼ�����HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);		 //��ʱ�Ͳ�������
	HAL_NVIC_SetPriority(EXTI2_IRQn, 1, 0);//�ʹ���һ��������ʹ��
	��������������������������������������������������������������****/



#include "config.h"
#include "key.h"


struct Button button1;			//����һ�������ṹ
void Callback_button1_Handler(void *btn);//�ص�����
uint8_t HAL_key1_ReadPin(void);

struct Button button2;			//����һ�������ṹ
void Callback_button2_Handler(void *btn);//�ص�����
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
	
	/***������������������������������������������������������������
	ԭ�������ȼ�����HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);		 //��ʱ�Ͳ�������
	               HAL_NVIC_SetPriority(EXTI2_IRQn, 1, 0);//�ʹ���һ��������ʹ��
	��������������������������������������������������������������*/
  HAL_NVIC_SetPriority(EXTI2_IRQn, 2, 0);  //�ͽ̳̱���һ��
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);
	
	
	GPIO_InitStruct.Pin = key1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = key2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


	
	
	button_init(&button1, HAL_key1_ReadPin, KEY1_DOWN);			//��ʼ����������
	/*ע�ᰴ���¼�*/
	button_attach(&button1, PRESS_UP, 					Callback_button1_Handler);					//��������ÿ���ɿ�������	
	button_attach(&button1, PRESS_DOWN,			 	  Callback_button1_Handler);			//�������£�ÿ�ΰ��¶�����
	button_attach(&button1, PRESS_REPEAT,			 	Callback_button1_Handler);			//�ظ����´���������repeat������������
	button_attach(&button1, SINGLE_CLICK, 			Callback_button1_Handler);			//���������¼�
	button_attach(&button1, DOUBLE_CLICK, 			Callback_button1_Handler);			//˫�������¼�	
	button_attach(&button1, LONG_PRESS_START, 	Callback_button1_Handler);	//�ﵽ����ʱ����ֵʱ����һ��
	button_attach(&button1, LONG_PRESS_HOLD, 		Callback_button1_Handler);	//�����ڼ�һֱ����
	button_start(&button1);																//��������
	

	button_init(&button2, HAL_key2_ReadPin, KEY2_DOWN);			//��ʼ����������
		/*ע�ᰴ���¼�*/
	button_attach(&button2, PRESS_UP, 					Callback_button2_Handler);					//��������ÿ���ɿ�������
	button_attach(&button2, PRESS_DOWN, 			  Callback_button2_Handler);			//�������£�ÿ�ΰ��¶�����
	button_attach(&button2, PRESS_REPEAT,			 	Callback_button1_Handler);			//�ظ����´���������repeat������������	
	button_attach(&button2, SINGLE_CLICK, 			Callback_button2_Handler);			//���������¼�
	button_attach(&button2, DOUBLE_CLICK, 			Callback_button2_Handler);			//˫�������¼�	
	button_attach(&button2, LONG_PRESS_START, 	Callback_button2_Handler);	//�ﵽ����ʱ����ֵʱ����һ��
	button_attach(&button2, LONG_PRESS_HOLD, 		Callback_button2_Handler);	//�����ڼ�һֱ����
	button_start(&button2);																//��������

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
	










/*�жϷ�����*/
void EXTI2_IRQHandler(void)
{
	/*����������*/
  HAL_GPIO_EXTI_IRQHandler(key0_Pin);

}

/*�жϻص�����*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	HAL_Delay(20);			//����
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
	/* HAL ��Ĭ�������ж��ٴ���ص����˳�ʱ����һ���жϣ����ⰴ�������󴥷� */
	/* HAL ��Ĭ�������ж��ٴ���ص����˳��ص�ʱ��һ���жϣ�������*/

	
//	if(GPIO_Pin == key0_Pin)
//  {
//    HAL_Delay(20);//��ʱһС��ʱ�䣬��������(ʵ�ʲ��Ի��ǻ���bug),�����������ж���ʹ����ʱ��������ʾ��ֻ����ʾ�á���ʾ����������ֿ�������ȷ��systick���ж����ȼ��Ƿ���� 
//    if(HAL_GPIO_ReadPin(key0_GPIO_Port,key0_Pin) == KEY0_DOWN)
//    {
//		printf("KEY0(PA2) Press down\n");
//  
//    }
//    __HAL_GPIO_EXTI_CLEAR_IT(key0_Pin);
//  }	

}


	/***������������������������������������������������������������
	ԭ�������ȼ�����HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);		 //��ʱ�Ͳ�������
	               HAL_NVIC_SetPriority(EXTI2_IRQn, 1, 0);//�ʹ���һ��������ʹ��
	��������������������������������������������������������������*/

