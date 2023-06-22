	/*****问题是缺这行代码，使得卡在printf跑不动
  HAL_UART_Init(&huart1);
	******/
	


#include "config.h"
#include "uart.h"


uint8_t USART1_Rxbuf[USART1_Buf_size];			//串口接收缓冲区
uint16_t USART1_Rxcnt = 0;									//存放当前串口接收数据存放的位置


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
	/*****问题是缺这行代码，使得卡在printf跑不动
  HAL_UART_Init(&huart1);
	******/	
//  if (HAL_UART_Init(&huart1) != HAL_OK)
//  {
//    Error_Handler();
//  }
	
	
/************以下为USART1中断新添**************/
  /*使能串口接收非空闲中断*/
	__HAL_UART_ENABLE_IT(&huart1, USART_IT_RXNE);			//cubeMX不会自动生成
	
	/*使能串口接收空闲中断*/
	__HAL_UART_ENABLE_IT(&huart1, USART_IT_IDLE);;			//cubeMX不会自动生成
/************以上为USART1中断新添**************/	

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
		
/************以下为USART1中断新添**************/		
		HAL_NVIC_SetPriority(USART1_IRQn, 1, 0);					//设置中断优先级
    HAL_NVIC_EnableIRQ(USART1_IRQn);        					//串口1中断使能
/************以上为USART1中断新添**************/			
		

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

		HAL_NVIC_DisableIRQ(USART1_IRQn);
		
  }
}




/************以下为USART1中断新添**************/
/*****
这里没有使用中断回调函数，而是参照标准库，自己写等待中断标志，清除中断标志
******/

void USART1_IRQHandler(void)
{

	uint8_t receive_char;
	
	if((__HAL_USART_GET_FLAG(&huart1, USART_FLAG_RXNE) != RESET))			//接收到非空中断，USART_FLAG_RXNE-不空闲
	{
		/***记住唯独这里不同只有这里写UART
		HAL_UASRT_Receive(&huart1, &receive_char, 1, 1000);
		***/
		
		/***
		视频上可以我不行，我只能打印字符串的最后一个字符
		串口调试助手发送个字符串，如何原样打印？？？？
		？？？？？？？？？？？？？？？？？？？？？？？
		？？？？？？？？？？？？？？？？？？？？？？？
		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		已经解决，可能是这个if少个{
		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!	
		***/
		
		HAL_UART_Receive(&huart1, &receive_char, 1, 1000);						//接收数据
		USART1_Rxbuf[USART1_Rxcnt++] = receive_char ;
		
		__HAL_USART_CLEAR_FLAG(&huart1,USART_FLAG_RXNE);							//清除中断标志
		
	}
	
	if((__HAL_USART_GET_FLAG(&huart1, USART_FLAG_IDLE) != RESET))	 //接收到空闲中断，USART_FLAG_IDLE-空闲
	{	
/***
	根据实验，此处不可添加此句，否则会打印两行。
	//  USART1_Rxbuf[USART1_Rxcnt] = '\0';														 //为数据添加结束标志\0
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	已经解决，可能是这个if少个{
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!	
***/
	USART1_Rxbuf[USART1_Rxcnt] = '\0';	
	printf("USART1 receive: %s\n",USART1_Rxbuf);										 //将接收到的数据打印到屏幕上
	USART1_Rxcnt = 0;																							 //接收计数清零
	__HAL_USART_CLEAR_IDLEFLAG(&huart1);
	
	}
}
/************以上为USART1中断新添**************/	




/*printf支持,要选择Target/use MicroLIB*/
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
/* 加入以下代码, 支持printf函数, 而不需要选择use MicroLIB */
#include "stdio.h"
#if 1
#if (__ARMCC_VERSION >= 6010050)                    /* 使用AC6编译器时 */
__asm(".global __use_no_semihosting\n\t");          /* 声明不使用半主机模式 */
__asm(".global __ARM_use_no_argv \n\t");            /* AC6下需要声明main函数为无参数格式，否则部分例程可能出现半主机模式 */

#else
/* 使用AC5编译器时, 要在这里定义__FILE 和 不使用半主机模式 */
#pragma import(__use_no_semihosting)

struct __FILE
{
    int handle;
    /* Whatever you require here. If the only file you are using is */
    /* standard output using printf() for debugging, no file handling */
    /* is required. */
};

#endif

/* 不使用半主机模式，至少需要重定义_ttywrch\_sys_exit\_sys_command_string函数,以同时兼容AC6和AC5模式 */
int _ttywrch(int ch)
{
    ch = ch;
    return ch;
}

/* 定义_sys_exit()以避免使用半主机模式 */
void _sys_exit(int x)
{
    x = x;
}

char *_sys_command_string(char *cmd, int len)
{
    return NULL;
}

/* FILE 在 stdio.h里面定义. */
FILE __stdout;

/* 重定义fputc函数, printf函数最终会通过调用fputc输出字符串到串口 */
int fputc(int ch, FILE *f)
{
    while ((USART1->SR & 0X40) == 0);               /* 等待上一个字符发送完成 */

    USART1->DR = (uint8_t)ch;                       /* 将要发送的字符 ch 写入到DR寄存器 */
    return ch;
}
#endif
/***********************************************END*******************************************/

