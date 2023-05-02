#ifndef DEBUG_TRACE_H
#define DEBUG_TRACE_H


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define LOG_ERROR(STR, ...)   do{ if (LOG_MODULE_LEVEL>0) {log_printf("err", TOSTRING(LOG_MODULE_NAME), STR, ##__VA_ARGS__);} }while(0)
#define LOG_WARNING(STR, ...) do{ if (LOG_MODULE_LEVEL>1) {log_printf("wrn", TOSTRING(LOG_MODULE_NAME), STR, ##__VA_ARGS__);}  }while(0)
#define LOG_INFO(STR, ...)    do{ if (LOG_MODULE_LEVEL>2) {log_printf("inf", TOSTRING(LOG_MODULE_NAME), STR, ##__VA_ARGS__);}  }while(0)
#define LOG_DEBUG(STR,...)    do{ if (LOG_MODULE_LEVEL>3) {log_printf("dbg", TOSTRING(LOG_MODULE_NAME), STR, ##__VA_ARGS__);} }while(0)
#define LOG_RAW_INFO(STR,...) do{ if (LOG_MODULE_LEVEL>2) {printf(STR, ##__VA_ARGS__);} }while(0)

void log_printf(const char *prefix, const char *module, const char * sFormat, ...);

#ifdef __cplusplus
}
#endif

#endif // DEBUG_TRACE_H
