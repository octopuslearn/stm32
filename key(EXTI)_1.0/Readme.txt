触发中断后，程序卡死：	

/***！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
	原因是优先级设置HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);		 //此时就不可以了
	               HAL_NVIC_SetPriority(EXTI2_IRQn, 1, 0);//和串口一样，可以使用
	！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！*/


  注意此处，触发方式选择正确，GPIO_InitStruct.Mode = GPIO_MODE_IT_上升沿;
  ***/
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;