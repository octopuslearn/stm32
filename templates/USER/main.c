#include "sys.h"
#include "delay.h"
#include "usart.h"

#include "led.h"

int main()
{
	delay_init(168);
	LED_Init();
	
	while(1)
	{
		GPIO_ResetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);//LED¡¡
		delay_ms(300);
		GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);//LED¡¡
		delay_ms(300);
	}
		
}
	

	
