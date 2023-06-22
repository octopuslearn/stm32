	/***
	原因是函数传递参数尤其是第二个参数缺少&，
	参数传递错误，
	缺函数头文件在.c或者.h中的声明
	****/
	
	
	
	/*****原因是问题是缺这行代码，使得卡在printf跑不动
  HAL_UART_Init(&huart1);
	******/
	


#include "config.h"
#include "uart.h"

struct rt_ringbuffer usart1_recv_ring_buf;	//串口1接收环形缓冲队列
uint8_t  USART1_Rxbuf[USART1_Buf_size];			//串口接收缓冲区
uint8_t USART1_Rxcnt = 0;									//存放当前串口接收数据存放的位置


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
  原因是HAL_UART_Init(&huart1);
	******/	
//  if (HAL_UART_Init(&huart1) != HAL_OK)
//  {
//    Error_Handler();
//  }
		
	
	/***usart1_recv_ring_buf-串口1环形队列， 消息池首地址， 消息池容量***/	
	rt_ringbuffer_init(&usart1_recv_ring_buf, USART1_Rxbuf, USART1_Buf_size);			//串口1接收环形缓冲队列初始化，和环形队列初始化一样的方法
	
	/***
	原因是最后一个参数传递错误rt_ringbuffer_init(&usart1_recv_ring_buf, USART1_Rxbuf, USART1_Rxcnt);			//串口1接收环形缓冲队列初始化，和环形队列初始化一样的方法
	***/
	
	
/************以下为USART1中断新添**************/
  /*新添：使能串口接收非空闲中断*/
	__HAL_UART_ENABLE_IT(&huart1, USART_IT_RXNE);			//cubeMX不会自动生成
	
	/*新添：使能串口接收空闲中断*/
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
		//新添：
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
		
		/***以下教程里没有?????***/
		HAL_NVIC_DisableIRQ(USART1_IRQn);
		/***以上教程里没有?????***/
  }
}



///*printf支持,要选择Target/use MicroLIB*/
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



/************以下为USART1中断新添**************/
/*****
新添：这里没有使用中断回调函数，而是参照标准库，自己写等待中断标志，清除中断标志
******/

void USART1_IRQHandler(void)
{

	uint8_t receive_char;
	system_message sys_msg;			//系统消息变量
	
	if((__HAL_USART_GET_FLAG(&huart1, UART_FLAG_RXNE) != RESET))			//接收到非空中断，USART_FLAG_RXNE-不空闲
	{
		/***记住唯独这里不同只有这里写UART
		原因是HAL_UASRT_Receive(&huart1, &receive_char, 1, 1000);
		***/
		
		HAL_UART_Receive(&huart1, &receive_char, 1, 1000);					//接收数据
		/***
		原因是第二个少了个&  rt_ringbuffer_put(&usart1_recv_ring_buf, receive_char, 1);		//将接收到的消息存到串口1消息环形队列
		***/
		rt_ringbuffer_put(&usart1_recv_ring_buf, &receive_char, 1);		//将接收到的消息存到串口1消息环形队列
		USART1_Rxcnt++;
		
		__HAL_USART_CLEAR_FLAG(&huart1,UART_FLAG_RXNE);							//清除中断标志
		
	}
	
	if((__HAL_USART_GET_FLAG(&huart1, UART_FLAG_IDLE) != RESET))	 //接收到空闲中断，USART_FLAG_IDLE-空闲
	{	
	sys_msg.msg_type = MSG_USART1_REC_FINISH;													 //一帧数据接收完成，赋值消息类型即MSG_USART1_FINISH-1接收到一帧数据消息
	sys_msg.msg_parameter = USART1_Rxcnt;													 //一帧数据接收完成，赋值消息长度即系统消息参数，比如：当系统消息类型为MSG_USART1_FINISH时，msg_parameter代表帧长度
	USART1_Rxcnt = 0;																							 //接收计数清零	

	rt_ringbuffer_put(&msg_ring_buf, (uint8_t *)&sys_msg.msg_type, 2);//当一帧数据发送完毕时，往消息队列msg_ring_buf发送系统消息    消息类型：USART_FLAG_IDLE   消息参数：帧长度     发送 串口1接收完成一帧消息（1字节）+串口1接收帧的长度消息（1字节）
		
	/***
	原因是第二个少了个&  rt_ringbuffer_put(&msg_ring_buf, (uint8_t *)&sys_msg.msg_type, 2);//当一帧数据发送完毕时，往消息队列msg_ring_buf发送系统消息    消息类型：USART_FLAG_IDLE   消息参数：帧长度
	***/
		
	__HAL_USART_CLEAR_IDLEFLAG(&huart1);
	
	}
}
/************以上为USART1中断新添**************/	
