/**
 * @file application.cpp
 * @author Aleksandr Ivashov (alexandration@icloud.com)
 * @brief
 * @version 0.1
 * @date 2022-10-27
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "application.h"

#include <array>
#include <cstdbool>
#include <cstring>

#include "version.h"
#include "utils/delay.h"
#include "io/io_gpio.h"

/* Azure RTOS includes*/
#include "tx_api.h"
#include "gx_api.h"
#include "guix/pdls_resources.h"
#include "guix/pdls_specifications.h"
#include "gx_win32_display_driver.h"

#define LOG_MODULE_NAME app
#if defined(NDEBUG)
#define LOG_MODULE_LEVEL (3)
#else
#define LOG_MODULE_LEVEL (3)
#endif
#include "log_libs.h"

TX_THREAD my_thread;

/** @addtogroup GUIX
 * @{
 */
GX_WINDOW_ROOT* winRootP; /** The root window is a special GUIX background window, right on top of the canvas. */
/** @} */

void my_thread_entry(ULONG thread_input)
{
	 bool led = false;
	 LOG_INFO("Version: %s", FW_VERSION);
	 while(1)
	 {
		  tx_thread_sleep(TX_TIMER_TICKS_PER_SECOND);
		  io_gpio_led(led);
		  led ^= true;
		  LOG_INFO("working...");
	 }
}

void tx_application_define(void *first_unused_memory)
{
	gx_system_initialize();
	gx_studio_display_configure(DISPLAY_1, win32_chromeart_graphics_driver_setup_565rgb, LANGUAGE_ENGLISH, DISPLAY_1_THEME_1, &winRootP);
	gx_studio_named_widget_create("scrMain", (GX_WIDGET*)winRootP, nullptr);
	gx_widget_show(winRootP);
	gx_system_start();

	/* Create my_thread! */
	tx_thread_create(&my_thread, "My Thread",
	my_thread_entry, 0x1234, first_unused_memory, 1024,
	3, 3, TX_NO_TIME_SLICE, TX_AUTO_START);
}