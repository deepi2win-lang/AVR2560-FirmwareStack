#ifndef ULTRASONIC_H
#define ULTRASONIC_H
#include "gpio.h"
typedef struct { GPIO_Port trig_port; uint8_t trig_pin; GPIO_Port echo_port; uint8_t echo_pin; uint16_t timeout_us; } Ultrasonic_Config;
void ultrasonic_init(Ultrasonic_Config*u); uint16_t ultrasonic_readDistance(Ultrasonic_Config*u);
#endif
