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
#include <cstdbool>
#include <cstring>

#include "application.h"
#include "version.h"
#include "utils/delay.h"
#include "io/io_gpio.h"
#include "tx_api.h"

#define LOG_MODULE_NAME app
#if defined(NDEBUG)
#define LOG_MODULE_LEVEL (3)
#else
#define LOG_MODULE_LEVEL (3)
#endif
#include "log_libs.h"

TX_THREAD my_thread;

/**
 * @brief
 *
 */
void application(void)
{
    /* Enter the ThreadX kernel. */
    tx_kernel_enter( );
}

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
    /* Create my_thread! */
    tx_thread_create(&my_thread, "My Thread",
    my_thread_entry, 0x1234, first_unused_memory, 1024,
    3, 3, TX_NO_TIME_SLICE, TX_AUTO_START);
}


