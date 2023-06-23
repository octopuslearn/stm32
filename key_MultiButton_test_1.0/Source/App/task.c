/*********************����Ϊԭ��git�޸Ķ�����ֻ����ȥ����**************************/
/***ԭ��git void button_init(struct Button* handle, uint8_t(*pin_level)(uint8_t), uint8_t active_level, uint8_t button_id)
�޸İ�      void button_init(struct Button* handle, uint8_t(*pin_level)(), uint8_t active_level);
ȥ����һ������********************************************************************/



	/***������������������������������������������������������������
	ԭ�������ȼ�����HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);		 //��ʱ�Ͳ�������
	               HAL_NVIC_SetPriority(EXTI2_IRQn, 1, 0);//�ʹ���һ��������ʹ��
	��������������������������������������������������������������*/
	
	
	/*****������ȱ���д��룬ʹ�ÿ���printf�ܲ���
  HAL_UART_Init(&huart1);
	******/
	


#include "config.h"
#include "task.h"

/*
 *Note:In order to add new task ,we must modify 4 places :
 *1.TASK_TIMER_CNT
 *2.timeout_cb declare
 *3.task_timer_para
 *4.timeout_cb realize
*/

/*--------------------------------1.����ʱ����������----------------------------------*/
#define TASK_TIMER_CNT   3   //����ʱ������,��������ʱ���޸ĸú�ֵ
struct Timer task_timer[TASK_TIMER_CNT];
/*---------------------------------------------------------------------------------------*/


/*---------------2.����ص���������(��������ʱ����Ӷ�Ӧ�Ļص���������)-----------------*/
void led0_task_timer_callback(void);//����ص���������
void led1_task_timer_callback(void);//����ص���������
void uart1_task_timer_callback(void);//uart-����ص���������
void button_scan_tack_timer_callback(void);//uart-����ص���������

/*---------------------------------------------------------------------------------------*/

/*---------------3.����ʱ������(��������ʱ�밴���¸�ʽ��Ӷ�Ӧ������ʱ������)--------*/
task_timer_parameter task_timer_para[TASK_TIMER_CNT] =
 {
   /*{timeout_cb,				timeout(ms),		repeat(ms)}*/
//	 {led0_task_timer_callback,	1000,			    1000},
	 {led1_task_timer_callback,	500,			    500},
	 {uart1_task_timer_callback,1000,					1000},
	 {button_scan_tack_timer_callback,0,					  5},			//����һ��5ms��ʱ��ѭ�����ú�̨������
	 
   /*{timeout_cb,				timeout(ms),		repeat(ms)}*/ 
 };
/*---------------------------------------------------------------------------------------*/       


/*--------4.����ʱ���ص�����ʵ��(��������ʱ����Ӷ�Ӧ�Ķ�ʱ���ص�����ʵ��)------------*/

void led0_task_timer_callback(void)//����ص�����ʵ��
{
	led0_toggle();
	
}

void led1_task_timer_callback(void)//����ص�����ʵ��
{
	led1_toggle();
	
}

void uart1_task_timer_callback(void)
{

	printf("sss\n\r");

}

void button_scan_tack_timer_callback()
{
	button_ticks();			//����һ��5ms��ʱ��ѭ�����ú�̨������
}

/*---------------------------------------------------------------------------------------*/


/*--�����ʼ��task_init(sys_init()�е���)�����к���task_run(main.c�е���)�������������޸�--*/

int task_init(void)
{   
	uint8_t task_index;
	for(task_index = 0;task_index < TASK_TIMER_CNT;task_index++)
	{
	    timer_init(&task_timer[task_index],
		           task_timer_para[task_index].timeout_cb, 
		           task_timer_para[task_index].timeout,
		           task_timer_para[task_index].repeat); 
		
	    timer_start(&task_timer[task_index]);
	}
	return 0;
}


static uint8_t message_buff[256];
void msg_process(void)			//ϵͳ��Ϣ����
{
	system_message sys_msg;
	
	if(rt_ringbuffer_data_len(&msg_ring_buf) != 0)											//��Ϣ���в�Ϊ�գ�������Ϣ��Ҫ����
	{
		rt_ringbuffer_get(&msg_ring_buf, (uint8_t *) &sys_msg.msg_type, 2); //��ȡ��Ϣ
				
		switch(sys_msg.msg_type)																					//������Ϣ����ִ����Ӧ�Ĳ���
		{
			case MSG_USART1_REC_FINISH:																			//��Ϣ���ͣ�MSG_USART1_REC_FINISH
				rt_ringbuffer_get(&usart1_recv_ring_buf, message_buff, sys_msg.msg_parameter);
				message_buff[sys_msg.msg_parameter] = '\0';
				printf("receive: %s\n",message_buff);
			break;
			
			default:break;
		}
	}
}


int task_run(void)
{
	timer_loop();
	msg_process();
	return 0;
}
/*---------------------------------------------------------------------------------------*/

