#include "keypad.h"
#include "timer.h"

#define KEYPAD_SETTLE_US    5
#define KEYPAD_DEBOUNCE_MS  20

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
    uint8_t idle = k->active_low ? HIGH : LOW;

    for (uint8_t i = 0; i < 4; i++)
    {
        gpio_pinMode(k->row_port, k->row_start + i, OUTPUT);
        gpio_pinWrite(k->row_port, k->row_start + i, idle);
    }

    for (uint8_t i = 0; i < 4; i++)
    {
        gpio_pinMode(k->column_port, k->column_start + i, INPUT);

        /* active low: idle columns are held HIGH by the internal pull-up */
        if (k->active_low)
        {
            gpio_pinWrite(k->column_port, k->column_start + i, HIGH);
        }
    }
}

/* Drive one row active and check one column; only touches the keypad pins */
static uint8_t key_down(Keypad_Config *k, uint8_t r, uint8_t c)
{
    uint8_t active = k->active_low ? LOW : HIGH;
    uint8_t v;

    gpio_pinWrite(k->row_port, k->row_start + r, active);
    timer_delay_us(KEYPAD_SETTLE_US);

    v = gpio_pinRead(k->column_port, k->column_start + c);

    gpio_pinWrite(k->row_port, k->row_start + r, (uint8_t)!active);

    return v == active;
}

/**
 * @brief Scan the keypad and return the pressed key.
 *
 * The key is debounced and returned once per press:
 * this waits until the key is released.
 *
 * @param k Keypad configuration.
 * @return Character corresponding to the pressed key,
 *         or 0 if no key is pressed.
 */
char keypad_getKey(Keypad_Config *k)
{
    for (uint8_t r = 0; r < 4; r++)
    {
        for (uint8_t c = 0; c < 4; c++)
        {
            if (!key_down(k, r, c))
            {
                continue;
            }

            timer_delay_ms(KEYPAD_DEBOUNCE_MS);

            if (!key_down(k, r, c))
            {
                return 0;
            }

            while (key_down(k, r, c))
            {
            }

            timer_delay_ms(KEYPAD_DEBOUNCE_MS);

            return keys[r][c];
        }
    }

    return 0;
}
