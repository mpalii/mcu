/**
 * @author Maksym Palii
 * @brief Reaction time measurement
 * @version 1.0
 * @date 2024 October 13
 * @link https://people.ece.cornell.edu/land/courses/ece4760/labs/s2012/lab1.html
 */

#define F_CPU (16000000UL)
 
#include "drivers/gpio.h"
#include <util/delay.h>

const uint8_t pins[] =
{
    // Port A
    _GPIO_UNUSED_01, _GPIO_UNUSED_02, _GPIO_UNUSED_03, _GPIO_UNUSED_04,
    _GPIO_UNUSED_05, _GPIO_UNUSED_06, _GPIO_UNUSED_07, _GPIO_UNUSED_08,
    // Port B
    _GPIO_UNUSED_09, _GPIO_UNUSED_10, _GPIO_UNUSED_11, _GPIO_UNUSED_12,
    _GPIO_UNUSED_13, _GPIO_UNUSED_14, _GPIO_UNUSED_15, _GPIO_UNUSED_16,
    // Port C
    _GPIO_UNUSED_17, _GPIO_UNUSED_18, _GPIO_UNUSED_19, _GPIO_UNUSED_20,
    _GPIO_UNUSED_21, _GPIO_UNUSED_22, _GPIO_UNUSED_23, _GPIO_UNUSED_24,
    // Port D
    _GPIO_UNUSED_25, _GPIO_UNUSED_26, _GPIO_UNUSED_27, _GPIO_UNUSED_28,
    _GPIO_UNUSED_29, _GPIO_UNUSED_30, _GPIO_UNUSED_31, _GPIO_UNUSED_32
};

inline void toggle_all_pins(void)
{
    for (uint8_t i = 0; i < sizeof(pins) / sizeof(pins[0]); i++)
    {
        gpio_toggle(pins[i]);
    }
}

int main(void)
{
    init_gpio();

    while (true)
    {
        toggle_all_pins();
        _delay_ms(125);
    }

    return 0;
}