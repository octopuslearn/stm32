#include "config.h"
#include "bsp_led.h"

void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */

  /*Configure GPIO pins : PAPin PAPin */
  GPIO_InitStruct.Pin = led0_Pin|led1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}


int led_toggle(void)
{
	HAL_GPIO_TogglePin(led0_GPIO_Port, led0_Pin);
	HAL_GPIO_TogglePin(led1_GPIO_Port, led1_Pin);
	return 0;
}

int led0_toggle(void)
{
	HAL_GPIO_TogglePin(led0_GPIO_Port, led0_Pin);
	return 0;
}

int led1_toggle(void)
{
	HAL_GPIO_TogglePin(led1_GPIO_Port, led1_Pin);
	return 0;
}
/*****************************END OF FILE*********************************/
