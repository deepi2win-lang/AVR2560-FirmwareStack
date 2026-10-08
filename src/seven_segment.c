#include "seven_segment.h"


/* Common-cathode 7-segment patterns */

static const uint8_t cc[10] =
{
    0x3F,   /* 0 */
    0x06,   /* 1 */
    0x5B,   /* 2 */
    0x4F,   /* 3 */
    0x66,   /* 4 */
    0x6D,   /* 5 */
    0x7D,   /* 6 */
    0x07,   /* 7 */
    0x7F,   /* 8 */
    0x6F    /* 9 */
};


static uint8_t digit_pattern(uint8_t digit)
{
    if (digit > 9)
    {
        return 0x00;
    }

    return cc[digit];
}


/* Set or clear only the digit-enable pins, leaving the rest of the port alone */
static void digits_write(SevenSegment_Config *s, uint8_t mask)
{
    uint8_t all = s->tens_mask | s->units_mask;

    for (uint8_t b = 0; b < 8; b++)
    {
        if (all & (1U << b))
        {
            gpio_pinWrite(s->digit_port, b, (mask >> b) & 1U);
        }
    }
}


void seven_segment_init(SevenSegment_Config *s)
{
    /* Segment lines are outputs */
    gpio_portMode(s->segment_port, 0xFF);

    /* Digit control lines are outputs */
    for (uint8_t b = 0; b < 8; b++)
    {
        if ((s->tens_mask | s->units_mask) & (1U << b))
        {
            gpio_pinMode(s->digit_port, b, OUTPUT);
        }
    }

    s->number = 0;
    s->digit = 0;

    seven_segment_off(s);
}


void seven_segment_off(SevenSegment_Config *s)
{
    /* Turn both digits OFF */

    digits_write(s, 0x00);

    /* Turn all segments OFF */

    if (s->common_type == COMMON_ANODE)
    {
        gpio_portWrite(s->segment_port, 0xFF);
    }
    else
    {
        gpio_portWrite(s->segment_port, 0x00);
    }
}


void seven_segment_display(
    SevenSegment_Config *s,
    uint8_t number
)
{
    if (number > 99)
    {
        return;
    }

    /*
     * Store the number.
     *
     * Actual multiplexing is done by
     * seven_segment_refresh().
     */

    s->number = number;
}


void seven_segment_refresh(SevenSegment_Config *s)
{
    uint8_t tens;
    uint8_t units;
    uint8_t pattern;

    tens = s->number / 10;
    units = s->number % 10;

    /* Turn both digits OFF before changing segments */

    digits_write(s, 0x00);

    if (s->digit == 0)
    {
        /* Tens digit */

        pattern = digit_pattern(tens);

        if (s->common_type == COMMON_ANODE)
        {
            pattern = (uint8_t)~pattern;
        }

        gpio_portWrite(
            s->segment_port,
            pattern
        );

        digits_write(s, s->tens_mask);

        s->digit = 1;
    }
    else
    {
        /* Units digit */

        pattern = digit_pattern(units);

        if (s->common_type == COMMON_ANODE)
        {
            pattern = (uint8_t)~pattern;
        }

        gpio_portWrite(
            s->segment_port,
            pattern
        );

        digits_write(s, s->units_mask);

        s->digit = 0;
    }
}
