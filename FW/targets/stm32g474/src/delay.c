/**
 * @file delay.c
 * @author Viacheslav (Viacheslav@mcublog.ru)
 * @brief
 * @version 0.1
 * @date 2022-10-02
 *
 * @copyright Mcublog Copyright (c) 2022
 *
 */
#include "delay.h"
#include "main.h"
//>>---------------------- Log control
#define LOG_MODULE_NAME delay
#if defined(NDEBUG)
#define LOG_MODULE_LEVEL (0)
#else
#define LOG_MODULE_LEVEL (3)
#endif
#include "log_libs.h"
//<<----------------------

//>>---------------------- Public

/**
 * @brief
 *
 * @param ms
 */
void delay_ms(uint32_t ms)
{
  HAL_Delay(ms);
}
//<<----------------------