/**
 * @file log_libs.c
 * @author Viacheslav (viacheslav@mcublog.ru)
 * @brief
 * @version 0.1
 * @date 2022-09-03
 *
 * @copyright Mcublog Copyright (c) 2022
 *
 */
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

#include "log_libs.h"

void log_printf(const char *prefix, const char *module, const char *sFormat, ...) {
    printf("%s> %s: ", prefix, module);
    va_list ParamList;
    va_start(ParamList, sFormat);
    vprintf(sFormat, ParamList);
    va_end(ParamList);
    printf("\n");
}
