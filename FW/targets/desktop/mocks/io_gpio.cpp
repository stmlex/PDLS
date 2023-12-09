/**
 * @file io_gpio.c
 * @author Viacheslav (viacheslav@mcublog.ru)
 * @brief
 * @version 0.1
 * @date 2022-10-27
 *
 * @copyright Viacheslav mcublog (c) 2022
 *
 */
#include "io_gpio.h"
#include "io_mock.h"
//>>---------------------- Log control
#define LOG_MODULE_NAME io_gpio
#if defined(NDEBUG)
#define LOG_MODULE_LEVEL (0)
#else
#define LOG_MODULE_LEVEL (3)
#endif
#include "log_libs.h"
//<<----------------------

//>>---------------------- Local variables
#define LED_GPIO_FILE_NAME "/tmp/io_led_gpio"
//<<----------------------

/**
 * @brief
 *
 * @param on
 */
void io_gpio_led(bool on)
{
    if (on)
        LOG_INFO("gpio led: switch ON");
    else
        LOG_INFO("gpio led: switch OFF");
    iomock_write_bool(LED_GPIO_FILE_NAME, on);
}