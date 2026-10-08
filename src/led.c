#include "led.h"

// Initialize the LED GPIO pin
void led_init(LED_Config *l)
{
    gpio_pinMode(l->port, l->pin, OUTPUT);
    led_off(l);
}

// Turn the LED on
void led_on(LED_Config *l)
{
    gpio_pinWrite(l->port, l->pin, l->active_level);
}

// Turn the LED off
void led_off(LED_Config *l)
{
    gpio_pinWrite(l->port, l->pin, (uint8_t)!l->active_level);
}

// Toggle the current state of the LED
void led_toggle(LED_Config *l)
{
    gpio_pinToggle(l->port, l->pin);
}
