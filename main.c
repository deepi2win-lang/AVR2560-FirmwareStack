#include "gpio.h"

int main(void)
{
    gpio_portMode(GPIO_PORTA, 0xFF);
    gpio_portWrite(GPIO_PORTA, 0xFF);

    while (1)
    {
    }
}
