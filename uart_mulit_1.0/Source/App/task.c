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

/*---------------------------------------------------------------------------------------*/

/*---------------3.����ʱ������(��������ʱ�밴���¸�ʽ��Ӷ�Ӧ������ʱ������)--------*/
task_timer_parameter task_timer_para[TASK_TIMER_CNT] =
 {
   /*{timeout_cb,				timeout(ms),		repeat(ms)}*/
	 {led0_task_timer_callback,	1000,			    1000},
	 {led1_task_timer_callback,	500,			    500},
	 {uart1_task_timer_callback,5000,					5000},
	 
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

//int ss()
//	{
//		printf("sss\n\r");
//		return 0;
//	}

void uart1_task_timer_callback(void)
{
//	ss();
	printf("sss\n\r");
//	printf("system running time is :%d s \n",HAL_GetTick()/ (1000U / uwTickFreq));
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

int task_run(void)
{
	timer_loop();
	return 0;
}
/*---------------------------------------------------------------------------------------*/
