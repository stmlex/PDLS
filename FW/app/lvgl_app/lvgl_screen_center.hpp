#ifndef LVGL_SCREEN_CENTER_HPP
#define LVGL_SCREEN_CENTER_HPP

#include "lvgl_screen.hpp"

namespace lvgl::screen
{
	class Center_t : public Common_t
	{
	public:
		void Init();
		virtual void Process() final;
	};
}

#endif /* LVGL_SCREEN_CENTER_HPP */
