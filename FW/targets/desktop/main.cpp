/**
 * @file main.c
 * @author Aleksandr Ivashov (alexandration@icloud.com)
 * @brief
 * @version 0.1
 * @date 2022-10-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "tx_api.h"
#include "gx_api.h"
//>>---------------------- Log control
#define LOG_MODULE_NAME main
#if defined(NDEBUG)
#define LOG_MODULE_LEVEL (0)
#else
#define LOG_MODULE_LEVEL (3)
#endif
#include "log_libs.h"
//<<----------------------

//>>---------------------- Global
extern "C" int main(int argc, char* argv[])
{
    /* Enter the ThreadX kernel. */
    tx_kernel_enter( );
    return 0;
}
//<<----------------------
