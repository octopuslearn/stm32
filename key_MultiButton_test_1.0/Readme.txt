	/*********************以下为原版git修改而来，只不过去掉了**************************/
/***原版git void button_init(struct Button* handle, uint8_t(*pin_level)(uint8_t), uint8_t active_level, uint8_t button_id)
修改版      void button_init(struct Button* handle, uint8_t(*pin_level)(), uint8_t active_level);
去掉了一个参数********************************************************************/
	

解释会出现那么多：
按下抬起单机
按下抬起按下抬起双击
按下保持抬起