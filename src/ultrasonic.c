#include "ultrasonic.h"
#include "timer.h"
void ultrasonic_init(Ultrasonic_Config*u){gpio_pinMode(u->trig_port,u->trig_pin,OUTPUT);gpio_pinMode(u->echo_port,u->echo_pin,INPUT);gpio_pinWrite(u->trig_port,u->trig_pin,LOW);}
uint16_t ultrasonic_readDistance(Ultrasonic_Config*u){uint16_t t=0;gpio_pinWrite(u->trig_port,u->trig_pin,LOW);timer_delay_ms(1);gpio_pinWrite(u->trig_port,u->trig_pin,HIGH);for(volatile uint16_t i=0;i<20;i++)__asm__ __volatile__("nop");gpio_pinWrite(u->trig_port,u->trig_pin,LOW);while(!gpio_pinRead(u->echo_port,u->echo_pin)){if(t++>=u->timeout_us)return 0;}t=0;while(gpio_pinRead(u->echo_port,u->echo_pin)){if(t++>=u->timeout_us)break;}return (uint16_t)(t/58);}
