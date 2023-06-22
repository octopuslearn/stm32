		/***
	原因是函数传递参数尤其是第二个参数缺少&，
	参数传递错误，
	缺函数头文件在.c或者.h中的声明
	****/
	
	
	/*****原因是问题是缺这行代码，使得卡在printf跑不动
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

/*--------------------------------1.任务定时器变量定义----------------------------------*/
#define TASK_TIMER_CNT   3   //任务定时器个数,增加任务时须修改该宏值
struct Timer task_timer[TASK_TIMER_CNT];
/*---------------------------------------------------------------------------------------*/


/*---------------2.任务回调函数声明(增加任务时须添加对应的回调函数声明)-----------------*/
void led0_task_timer_callback(void);//任务回调函数声明
void led1_task_timer_callback(void);//任务回调函数声明
void uart1_task_timer_callback(void);//uart-任务回调函数声明

/*---------------------------------------------------------------------------------------*/

/*---------------3.任务定时器参数(增加任务时须按如下格式添加对应的任务定时器参数)--------*/
task_timer_parameter task_timer_para[TASK_TIMER_CNT] =
 {
   /*{timeout_cb,				timeout(ms),		repeat(ms)}*/
	 {led0_task_timer_callback,	1000,			    1000},
	 {led1_task_timer_callback,	500,			    500},
	 {uart1_task_timer_callback,500,					500},
	 
   /*{timeout_cb,				timeout(ms),		repeat(ms)}*/ 
 };
/*---------------------------------------------------------------------------------------*/       


/*--------4.任务定时器回调函数实现(增加任务时须添加对应的定时器回调函数实现)------------*/

void led0_task_timer_callback(void)//任务回调函数实现
{
	led0_toggle();
	
}

void led1_task_timer_callback(void)//任务回调函数实现
{
	led1_toggle();
	
}

void uart1_task_timer_callback(void)
{

	printf("sss\n\r");

}

/*---------------------------------------------------------------------------------------*/


/*--任务初始化task_init(sys_init()中调用)及运行函数task_run(main.c中调用)，本部分无须修改--*/

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
void msg_process(void)			//系统消息处理
{
	system_message sys_msg;
	
	if(rt_ringbuffer_data_len(&msg_ring_buf) != 0)											//消息队列不为空，则有消息需要处理
	{
		rt_ringbuffer_get(&msg_ring_buf, (uint8_t *)&sys_msg.msg_type, 2); //读取消息
		/***
		原因是rt_ringbuffer_get(&msg_ring_buf, (uint8_t *)sys_msg.msg_type, 2); //读取消息
		少了第二个&
		***/		
		switch(sys_msg.msg_type)																					//根据消息类型执行相应的操作
		{
			case MSG_USART1_REC_FINISH:																			//消息类型：MSG_USART1_REC_FINISH
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
