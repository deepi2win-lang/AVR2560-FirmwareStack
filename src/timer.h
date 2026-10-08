#ifndef TIMER_H
#define TIMER_H
#include "define.h"
typedef struct { uint8_t timer; uint8_t mode; uint16_t prescaler; } Timer_Config;
void timer_init(Timer_Config*t); void timer_start(Timer_Config*t); void timer_stop(Timer_Config*t); void timer_delay_ms(uint16_t ms);
#endif
