#ifndef ULTRASONIC_H
#define ULTRASONIC_H
#include "gpio.h"

/* returned when no echo arrives within timeout_us */
#define ULTRASONIC_NO_ECHO  0xFFFF

/* timeout_us: max wait for each echo edge, e.g. 30000 (~5 m); capped at 32767 */
typedef struct { GPIO_Port trig_port; uint8_t trig_pin; GPIO_Port echo_port; uint8_t echo_pin; uint16_t timeout_us; } Ultrasonic_Config;

void ultrasonic_init(Ultrasonic_Config *u);
uint16_t ultrasonic_readDistance(Ultrasonic_Config *u);   /* cm, or ULTRASONIC_NO_ECHO; uses Timer1 */
#endif
