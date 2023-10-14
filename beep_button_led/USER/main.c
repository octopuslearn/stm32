#include "sys.h"
#include "delay.h"
#include "usart.h"


#include "led.h"
#include "button.h"
#include "beep.h"

int main()
{
	delay_init(168);
	
	LED_Init();
	BUTTON_Init();
	BEEP_Init();
	
	while(1)
	{
		int BUTTON_Value = BUTTON_Value();
		switch(BUTTON_Value)
		{
			case 0:LED0;break;
			case 1:LED1;break;
			case 2:BEEP();break;
			default:break;
		}			
	}
}

