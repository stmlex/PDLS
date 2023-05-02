
#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    APP_GPIO_IRQ_RISING = 0,
    APP_GPIO_IRQ_FALLING
} app_t_irq_edge_t;

typedef bool(*app_t_gpio_irq_handler_t)(app_t_irq_edge_t);

#ifdef __cplusplus
extern "C" {
#endif

    const char *cm_irq_edge_stringify(app_t_irq_edge_t edge);
    const char *cm_stringify_bool(bool value);

#ifdef __cplusplus
}
#endif

#endif // COMMON_TYPES_H