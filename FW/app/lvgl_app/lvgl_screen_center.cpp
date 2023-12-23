#include "lvgl_screen_center.hpp"

#include "lvgl.h"

lv_obj_t * chart;

void lvgl::screen::Center_t::Init()
{
	Common_t::Init();

	lv_obj_t* vertLayout = lv_obj_create(screen);
	lv_obj_set_size(vertLayout, LV_PCT(100), LV_PCT(100));
	lv_obj_set_flex_flow(vertLayout, LV_FLEX_FLOW_COLUMN);
	{
		lv_obj_t* contBar = lv_obj_create(vertLayout);
		lv_obj_set_size(contBar, LV_PCT(100), LV_SIZE_CONTENT);
		lv_obj_align(contBar, LV_ALIGN_TOP_MID, 0, 0);
		lv_obj_set_flex_flow(contBar, LV_FLEX_FLOW_ROW);
		{
			lv_obj_t* label = lv_label_create(contBar);
			lv_label_set_text(label, "Chart");
		}

		/*Create a chart*/
		chart = lv_chart_create(vertLayout);
		lv_obj_set_size(chart, LV_PCT(100), LV_PCT(100));
		lv_chart_set_type(chart, LV_CHART_TYPE_LINE);   /*Show lines and points too*/

		lv_obj_t* contDownBar = lv_obj_create(vertLayout);
		lv_obj_set_size(contDownBar, LV_PCT(100), LV_SIZE_CONTENT);
	}
}

void lvgl::screen::Center_t::Process()
{

}