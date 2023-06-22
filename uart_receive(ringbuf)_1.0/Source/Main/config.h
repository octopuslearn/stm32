	/***
	原因是函数传递参数尤其是第二个参数缺少&，
	参数传递错误，
	缺函数头文件在.c或者.h中的声明
	****/
	
	/*****原因是问题是缺这行代码，使得卡在printf跑不动
  HAL_UART_Init(&huart1);
	******/
	


#ifndef  __CONFIG_H__
#define  __CONFIG_H__

//无符号类型的定义

	
//----------------------------------------


//全局宏定义

//----------------------------------------


//全局类型定义
typedef enum{FALSE = 0, TRUE = !FALSE}BOOL;


typedef enum																				//定义消息枚举类型
{
	MSG_NULL = 0,
	/*****************************************/
	//添加用户消息常量，例如：MSG_XXX,
	
	MSG_KEY1_PRESS,
	MSG_USART1_REC_FINISH,																//串口1接收到一帧数据消息
	/******************************************/
	MSG_NUM
	
}MSG_TYPE;


typedef struct																																	//定义系统消息数据类型（消息类型+消息参数）
{
	MSG_TYPE msg_type;																														//系统消息类型，比如MSG_USART1_FINISH
  /***以下为做测试用，串口最大只能有256字节，若要加更改数据类型即可****/
	unsigned char msg_parameter;																									//系统消息参数，比如：当系统消息类型为MSG_USART1_FINISH时，msg_parameter代表帧长度
	/***以上为做测试用，串口最大只能有256字节，若要加更改数据类型即可****/
}system_message;



//-------------------------------------


#ifdef MAIN_CONFIG  //头文件被多个C调用时，避免变量冲突问题
	#define EXT
#else 
	#define EXT extern
#endif
	
	
//-------------------------------------
	
//常用头文件包含
#include "stm32f1xx.h"  //芯片基础头文件
#include "stdio.h"
#include "string.h"
#include "math.h"
#include <stdarg.h> 
#include <stdbool.h>
#include <stdlib.h>

	
//-------------------------------------
	
//外设驱动头文件包含
#include "system.h"  //系统相关头文件
#include "bsp_led.h"	
#include "uart.h"	
	
//----------------------------------------	

//软件包头文件包含
#include "multi_timer.h"
#include "ringbuffer.h"

//----------------------------------------
//应用相关头文件包含
#include "task.h"


//----------------------------------------
//全局变量定义,请使用EXT修饰
EXT unsigned char g_Var;	
EXT struct rt_ringbuffer msg_ring_buf;			//存储消息的环形队列，在system.c中初始化
//----------------------------------------	
#endif


/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
