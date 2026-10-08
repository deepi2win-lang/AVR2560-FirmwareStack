#include "ultrasonic.h"
#include "timer.h"

void ultrasonic_init(Ultrasonic_Config *u)
{
    gpio_pinMode(u->trig_port, u->trig_pin, OUTPUT);
    gpio_pinMode(u->echo_port, u->echo_pin, INPUT);
    gpio_pinWrite(u->trig_port, u->trig_pin, LOW);
}

uint16_t ultrasonic_readDistance(Ultrasonic_Config *u)
{
    /* Timer1, normal mode, 16 MHz / 8 = 0.5 us per tick */
    Timer_Config t = { TIMER1, TIMER_NORMAL, PRESCALER_8, 0 };

    uint16_t timeout_us = (u->timeout_us > 32767) ? 32767 : u->timeout_us;
    uint16_t timeout_ticks = (uint16_t)(timeout_us * 2);
    uint16_t ticks;

    /* 10 us trigger pulse */
    gpio_pinWrite(u->trig_port, u->trig_pin, LOW);
    timer_delay_us(2);
    gpio_pinWrite(u->trig_port, u->trig_pin, HIGH);
    timer_delay_us(10);
    gpio_pinWrite(u->trig_port, u->trig_pin, LOW);

    timer_init(&t);
    timer_start(&t);

    /* wait for echo to go HIGH */
    while (!gpio_pinRead(u->echo_port, u->echo_pin))
    {
        if (timer_getCount(&t) >= timeout_ticks)
        {
            timer_stop(&t);
            return ULTRASONIC_NO_ECHO;
        }
    }

    /* time the echo pulse */
    timer_resetCount(&t);

    while (gpio_pinRead(u->echo_port, u->echo_pin))
    {
        if (timer_getCount(&t) >= timeout_ticks)
        {
            timer_stop(&t);
            return ULTRASONIC_NO_ECHO;
        }
    }

    timer_stop(&t);
    ticks = timer_getCount(&t);

    /* distance (cm) = time_us / 58 = ticks / 116 */
    return (uint16_t)(ticks / 116);
}
