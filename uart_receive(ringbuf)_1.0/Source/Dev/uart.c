	/***
	ԭ���Ǻ������ݲ��������ǵڶ�������ȱ��&��
	�������ݴ���
	ȱ����ͷ�ļ���.c����.h�е�����
	****/
	
	
	
	/*****ԭ����������ȱ���д��룬ʹ�ÿ���printf�ܲ���
  HAL_UART_Init(&huart1);
	******/
	


#include "config.h"
#include "uart.h"

struct rt_ringbuffer usart1_recv_ring_buf;	//����1���ջ��λ������
uint8_t  USART1_Rxbuf[USART1_Buf_size];			//���ڽ��ջ�����
uint8_t USART1_Rxcnt = 0;									//��ŵ�ǰ���ڽ������ݴ�ŵ�λ��


UART_HandleTypeDef huart1;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{


  huart1.Instance = USART1;
  huart1.Init.BaudRate = USART1_BAUD;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&huart1);
	/*****������ȱ���д��룬ʹ�ÿ���printf�ܲ���
  ԭ����HAL_UART_Init(&huart1);
	******/	
//  if (HAL_UART_Init(&huart1) != HAL_OK)
//  {
//    Error_Handler();
//  }
		
	
	/***usart1_recv_ring_buf-����1���ζ��У� ��Ϣ���׵�ַ�� ��Ϣ������***/	
	rt_ringbuffer_init(&usart1_recv_ring_buf, USART1_Rxbuf, USART1_Buf_size);			//����1���ջ��λ�����г�ʼ�����ͻ��ζ��г�ʼ��һ���ķ���
	
	/***
	ԭ�������һ���������ݴ���rt_ringbuffer_init(&usart1_recv_ring_buf, USART1_Rxbuf, USART1_Rxcnt);			//����1���ջ��λ�����г�ʼ�����ͻ��ζ��г�ʼ��һ���ķ���
	***/
	
	
/************����ΪUSART1�ж�����**************/
  /*������ʹ�ܴ��ڽ��շǿ����ж�*/
	__HAL_UART_ENABLE_IT(&huart1, USART_IT_RXNE);			//cubeMX�����Զ�����
	
	/*������ʹ�ܴ��ڽ��տ����ж�*/
	__HAL_UART_ENABLE_IT(&huart1, USART_IT_IDLE);;			//cubeMX�����Զ�����
/************����ΪUSART1�ж�����**************/	

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {

    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		
/************����ΪUSART1�ж�����**************/		
		//������
		HAL_NVIC_SetPriority(USART1_IRQn, 1, 0);					//�����ж����ȼ�
    HAL_NVIC_EnableIRQ(USART1_IRQn);        					//����1�ж�ʹ��
/************����ΪUSART1�ж�����**************/			
		

  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {

    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);
		
		/***���½̳���û��?????***/
		HAL_NVIC_DisableIRQ(USART1_IRQn);
		/***���Ͻ̳���û��?????***/
  }
}



///*printf֧��,Ҫѡ��Target/use MicroLIB*/
//int fputc(int ch, FILE *f)
//{
//  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
//  return ch;
//}


//int fgetc(FILE * f)
//{
//  uint8_t ch = 0;
//  HAL_UART_Receive(&huart1,&ch, 1, 0xffff);
//  return ch;
//}


/******************************************************************************************/
/* �������´���, ֧��printf����, ������Ҫѡ��use MicroLIB */
#include "stdio.h"
#if 1
#if (__ARMCC_VERSION >= 6010050)                    /* ʹ��AC6������ʱ */
__asm(".global __use_no_semihosting\n\t");          /* ������ʹ�ð�����ģʽ */
__asm(".global __ARM_use_no_argv \n\t");            /* AC6����Ҫ����main����Ϊ�޲�����ʽ�����򲿷����̿��ܳ��ְ�����ģʽ */

#else
/* ʹ��AC5������ʱ, Ҫ�����ﶨ��__FILE �� ��ʹ�ð�����ģʽ */
#pragma import(__use_no_semihosting)

struct __FILE
{
    int handle;
    /* Whatever you require here. If the only file you are using is */
    /* standard output using printf() for debugging, no file handling */
    /* is required. */
};

#endif

/* ��ʹ�ð�����ģʽ��������Ҫ�ض���_ttywrch\_sys_exit\_sys_command_string����,��ͬʱ����AC6��AC5ģʽ */
int _ttywrch(int ch)
{
    ch = ch;
    return ch;
}

/* ����_sys_exit()�Ա���ʹ�ð�����ģʽ */
void _sys_exit(int x)
{
    x = x;
}

char *_sys_command_string(char *cmd, int len)
{
    return NULL;
}

/* FILE �� stdio.h���涨��. */
FILE __stdout;

/* �ض���fputc����, printf�������ջ�ͨ������fputc����ַ��������� */
int fputc(int ch, FILE *f)
{
    while ((USART1->SR & 0X40) == 0);               /* �ȴ���һ���ַ�������� */

    USART1->DR = (uint8_t)ch;                       /* ��Ҫ���͵��ַ� ch д�뵽DR�Ĵ��� */
    return ch;
}
#endif
/***********************************************END*******************************************/



/************����ΪUSART1�ж�����**************/
/*****
����������û��ʹ���жϻص����������ǲ��ձ�׼�⣬�Լ�д�ȴ��жϱ�־������жϱ�־
******/

void USART1_IRQHandler(void)
{

	uint8_t receive_char;
	system_message sys_msg;			//ϵͳ��Ϣ����
	
	if((__HAL_USART_GET_FLAG(&huart1, UART_FLAG_RXNE) != RESET))			//���յ��ǿ��жϣ�USART_FLAG_RXNE-������
	{
		/***��סΨ�����ﲻֻͬ������дUART
		ԭ����HAL_UASRT_Receive(&huart1, &receive_char, 1, 1000);
		***/
		
		HAL_UART_Receive(&huart1, &receive_char, 1, 1000);					//��������
		/***
		ԭ���ǵڶ������˸�&  rt_ringbuffer_put(&usart1_recv_ring_buf, receive_char, 1);		//�����յ�����Ϣ�浽����1��Ϣ���ζ���
		***/
		rt_ringbuffer_put(&usart1_recv_ring_buf, &receive_char, 1);		//�����յ�����Ϣ�浽����1��Ϣ���ζ���
		USART1_Rxcnt++;
		
		__HAL_USART_CLEAR_FLAG(&huart1,UART_FLAG_RXNE);							//����жϱ�־
		
	}
	
	if((__HAL_USART_GET_FLAG(&huart1, UART_FLAG_IDLE) != RESET))	 //���յ������жϣ�USART_FLAG_IDLE-����
	{	
	sys_msg.msg_type = MSG_USART1_REC_FINISH;													 //һ֡���ݽ�����ɣ���ֵ��Ϣ���ͼ�MSG_USART1_FINISH-1���յ�һ֡������Ϣ
	sys_msg.msg_parameter = USART1_Rxcnt;													 //һ֡���ݽ�����ɣ���ֵ��Ϣ���ȼ�ϵͳ��Ϣ���������磺��ϵͳ��Ϣ����ΪMSG_USART1_FINISHʱ��msg_parameter����֡����
	USART1_Rxcnt = 0;																							 //���ռ�������	

	rt_ringbuffer_put(&msg_ring_buf, (uint8_t *)&sys_msg.msg_type, 2);//��һ֡���ݷ������ʱ������Ϣ����msg_ring_buf����ϵͳ��Ϣ    ��Ϣ���ͣ�USART_FLAG_IDLE   ��Ϣ������֡����     ���� ����1�������һ֡��Ϣ��1�ֽڣ�+����1����֡�ĳ�����Ϣ��1�ֽڣ�
		
	/***
	ԭ���ǵڶ������˸�&  rt_ringbuffer_put(&msg_ring_buf, (uint8_t *)&sys_msg.msg_type, 2);//��һ֡���ݷ������ʱ������Ϣ����msg_ring_buf����ϵͳ��Ϣ    ��Ϣ���ͣ�USART_FLAG_IDLE   ��Ϣ������֡����
	***/
		
	__HAL_USART_CLEAR_IDLEFLAG(&huart1);
	
	}
}
/************����ΪUSART1�ж�����**************/	