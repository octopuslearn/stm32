/**
  ******************************************************************************
  * @file    main.c 
  * @author  hezhijie157(cpe.fjnu.edu.cn)
  * @brief   Main program body
  ******************************************************************************
  * Change Logs:
  * Date           Author       Notes
  * 
  ******************************************************************************
  */
/* Macro ---------------------------------------------------------------------*/
#define MAIN_CONFIG

/* Includes ------------------------------------------------------------------*/
#include "config.h"

int main(void)
{
    sys_init();
	while (1)
	{
    led_togopin();
		HAL_Delay(1000);
	}
}


/**********************************END OF FILE**********************************/
