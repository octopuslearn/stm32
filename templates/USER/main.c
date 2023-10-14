#include "sys.h"
#include "delay.h"
#include "usart.h"

#include "led.h"
//如此方法有报错
//#define LED0(x) do{ x ? GPIO_ResetBits（GPIOF,GPIO_Pin_9 | GPIO_Pin_10) : GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);}while(0)
//#define LED1(x) do{ x ? GPIO_ResetBits（GPIOF,GPIO_Pin_9 | GPIO_Pin_10) : GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);}while(0)


int main()
{
	delay_init(168);
	LED_Init();
	
	while(1)
	{
		GPIO_ResetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);//LED亮,拉低
		delay_ms(300);
		GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);  //LED亮，拉高
		delay_ms(300);
//		LED0(1);
//		LED1(1);
//		delay_ms(300);
//		LED0(0);
//		LED1(0);
//		delay_ms(300);
	}
		
}
	

	
