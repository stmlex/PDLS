/**
 * @file delay.c
 * @author Viacheslav (Viacheslav@mcublog.ru)
 * @brief
 * @version 0.1
 * @date 2022-09-27
 *
 * @copyright Mcublog Copyright (c) 2022
 *
 */
#include <unistd.h>

#include "utils/delay.h"
//>>---------------------- Log control
#define LOG_MODULE_NAME delay_mock
#if defined(NDEBUG)
#define LOG_MODULE_LEVEL (0)
#else
#define LOG_MODULE_LEVEL (3)
#endif
#include "log_libs.h"
//<<----------------------

#define MS_MULT (1000)

/**
 * @brief
 *
 * @param ms
 */
void delay_ms(uint32_t ms)
{
    usleep(ms * MS_MULT);
}