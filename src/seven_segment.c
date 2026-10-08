#include "seven_segment.h"

static const uint8_t cc[10] =
{
    0x3F, 0x06, 0x5B, 0x4F, 0x66,
    0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

// Initialize the seven-segment display
void seven_segment_init(SevenSegment_Config *s)
{
    gpio_portMode(s->segment_port, 0xFF);
    gpio_portMode(s->digit_port, s->digit_mask);
    seven_segment_off(s);
}

// Display a digit from 0 to 9
void seven_segment_write(SevenSegment_Config *s, uint8_t n)
{
    if (n > 9)
        return;

    uint8_t v = cc[n];

    if (s->common_type == COMMON_ANODE)
        v = (uint8_t)~v;

    gpio_portWrite(s->segment_port, v);
    gpio_portWrite(s->digit_port, s->digit_mask);
}

// Turn off the seven-segment display
void seven_segment_off(SevenSegment_Config *s)
{
    gpio_portWrite(
        s->segment_port,
        s->common_type == COMMON_ANODE ? 0xFF : 0x00
    );
}
