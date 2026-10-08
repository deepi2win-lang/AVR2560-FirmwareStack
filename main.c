#include "gpio.h"
#include "led.h"
#include "keypad.h"
#include "timer.h"

int main(void)
{
    uint8_t key;

    /* LED on PF0 */
    gpio_portMode(GPIO_PORTF, 0x01);

    led_init(GPIO_PORTF, 0x01);

    keypad_init();

    timer1_init();

    while (1)
    {
        key = keypad_getKey();

        if (key != 0)
        {
            led_on();

            timer1_delay_ms(1000);

            led_off();
        }
    }
}
