#ifndef DEFINE_H
#define DEFINE_H

#include <stdint.h>

/* GPIO modes */
#define INPUT   0
#define OUTPUT  1

/* Logic levels */
#define LOW     0
#define HIGH    1


/* GPIO port structure */
typedef struct
{
    uint16_t pin_address;
    uint16_t ddr_address;
    uint16_t port_address;

} GPIO_Port;


/* ATmega2560 GPIO ports */

#define GPIO_PORTA   ((GPIO_Port){0x20, 0x21, 0x22})
#define GPIO_PORTB   ((GPIO_Port){0x23, 0x24, 0x25})
#define GPIO_PORTC   ((GPIO_Port){0x26, 0x27, 0x28})
#define GPIO_PORTD   ((GPIO_Port){0x29, 0x2A, 0x2B})
#define GPIO_PORTE   ((GPIO_Port){0x2C, 0x2D, 0x2E})
#define GPIO_PORTF   ((GPIO_Port){0x2F, 0x30, 0x31})
#define GPIO_PORTG   ((GPIO_Port){0x32, 0x33, 0x34})
#define GPIO_PORTH   ((GPIO_Port){0x100, 0x101, 0x102})
#define GPIO_PORTJ   ((GPIO_Port){0x103, 0x104, 0x105})
#define GPIO_PORTK   ((GPIO_Port){0x106, 0x107, 0x108})
#define GPIO_PORTL   ((GPIO_Port){0x109, 0x10A, 0x10B})

#endif