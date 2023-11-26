/**
 * @file io_gpio.cpp
 * @author Aleksandr Ivashov (alexandration@icloud.com)
 * @brief
 * @date 2023-12-17
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "io_gpio.h"
#include "io_mock.h"

#include <filesystem>

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
static const auto LED_GPIO_FILE_NAME = std::filesystem::path("/tmp/io_led_gpio");
//<<----------------------

/**
 * @brief
 *
 * @param on
 */
void io_gpio_led(bool on)
{
	LOG_INFO("gpio led: switch %s", on ? "ON" : "OFF");
	iomock_write_bool(LED_GPIO_FILE_NAME, on);
}