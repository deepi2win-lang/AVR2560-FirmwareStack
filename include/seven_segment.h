#ifndef SEVEN_SEGMENT_H
#define SEVEN_SEGMENT_H
#include "gpio.h"

/*
 * Two multiplexed digits.
 * segment_port: segments a-g, dp on pins 0-7.
 * digit_port:   tens_mask / units_mask pins enable each digit (active high).
 * number, digit: internal state, set to 0.
 */
typedef struct { GPIO_Port segment_port; GPIO_Port digit_port; uint8_t common_type; uint8_t tens_mask; uint8_t units_mask; uint8_t number; uint8_t digit; } SevenSegment_Config;

void seven_segment_init(SevenSegment_Config *s);
void seven_segment_display(SevenSegment_Config *s, uint8_t number);   /* 0-99 */
void seven_segment_refresh(SevenSegment_Config *s);                   /* call every few ms */
void seven_segment_off(SevenSegment_Config *s);
#endif
