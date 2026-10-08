#ifndef TIMER_H
#define TIMER_H
#include "define.h"

/*
 * compare: OCRnA value used in TIMER_CTC mode (8 bit for Timer0/2).
 *
 * timer_delay_ms / timer_delay_us and the ultrasonic driver use Timer1,
 * so do not run your own TIMER1 config at the same time as them.
 */
typedef struct { uint8_t timer; uint8_t mode; uint16_t prescaler; uint16_t compare; } Timer_Config;

void timer_init(Timer_Config *t);
void timer_start(Timer_Config *t);
void timer_stop(Timer_Config *t);
void timer_resetCount(Timer_Config *t);
uint16_t timer_getCount(Timer_Config *t);

void timer_delay_ms(uint16_t ms);
void timer_delay_us(uint16_t us);
#endif
