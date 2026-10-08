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
    uint8_t value;

    value = cc[digit];

    if (digit > 9)
    {
        return 0x00;
    }

    if (digit == 0)
    {
        value = cc[0];
    }

    return value;
}


void seven_segment_init(SevenSegment_Config *s)
{
    /* Segment lines are outputs */
    gpio_portMode(s->segment_port, 0xFF);

    /* Digit control lines are outputs */
    gpio_portMode(
        s->digit_port,
        s->tens_mask | s->units_mask
    );

    seven_segment_off(s);
}


void seven_segment_off(SevenSegment_Config *s)
{
    /* Turn both digits OFF */

    gpio_portWrite(
        s->digit_port,
        0x00
    );

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

    uint8_t tens;
    uint8_t units;

    tens = number / 10;
    units = number % 10;

    /*
     * Store the number.
     *
     * Actual multiplexing is done by
     * seven_segment_refresh().
     */

    (void)tens;
    (void)units;
}


void seven_segment_refresh(SevenSegment_Config *s)
{
    static uint8_t number = 0;
    static uint8_t digit = 0;

    uint8_t tens;
    uint8_t units;
    uint8_t pattern;

    tens = number / 10;
    units = number % 10;

    /* Turn both digits OFF before changing segments */

    gpio_portWrite(
        s->digit_port,
        0x00
    );

    if (digit == 0)
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

        gpio_portWrite(
            s->digit_port,
            s->tens_mask
        );

        digit = 1;
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

        gpio_portWrite(
            s->digit_port,
            s->units_mask
        );

        digit = 0;
    }
}
