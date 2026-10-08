#include "timer.h"
static volatile uint8_t*R(uint16_t a){return (volatile uint8_t*)a;}
static uint8_t bits(uint16_t p){switch(p){case 1:return 1;case 8:return 2;case 64:return 3;case 256:return 4;case 1024:return 5;default:return 0;}}
void timer_init(Timer_Config*t){if(t->timer==TIMER0){*R(TCCR0A_ADDR)=(t->mode==TIMER_CTC)?(1<<1):0;*R(TCCR0B_ADDR)=0;}else if(t->timer==TIMER2){*R(TCCR2A_ADDR)=(t->mode==TIMER_CTC)?(1<<1):0;*R(TCCR2B_ADDR)=0;} }
void timer_start(Timer_Config*t){if(t->timer==TIMER0)*R(TCCR0B_ADDR)=bits(t->prescaler);else if(t->timer==TIMER2)*R(TCCR2B_ADDR)=bits(t->prescaler);}
void timer_stop(Timer_Config*t){if(t->timer==TIMER0)*R(TCCR0B_ADDR)=0;else if(t->timer==TIMER2)*R(TCCR2B_ADDR)=0;}
void timer_delay_ms(uint16_t ms){volatile uint32_t i;while(ms--){for(i=0;i<4000UL;i++){__asm__ __volatile__("nop");}}}
