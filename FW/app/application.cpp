/**
 * @file application.cpp
 * @author Aleksandr Ivashov (alexandration@icloud.com)
 * @brief
 *
 * @copyright V
 *
 */
#include <cstdbool>
#include <cstring>

#include "application.h"
#include "version.h"
#include "io/io_gpio.h"
#include "freertos_utils.h"
#include "lvgl.h"
#include "lvgl_main.hpp"
//>>---------------------- Log control
#define LOG_MODULE_NAME app
#if defined(NDEBUG)
#define LOG_MODULE_LEVEL (3)
#else
#define LOG_MODULE_LEVEL (3)
#endif
#include "log_libs.h"
//<<----------------------

//>>---------------------- Local declarations

//<<----------------------

static constexpr TickType_t BLINK_TIMER_PERIOD = 1000;

TimerHandle_t timerBlink;

bool led = false;

static void MainTaskFunc(void *pvParameters)
{
	FRTOS_TimerCreateStatic("lvgl", BLINK_TIMER_PERIOD, pdTRUE, 0,
	[](TimerHandle_t xTimer)
	{
		(void)xTimer;
		led ^= true;
		io_gpio_led(led);
		LOG_INFO("working...");
	},timerBlink);
	xTimerStart(timerBlink, portMAX_DELAY);

	lvgl::Init();

	vTaskDelete(nullptr);
}

/**
 * @brief
 *
 */
void application()
{
	LOG_INFO("Version: %s", FW_VERSION);
	xTaskCreate(MainTaskFunc, "test", configMINIMAL_STACK_SIZE, NULL, 1, nullptr);
	vTaskStartScheduler();
	while(1) {}
}

extern "C" void vApplicationStackOverflowHook(TaskHandle_t xTask, char* pcTaskName)
{
	char* ErrTask = pcTaskName;
	(void)ErrTask;
	while(1);
}

extern "C" void vApplicationTickHook(void)
{
	lv_tick_inc(1);
}