	/***������������������������������������������������������������
	ԭ�������ȼ�����HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);		 //��ʱ�Ͳ�������
	               HAL_NVIC_SetPriority(EXTI2_IRQn, 1, 0);//�ʹ���һ��������ʹ��
	��������������������������������������������������������������*/



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
  ע��˴���������ʽѡ����ȷ��GPIO_InitStruct.Mode = GPIO_MODE_IT_������;
  ***/
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
			if(key0 == KEY_UP)
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
//    if(HAL_GPIO_ReadPin(key0_GPIO_Port,key0_Pin) == KEY_UP)
//    {
//		printf("KEY0(PA2) Press down\n");
//  
//    }
//    __HAL_GPIO_EXTI_CLEAR_IT(key0_Pin);
//  }	

}

