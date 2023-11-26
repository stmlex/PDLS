/**
 * @file io_mock.cpp
 * @author Aleksandr Ivashov (alexandration@icloud.com)
 * @brief
 * @version 0.1
 * @date 2023-12-16
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "io_mock.h"

#include <iostream>
#include <fstream>

#include "freertos_utils.h"

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
bool iomock_read_bool(const std::filesystem::path& filename)
{
    bool result = false;
    std::fstream fs(filename, std::fstream::in);
    if(!fs.is_open())
    {
        LOG_ERROR("Error while opening: %s", filename);
        return false;
    }
    char ch = fs.get();
    while (ch != EOF)
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
    fs.close();
    return result;
}

/**
 * @brief Write bool state
 *
 * @param filename
 * @param value
 */
void iomock_write_bool(const std::filesystem::path& filename, bool value)
{
    std::ofstream fs{filename};
    if (!fs.is_open())
    {
        LOG_ERROR("Error while opening: %s", filename.c_str());
        return;
    }
    char ch = value ? '1' : '0';
    fs << ch;
    fs.close();
    return;
}

/**
 * @brief Edge detection function
 *
 * @param vargp pointer to iomock_handlers_t struct
 * @return void*
 */
void *iomock_edge_detecting(void* vargp)
{
    iomock_handlers_t *mock_handlers = (iomock_handlers_t *)(vargp);
    bool old_state, new_state;
    old_state = new_state = mock_handlers->state_reading();
    while (1)
    {
        if (mock_handlers == NULL)
        {
            LOG_ERROR("mock_handlers is NULL");
            vTaskDelay(IOMOCK_EDGE_DETECTING_ERROR_PERIOD_MS);
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
        vTaskDelay(IOMOCK_EDGE_DETECTING_PERIOD_MS);
    }
    return NULL;
}

//<<----------------------
