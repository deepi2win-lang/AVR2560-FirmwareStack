#include "gpio.h"

/* Disable interrupts around a read-modify-write, restore afterwards */
#define ATOMIC_BEGIN()  uint8_t sreg = *(volatile uint8_t *)SREG_ADDR; \
                        __asm__ __volatile__("cli" ::: "memory")
#define ATOMIC_END()    (*(volatile uint8_t *)SREG_ADDR = sreg)

void gpio_portMode(GPIO_Port p, uint8_t m)
{
    volatile uint8_t *reg = (volatile uint8_t *)p.ddr_address;

    *reg = m;
}


void gpio_portWrite(GPIO_Port p, uint8_t v)
{
    volatile uint8_t *reg = (volatile uint8_t *)p.port_address;

    *reg = v;
}

/**
 * @brief Read the current value of a GPIO port.
 *
 * @param p GPIO port configuration.
 * @return Current 8-bit port value.
 */
uint8_t gpio_portRead(GPIO_Port p)
{
    volatile uint8_t *reg = (volatile uint8_t *)p.pin_address;

    return *reg;
}

/**
  @brief Configure the direction of a single GPIO pin.
 
  @param p GPIO port configuration.
 @param b Pin number (0-7).
 @param m Pin mode: 1 = Output, 0 = Input.
 */
void gpio_pinMode(GPIO_Port p, uint8_t b, uint8_t m)
{
    volatile uint8_t *reg = (volatile uint8_t *)p.ddr_address;

    if (b > 7)
    {
        return;
    }

    ATOMIC_BEGIN();

    if (m)
    {
        *reg |= (uint8_t)(1U << b);
    }
    else
    {
        *reg &= (uint8_t)~(1U << b);
    }

    ATOMIC_END();
}

/**
 * @brief Set or clear a single GPIO pin.
 *
 * @param p GPIO port configuration.
 * @param b Pin number (0-7).
 * @param v Pin value: 1 = HIGH, 0 = LOW.
 */
void gpio_pinWrite(GPIO_Port p, uint8_t b, uint8_t v)
{
    volatile uint8_t *reg = (volatile uint8_t *)p.port_address;

    if (b > 7)
    {
        return;
    }

    ATOMIC_BEGIN();

    if (v)
    {
        *reg |= (uint8_t)(1U << b);
    }
    else
    {
        *reg &= (uint8_t)~(1U << b);
    }

    ATOMIC_END();
}

/**
 * @brief Read the logic level of a single GPIO pin.
 *
 * @param p GPIO port configuration.
 * @param b Pin number (0-7).
 * @return 1 if HIGH, 0 if LOW.
 */
uint8_t gpio_pinRead(GPIO_Port p, uint8_t b)
{
    volatile uint8_t *reg = (volatile uint8_t *)p.pin_address;

    if (b > 7)
    {
        return 0;
    }

    return (uint8_t)((*reg >> b) & 1U);
}

/**
 * @brief Toggle the current state of a GPIO pin.
 *
 * @param p GPIO port configuration.
 * @param b Pin number (0-7).
 */
void gpio_pinToggle(GPIO_Port p, uint8_t b)
{
    volatile uint8_t *reg = (volatile uint8_t *)p.port_address;

    if (b > 7)
    {
        return;
    }

    ATOMIC_BEGIN();

    *reg ^= (uint8_t)(1U << b);

    ATOMIC_END();
}
