#include "gpio.h"

int main(void)
{
    gpio_portMode(GPIO_PORTF, 0xFF);
    gpio_portWrite(GPIO_PORTF, 0xFF);

    while (1)
    {
    }
}
