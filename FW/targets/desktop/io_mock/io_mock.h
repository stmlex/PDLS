
#ifndef IO_MOCK_H
#define IO_MOCK_H

#include <cstdbool>
#include <filesystem>

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

bool iomock_read_bool(const std::filesystem::path& filename);
void iomock_write_bool(const std::filesystem::path& filename, bool value);
void *iomock_edge_detecting(void *vargp);

#endif // IO_MOCK_H