	/***
	原因是函数传递参数尤其是第二个参数缺少&，
	参数传递错误，
	缺函数头文件在.c或者.h中的声明
	****/
	
	/*****原因是问题是缺这行代码，使得卡在printf跑不动
  HAL_UART_Init(&huart1);
	******/
	


#ifndef __bsp_uart_H__
#define __bsp_uart_H__

#include "stm32f1xx.h"
#include "ringbuffer.h"

#ifdef __cplusplus
 extern "C" {
#endif

	 
/************以下为USART1中断新添**************/	 
//新添：
#define USART1_Buf_size 256												//串口接收缓冲区数据大小
#define USART1_BAUD 115200												//串口波特率	 
extern uint8_t USART1_Rxbuf[USART1_Buf_size];			//串口接收缓冲区
extern uint8_t USART1_Rxcnt;											//存放当前串口接收数据存放的位置，串口接收计数
extern struct rt_ringbuffer usart1_recv_ring_buf;	//串口1接收环形缓冲队列
/************以上为USART1中断新添**************/	 	 
	 
	 
extern UART_HandleTypeDef huart1;	
	 
void MX_USART1_UART_Init(void);


#ifdef __cplusplus
}
#endif


#endif

/*****************************END OF FILE*********************************/
