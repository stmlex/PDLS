/**
 * @file timer.c
 * @author Viacheslav (Viacheslav@mcublog.ru)
 * @brief
 * @version 0.1
 * @date 2022-10-02
 *
 * @copyright Mcublog Copyright (c) 2022
 *
 */
#include "timer.h"
//>>---------------------- Log control
#define LOG_MODULE_NAME timer
#if defined(NDEBUG)
#define LOG_MODULE_LEVEL (0)
#else
#define LOG_MODULE_LEVEL (3)
#endif
#include "log_libs.h"
//<<----------------------

//>>---------------------- Public
void timer_init(timer_systick_callback_t systick_callback)
{
}
void timer_irq_enable(void)
{
}
void timer_irq_disable(void)
{
}
//<<----------------------