#ifndef LVGL_SCREEN_HPP
#define LVGL_SCREEN_HPP

#include "lvgl.h"

namespace lvgl::screen
{
	class Common_t
	{
	public:
		constexpr Common_t() = default;
		void Init();
		void Show();
		virtual void Process() = 0;
		static Common_t* scrActive;
	protected:
		lv_obj_t* screen;
	};
}


#endif /* LVGL_SCREEN_HPP */
