#include "gpio.h"
#include "led.h"
#include "timer.h"

int main(void)
{
    /* PF0 as output */
    gpio_portMode(GPIO_PORTF, 0x01);

    /* LED on PF0 */
    led_init(GPIO_PORTF, 0x01);

    /* Initialize Timer1 */
    timer1_init();

    while (1)
    {
        /* LED ON */
        led_on();

        /* 1 second */
        timer1_delay_ms(1000);

        /* LED OFF */
        led_off();

        /* 1 second */
        timer1_delay_ms(1000);
    }
}
