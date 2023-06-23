#ifndef __bsp_uart_H__
#define __bsp_uart_H__

#include "stm32f1xx.h"
#include "ringbuffer.h"

#ifdef __cplusplus
 extern "C" {
#endif

	 
/************����ΪUSART1�ж�����**************/	 
#define USART1_Buf_size 256												//���ڽ��ջ��������ݴ�С
#define USART1_BAUD 115200												//���ڲ�����	 
extern uint8_t USART1_Rxbuf[USART1_Buf_size];			//���ڽ��ջ�����
extern uint8_t USART1_Rxcnt;											//��ŵ�ǰ���ڽ������ݴ�ŵ�λ�ã����ڽ��ռ���
extern struct rt_ringbuffer usart1_recv_ring_buf;	//����1���ջ��λ������
/************����ΪUSART1�ж�����**************/	 	 
	 
	 
extern UART_HandleTypeDef huart1;	
	 
void MX_USART1_UART_Init(void);


#ifdef __cplusplus
}
#endif


#endif

/*****************************END OF FILE*********************************/
