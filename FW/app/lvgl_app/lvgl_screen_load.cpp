#include "lvgl_screen_load.hpp"

#include "freertos_utils.h"

lv_obj_t* barProgress;
TickType_t startTick = 0;

void lvgl::screen::Load_t::Init()
{
	Common_t::Init();

	barProgress = lv_bar_create(screen);
	lv_obj_center(barProgress);
	lv_bar_set_range(barProgress, 0, 100);
	lv_bar_set_start_value(barProgress, 0, LV_ANIM_ON);

	startTick = xTaskGetTickCount();
}

void lvgl::screen::Load_t::Process()
{
	const auto now = xTaskGetTickCount();
	auto val = (now - startTick) / 100;
	lv_bar_set_value(barProgress, val, LV_ANIM_ON);
}

