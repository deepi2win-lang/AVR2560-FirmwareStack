#include "led.h"
#include "timer.h"

int main(void)
{
    /* LED on PF0, active high */
    LED_Config led = { GPIO_PORTF, 0, HIGH };

    led_init(&led);

    while (1)
    {
        /* LED ON */
        led_on(&led);

        /* 1 second */
        timer_delay_ms(1000);

        /* LED OFF */
        led_off(&led);

        /* 1 second */
        timer_delay_ms(1000);
    }
}
