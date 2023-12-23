#include "lvgl_screen.hpp"

lvgl::screen::Common_t* lvgl::screen::Common_t::scrActive = nullptr;

void lvgl::screen::Common_t::Init()
{
	screen = lv_obj_create(NULL);
	lv_obj_set_size(screen, LV_PCT(100), LV_PCT(100));
}

void lvgl::screen::Common_t::Show()
{
	lv_scr_load(screen);
	scrActive = this;
}
