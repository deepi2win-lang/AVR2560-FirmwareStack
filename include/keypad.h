#ifndef KEYPAD_H
#define KEYPAD_H
#include "gpio.h"
typedef struct { GPIO_Port row_port; GPIO_Port column_port; uint8_t row_start; uint8_t column_start; uint8_t active_low; } Keypad_Config;
void keypad_init(Keypad_Config*k); char keypad_getKey(Keypad_Config*k);
#endif
