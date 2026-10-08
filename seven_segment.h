#ifndef SEVEN_SEGMENT_H
#define SEVEN_SEGMENT_H
#include "gpio.h"
typedef struct { GPIO_Port segment_port; GPIO_Port digit_port; uint8_t common_type; uint8_t digit_mask; } SevenSegment_Config;
void seven_segment_init(SevenSegment_Config*s); void seven_segment_write(SevenSegment_Config*s,uint8_t n); void seven_segment_off(SevenSegment_Config*s);
#endif
