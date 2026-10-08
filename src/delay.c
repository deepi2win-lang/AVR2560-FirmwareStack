#include "delay.h"
#include "timer.h"

void delay_ms(uint16_t ms)
{
    timer_delay_ms(ms);
}

void delay_s(uint16_t seconds)
{
    for (uint16_t i = 0; i < seconds; i++)
    {
        timer_delay_ms(1000);
    }
}
