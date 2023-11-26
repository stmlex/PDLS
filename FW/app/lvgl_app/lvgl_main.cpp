#include "lvgl_main.hpp"

#include "lvgl.h"
#include "lvgl_port.hpp"
#include "freertos_utils.h"

static TaskHandle_t taskLvgl;

static void LvglTaskFunc(void *pvParameters)
{
	lv_init();
	lvgl_port_init();

	for(;;)
	{
		auto ret = lv_task_handler();
		vTaskDelay(ret);
	}
}

void lvgl::Init()
{
	FRTOS_TaskCreateStaticSafe(LvglTaskFunc, "lvgl", 2048, NULL, 5, taskLvgl);
}