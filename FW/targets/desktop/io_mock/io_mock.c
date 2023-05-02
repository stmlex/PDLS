/**
 * @file io_mock.c
 * @author Viacheslav (Viacheslav@mcublog.ru)
 * @brief IO mocking module
 * @version 0.1
 * @date 2022-09-26
 *
 * @copyright Mcublog Copyright (c) 2022
 *
 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils/delay.h"
#include "io_mock.h"
//>>---------------------- Log control
#define LOG_MODULE_NAME iomock
#if defined(NDEBUG)
#define LOG_MODULE_LEVEL (0)
#else
#define LOG_MODULE_LEVEL (3)
#endif
#include "log_libs.h"
//<<----------------------

//>>---------------------- Locals
#define IOMOCK_EDGE_DETECTING_PERIOD_MS (10)
#define IOMOCK_EDGE_DETECTING_ERROR_PERIOD_MS (1000)
//<<----------------------

//>>---------------------- Public functions
/**
 * @brief Read bool value ('1'/'0') from file
 *
 * @param filename
 * @return true
 * @return false
 */
bool iomock_read_bool(const char *filename)
{
    bool result = false;
    FILE *fp = fopen(filename, "r"); // read mode
    if (fp == NULL)
    {
        LOG_ERROR("Error while opening: %s", filename);
        return false;
    }
    char ch = 0;
    while ((ch = fgetc(fp)) != EOF)
    {
        if ('1' == ch)
        {
            result = true;
            break;
        }
        else if ('0' == ch)
        {
            result = false;
            break;
        }
    }
    fclose(fp);
    return result;
}

/**
 * @brief Write bool state
 *
 * @param filename
 * @param value
 */
void iomock_write_bool(const char *filename, bool value)
{
    bool result = false;
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        LOG_ERROR("Error while opening: %s", filename);
        return;
    }
    char ch = value ? '1' : '0';
    fputc(ch, fp);
    fclose(fp);
    return;
}

/**
 * @brief Edge detection function
 *
 * @param vargp pointer to iomock_handlers_t struct
 * @return void*
 */
void *iomock_edge_detecting(void *vargp)
{
    iomock_handlers_t *mock_handlers = (iomock_handlers_t *)(vargp);
    bool old_state, new_state;
    old_state = new_state = mock_handlers->state_reading();
    while (1)
    {
        if (mock_handlers == NULL)
        {
            LOG_ERROR("mock_handlers is NULL");
            delay_ms(IOMOCK_EDGE_DETECTING_ERROR_PERIOD_MS);
            continue;
        }
        new_state = mock_handlers->state_reading();
        if (old_state == false && new_state == true)
        {
            LOG_DEBUG("rising edge detected");
            mock_handlers->irg_handler(IOMOCK_IRQ_RISING);
        }
        else if (old_state == true && new_state == false)
        {
            LOG_DEBUG("falling edge detected");
            mock_handlers->irg_handler(IOMOCK_IRQ_FALLING);
        }
        old_state = new_state;
        delay_ms(IOMOCK_EDGE_DETECTING_PERIOD_MS);
    }
    return NULL;
}

/**
 * @brief
 *
 * @param filename
 * @return true
 * @return false
 */
bool iomock_file_is_exist(const char *filename)
{
    FILE *file;
    bool res = false;
    if ((file = fopen(filename, "r")) == NULL)
    {
        if (errno == ENOENT)
        {
            LOG_INFO("File: %s doesn't exist", filename);
        }
        else
        {
            // Check for other errors too, like EACCES and EISDIR
            LOG_ERROR("Some other error occured");
        }
    }
    else
    {
        fclose(file);
        res = true;
    }
    return res;
}
//<<----------------------
