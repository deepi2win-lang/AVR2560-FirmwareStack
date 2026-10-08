#include "gpio.h"


void gpio_portMode(GPIO_Port port, uint8_t mode)
{
    volatile uint8_t *ddr;

    ddr = (volatile uint8_t *)port.ddr_address;

    *ddr = mode;
}


void gpio_portWrite(GPIO_Port port, uint8_t value)
{
    volatile uint8_t *port_reg;

    port_reg = (volatile uint8_t *)port.port_address;

    *port_reg = value;
}


uint8_t gpio_portRead(GPIO_Port port)
{
    volatile uint8_t *pin;

    pin = (volatile uint8_t *)port.pin_address;

    return *pin;
}