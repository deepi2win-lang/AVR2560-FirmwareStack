#include "gpio.h"
#include "led.h"
#include "delay.h"

int main(void)
{
    /* Configure PORTF as output */
    gpio_portMode(GPIO_PORTF, 0xFF);

    /* Initialize LED on PF0 */
    led_init(GPIO_PORTF, 0x01);

    while (1)
    {
        led_on();
        delay_s(1);

        led_off();
        delay_s(1);
    }
}
