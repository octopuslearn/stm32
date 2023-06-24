/*********************以下为原版git修改而来，只不过去掉了**************************/
/***原版git void button_init(struct Button* handle, uint8_t(*pin_level)(uint8_t), uint8_t active_level, uint8_t button_id)
修改版      void button_init(struct Button* handle, uint8_t(*pin_level)(), uint8_t active_level);
去掉了一个参数********************************************************************/


#ifndef __task_H__
#define __task_H__

#include "stm32f1xx.h"
#ifdef __cplusplus
 extern "C" {
#endif

typedef struct timer_parameter {
    void (*timeout_cb)(void); 
	uint32_t timeout;
	uint32_t repeat;
}task_timer_parameter;


int task_init(void);
int task_run(void);


#ifdef __cplusplus
}
#endif


#endif
/*****************************END OF FILE*********************************/
