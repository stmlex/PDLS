/**
 * @file common_type.c
 * @author Viacheslav (Viacheslav@mcublog.ru)
 * @brief
 * @version 0.1
 * @date 2022-10-01
 *
 * @copyright Mcublog Copyright (c) 2022
 *
 */
#include "common_type.h"
//>>---------------------- Log control
#define LOG_MODULE_NAME cm
#if defined(NDEBUG)
#define LOG_MODULE_LEVEL (0)
#else
#define LOG_MODULE_LEVEL (3)
#endif
#include "log_libs.h"
//<<----------------------

//>>---------------------- Public functions
/**
 * @brief
 *
 * @param edge
 * @return const char*
 */
const char *cm_irq_edge_stringify(app_t_irq_edge_t edge)
{
    if (edge == APP_GPIO_IRQ_RISING)
        return "APP_GPIO_IRQ_RISING";
    else if (edge == APP_GPIO_IRQ_FALLING)
        return "APP_GPIO_IRQ_FALLING";
    return "";
}

/**
 * @brief
 *
 * @param value
 * @return const char*
 */
const char *cm_stringify_bool(bool value)
{
    if (value)
        return "True";
    return "False";
}
//<<----------------------