#include "lvgl_main.hpp"

#include "lvgl.h"
#include "lvgl_port.hpp"
#include "freertos_utils.h"

#include "lvgl_screen_load.hpp"
#include "lvgl_screen_center.hpp"

static TaskHandle_t taskLvgl;

static lvgl::screen::Load_t scrLoad;
static lvgl::screen::Center_t scrCenter;

static void InterfaceInit()
{
	scrLoad.Init();
	scrCenter.Init();
	scrCenter.Show();
}

static void LvglTaskFunc(void *pvParameters)
{
	lv_init();
	lvgl_port_init();
	InterfaceInit();

	for(;;)
	{
		lvgl::screen::Common_t::scrActive->Process();
		auto ret = lv_task_handler();
		vTaskDelay(ret);
	}
}

void lvgl::Init()
{
	FRTOS_TaskCreateStaticSafe(LvglTaskFunc, "lvgl", 2048, NULL, 5, taskLvgl);
}