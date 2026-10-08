#include "delay.h"

#define F_CPU 16000000UL

void delay_ms(uint16_t ms)
{
    volatile uint32_t i;
    volatile uint32_t j;

    for (i = 0; i < ms; i++)
    {
        for (j = 0; j < 4000; j++)
        {

        }
    }
}

void delay_s(uint16_t seconds)
{
    for (uint16_t i = 0; i < seconds; i++)
    {
        delay_ms(1000);
    }
}
