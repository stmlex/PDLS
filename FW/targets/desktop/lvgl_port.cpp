#include "lvgl_port.hpp"

static constexpr size_t DISP_HOR_RES = 320;
static constexpr size_t DISP_VER_RES = 240;

bool lvgl_port_init()
{
	auto ret = false;

#if defined USE_WIN32DRV
	ret = lv_win32_init(GetModuleHandleW(NULL), SW_SHOW, DISP_HOR_RES, DISP_VER_RES, LoadIconW(GetModuleHandleW(NULL), nullptr));
#elif defined USE_SDL
	ret = lv_sdl_init();
#endif
	return ret;
}
