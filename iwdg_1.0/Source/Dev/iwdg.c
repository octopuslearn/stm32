#include "config.h"
#include "iwdg.h"


/*
 * 设置 IWDG 的超时时间
 * Tout = prv/40 * rlv (s)
 *      prv可以是[4,8,16,32,64,128,256]
 * prv:预分频器值，取值如下：
 *     @arg IWDG_PRESCALER_4: IWDG prescaler set to 4
 *     @arg IWDG_PRESCALER_8: IWDG prescaler set to 8
 *     @arg IWDG_PRESCALER_16: IWDG prescaler set to 16
 *     @arg IWDG_PRESCALER_32: IWDG prescaler set to 32
 *     @arg IWDG_PRESCALER_64: IWDG prescaler set to 64
 *     @arg IWDG_PRESCALER_128: IWDG prescaler set to 128
 *     @arg IWDG_PRESCALER_256: IWDG prescaler set to 256
 *
 *		独立看门狗使用LSI作为时钟。
 *		LSI 的频率一般在 30~60KHZ 之间，根据温度和工作场合会有一定的漂移，我
 *		们一般取 40KHZ，所以独立看门狗的定时时间并一定非常精确，只适用于对时间精度
 *		要求比较低的场合。
 *
 * rlv:预分频器值，取值范围为：0-0XFFF
 * 函数调用举例：
 * iwdg_init(IWDG_PRESCALER_64 ,625);  // IWDG 1s 超时溢出 
 *						（64/40）*625 = 1s
 */


IWDG_HandleTypeDef hiwdg;

/* IWDG init function */
/***cubeMX基础上有更改***/
void MX_IWDG_Init(uint8_t prv, uint16_t rlv)
{
	
  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = prv;
  hiwdg.Init.Reload = rlv;
	/****此为新添***/
	HAL_IWDG_Init(&hiwdg);
	
/***cubeMX自带***/	
//  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
//  {
//    Error_Handler();
//  }

}

