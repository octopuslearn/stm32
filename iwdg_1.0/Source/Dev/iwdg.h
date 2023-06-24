#ifndef __IWDG_H__
#define __IWDG_H__


/*
 * ���� IWDG �ĳ�ʱʱ��
 * Tout = prv/40 * rlv (s)
 *      prv������[4,8,16,32,64,128,256]
 * prv:Ԥ��Ƶ��ֵ��ȡֵ���£�
 *     @arg IWDG_PRESCALER_4: IWDG prescaler set to 4
 *     @arg IWDG_PRESCALER_8: IWDG prescaler set to 8
 *     @arg IWDG_PRESCALER_16: IWDG prescaler set to 16
 *     @arg IWDG_PRESCALER_32: IWDG prescaler set to 32
 *     @arg IWDG_PRESCALER_64: IWDG prescaler set to 64
 *     @arg IWDG_PRESCALER_128: IWDG prescaler set to 128
 *     @arg IWDG_PRESCALER_256: IWDG prescaler set to 256
 *
 *		�������Ź�ʹ��LSI��Ϊʱ�ӡ�
 *		LSI ��Ƶ��һ���� 30~60KHZ ֮�䣬�����¶Ⱥ͹������ϻ���һ����Ư�ƣ���
 *		��һ��ȡ 40KHZ�����Զ������Ź��Ķ�ʱʱ�䲢һ���ǳ���ȷ��ֻ�����ڶ�ʱ�侫��
 *		Ҫ��Ƚϵ͵ĳ��ϡ�
 *
 * rlv:Ԥ��Ƶ��ֵ��ȡֵ��ΧΪ��0-0XFFF
 * �������þ�����
 * iwdg_init(IWDG_PRESCALER_64 ,625);  // IWDG 1s ��ʱ��� 
 *						��64/40��*625 = 1s
 */


#include "stm32f1xx.h"

#ifdef __cplusplus
 extern "C" {
#endif

extern IWDG_HandleTypeDef hiwdg;
	 
/***cubeMX�������и���***/
void MX_IWDG_Init(uint8_t prv, uint16_t rlv);

#ifdef __cplusplus
}
#endif


#endif

/*****************************END OF FILE*********************************/

