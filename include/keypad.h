#ifndef KEYPAD_H
#define KEYPAD_H
#include "gpio.h"

/*
 * Rows: 4 outputs from row_start, columns: 4 inputs from column_start.
 * active_low = 1: internal pull-ups are enabled on the columns.
 * active_low = 0: the columns need external pull-down resistors.
 */
typedef struct { GPIO_Port row_port; GPIO_Port column_port; uint8_t row_start; uint8_t column_start; uint8_t active_low; } Keypad_Config;

void keypad_init(Keypad_Config *k);
char keypad_getKey(Keypad_Config *k);
#endif
