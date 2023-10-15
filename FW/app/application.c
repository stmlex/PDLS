/**
 * @file application.c
 * @author Aleksandr Ivashov (alexandration@icloud.com)
 * @brief
 *
 * @copyright V
 *
 */
#include <stdbool.h>
#include <string.h>

#include "application.h"
#include "version.h"
#include "utils/delay.h"
#include "io/io_gpio.h"
#include "freertos_utils.h"
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

TaskHandle_t taskTest;

void TestTaskFunc(void *pvParameters)
{
    bool led = false;
    for(;;)
    {
        vTaskDelay(1000);
        io_gpio_led(led);
        led ^= true;
        LOG_INFO("working...");
    }
}

/**
 * @brief
 *
 */
void application(void)
{
    LOG_INFO("Version: %s", FW_VERSION);
    FRTOS_TaskCreateStatic(TestTaskFunc, "test", configMINIMAL_STACK_SIZE, NULL, 1, taskTest);
	vTaskStartScheduler();
    while(1) {}
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char* pcTaskName)
{
    char* ErrTask = pcTaskName;
    (void)ErrTask;
	while(1);
}
