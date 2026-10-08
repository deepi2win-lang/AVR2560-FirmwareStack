#ifndef GPIO_H
#define GPIO_H

#include "define.h"

/* Configure complete GPIO port */
void gpio_portMode(GPIO_Port port, uint8_t mode);

/* Write complete GPIO port */
void gpio_portWrite(GPIO_Port port, uint8_t value);

/* Read complete GPIO port */
uint8_t gpio_portRead(GPIO_Port port);

#endif
