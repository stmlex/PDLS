
#ifndef IO_MOCK_H
#define IO_MOCK_H

#include <stdbool.h>

typedef enum
{
    IOMOCK_IRQ_RISING = 0,
    IOMOCK_IRQ_FALLING
} iomock_irq_edge_t;

typedef void (*iomock_irq_handler_t)(iomock_irq_edge_t);
typedef bool (*iomock_reading_t)(void);

typedef struct
{
    iomock_irq_handler_t irg_handler;
    iomock_reading_t state_reading;
} iomock_handlers_t;

#ifdef __cplusplus
extern "C"
{
#endif

    bool iomock_read_bool(const char *filename);
    void iomock_write_bool(const char *filename, bool value);
    void *iomock_edge_detecting(void *vargp);

    bool iomock_file_is_exist(const char *filename);

#ifdef __cplusplus
}
#endif

#endif // IO_MOCK_H