/**
 * @file application.c
 * @author Viacheslav (viacheslav@mcublog.ru)
 * @brief
 * @version 0.1
 * @date 2022-10-27
 *
 * @copyright Viacheslav mcublog (c) 2022
 *
 */
#include <stdbool.h>
#include <string.h>

#include "application.h"
#include "version.h"
#include "utils/delay.h"
#include "io/io_gpio.h"
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

/**
 * @brief
 *
 */
void application(void)
{
    bool led = false;
    LOG_INFO("Version: %s", FW_VERSION);
    while (1)
    {
        delay_ms(1000);
        io_gpio_led(led);
        led ^= true;
        LOG_INFO("working...");
    }
}