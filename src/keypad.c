#include "keypad.h"

static const char keys[4][4] =
{
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

/**
 * @brief Initialize the 4x4 keypad.
 *
 * @param k Keypad configuration.
 */
void keypad_init(Keypad_Config *k)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        gpio_pinMode(k->row_port, k->row_start + i, OUTPUT);
        gpio_pinWrite(k->row_port, k->row_start + i, HIGH);
    }

    for (uint8_t i = 0; i < 4; i++)
    {
        gpio_pinMode(k->column_port, k->column_start + i, INPUT);
    }
}

/**
 * @brief Scan the keypad and return the pressed key.
 *
 * @param k Keypad configuration.
 * @return Character corresponding to the pressed key,
 *         or 0 if no key is pressed.
 */
char keypad_getKey(Keypad_Config *k)
{
    for (uint8_t r = 0; r < 4; r++)
    {
        gpio_portWrite(k->row_port, 0xFF);

        gpio_pinWrite(
            k->row_port,
            k->row_start + r,
            k->active_low ? LOW : HIGH
        );

        for (uint8_t c = 0; c < 4; c++)
        {
            uint8_t v = gpio_pinRead(
                k->column_port,
                k->column_start + c
            );

            if (v == (k->active_low ? LOW : HIGH))
            {
                return keys[r][c];
            }
        }
    }

    return 0;
}
