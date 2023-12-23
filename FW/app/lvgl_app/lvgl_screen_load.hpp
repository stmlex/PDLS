#ifndef LVGL_SCREEN_LOAD
#define LVGL_SCREEN_LOAD

#include "lvgl_screen.hpp"

namespace lvgl::screen
{
	class Load_t : public Common_t
	{
	public:
		void Init();
		virtual void Process() final;
	};
};

#endif /* LVGL_SCREEN_LOAD */
