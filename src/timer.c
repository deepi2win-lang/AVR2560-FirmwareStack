#include "timer.h"

/* Convert register address to pointer */
static volatile uint8_t *R(uint16_t a)
{
    return (volatile uint8_t *)a;
}

static volatile uint16_t *R16(uint16_t a)
{
    return (volatile uint16_t *)a;
}

/* Convert prescaler value to CS bits for Timer0 / Timer1 */
static uint8_t bits(uint16_t p)
{
    switch (p)
    {
        case 1:
            return 1;

        case 8:
            return 2;

        case 64:
            return 3;

        case 256:
            return 4;

        case 1024:
            return 5;

        default:
            return 0;
    }
}

/* Timer2 has its own CS table (adds /32 and /128) */
static uint8_t bits_timer2(uint16_t p)
{
    switch (p)
    {
        case 1:
            return 1;

        case 8:
            return 2;

        case 32:
            return 3;

        case 64:
            return 4;

        case 128:
            return 5;

        case 256:
            return 6;

        case 1024:
            return 7;

        default:
            return 0;
    }
}

/* Initialize Timer0, Timer1 or Timer2 (timer stays stopped) */
void timer_init(Timer_Config *t)
{
    if (t->timer == TIMER0)
    {
        /* CTC = WGM01 in TCCR0A */
        *R(TCCR0A_ADDR) =
            (t->mode == TIMER_CTC) ? (1 << 1) : 0;

        *R(TCCR0B_ADDR) = 0;
        *R(TCNT0_ADDR) = 0;
        *R(OCR0A_ADDR) = (uint8_t)t->compare;
    }

    else if (t->timer == TIMER1)
    {
        *R(TCCR1A_ADDR) = 0;

        /* CTC = WGM12 in TCCR1B */
        *R(TCCR1B_ADDR) =
            (t->mode == TIMER_CTC) ? (1 << 3) : 0;

        *R16(TCNT1_ADDR) = 0;
        *R16(OCR1A_ADDR) = t->compare;
    }

    else if (t->timer == TIMER2)
    {
        /* CTC = WGM21 in TCCR2A */
        *R(TCCR2A_ADDR) =
            (t->mode == TIMER_CTC) ? (1 << 1) : 0;

        *R(TCCR2B_ADDR) = 0;
        *R(TCNT2_ADDR) = 0;
        *R(OCR2A_ADDR) = (uint8_t)t->compare;
    }
}

/* Start timer with selected prescaler (keeps the WGM bits) */
void timer_start(Timer_Config *t)
{
    if (t->timer == TIMER0)
    {
        *R(TCCR0B_ADDR) = (uint8_t)((*R(TCCR0B_ADDR) & ~0x07) | bits(t->prescaler));
    }

    else if (t->timer == TIMER1)
    {
        *R(TCCR1B_ADDR) = (uint8_t)((*R(TCCR1B_ADDR) & ~0x07) | bits(t->prescaler));
    }

    else if (t->timer == TIMER2)
    {
        *R(TCCR2B_ADDR) = (uint8_t)((*R(TCCR2B_ADDR) & ~0x07) | bits_timer2(t->prescaler));
    }
}

/* Stop timer (clears only the clock select bits) */
void timer_stop(Timer_Config *t)
{
    if (t->timer == TIMER0)
    {
        *R(TCCR0B_ADDR) &= (uint8_t)~0x07;
    }

    else if (t->timer == TIMER1)
    {
        *R(TCCR1B_ADDR) &= (uint8_t)~0x07;
    }

    else if (t->timer == TIMER2)
    {
        *R(TCCR2B_ADDR) &= (uint8_t)~0x07;
    }
}

/* Reset the counter to 0 */
void timer_resetCount(Timer_Config *t)
{
    if (t->timer == TIMER0)
    {
        *R(TCNT0_ADDR) = 0;
    }

    else if (t->timer == TIMER1)
    {
        *R16(TCNT1_ADDR) = 0;
    }

    else if (t->timer == TIMER2)
    {
        *R(TCNT2_ADDR) = 0;
    }
}

/* Read the current counter value */
uint16_t timer_getCount(Timer_Config *t)
{
    if (t->timer == TIMER0)
    {
        return *R(TCNT0_ADDR);
    }

    else if (t->timer == TIMER1)
    {
        return *R16(TCNT1_ADDR);
    }

    else if (t->timer == TIMER2)
    {
        return *R(TCNT2_ADDR);
    }

    return 0;
}

/* Wait for one Timer1 CTC period: OCR1A = top, cs = clock select bits */
static void timer1_wait(uint16_t top, uint8_t cs)
{
    *R(TCCR1A_ADDR) = 0;
    *R(TCCR1B_ADDR) = 0;
    *R16(TCNT1_ADDR) = 0;
    *R16(OCR1A_ADDR) = top;

    /* clear OCF1A by writing 1 */
    *R(TIFR1_ADDR) = (1 << 1);

    /* CTC (WGM12) + prescaler */
    *R(TCCR1B_ADDR) = (uint8_t)((1 << 3) | cs);

    while (!(*R(TIFR1_ADDR) & (1 << 1)))
    {
    }

    *R(TCCR1B_ADDR) = 0;
}

/* Hardware delay in milliseconds (Timer1, 16 MHz) */
void timer_delay_ms(uint16_t ms)
{
    while (ms--)
    {
        /* 16 MHz / 64 = 250 kHz, 250 ticks = 1 ms */
        timer1_wait(249, bits(PRESCALER_64));
    }
}

/* Hardware delay in microseconds (Timer1, 16 MHz) */
void timer_delay_us(uint16_t us)
{
    while (us > 0)
    {
        /* 16 MHz / 8 = 2 MHz, 2 ticks = 1 us; OCR1A is 16 bit */
        uint16_t chunk = (us > 32767) ? 32767 : us;

        timer1_wait((uint16_t)(chunk * 2 - 1), bits(PRESCALER_8));

        us -= chunk;
    }
}
