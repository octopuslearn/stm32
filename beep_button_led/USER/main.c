#include "sys.h"
#include "delay.h"
#include "usart.h"


#include "led.h"
#include "button.h"
#include "beep.h"

int main()
{
	u8 BUTTON_Value_in;
	delay_init(168);
	
	LED_Init();
	BUTTON_Init();
	BEEP_Init();
	
	while(1)
	{
		BUTTON_Value_in = BUTTON_Value(1);
		if(BUTTON_Value_in)
		{
			switch(BUTTON_Value_in)
			{
				case 3:LED0 = !LED0;break;
				case 2:LED1 = !LED1;break;
				case 1:BEEP = !BEEP;break;
				default:break;
			}			
		}
	}
}

