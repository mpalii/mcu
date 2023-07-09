/*
 * @author Maksym Palii
 * @brief GPIO driver, 2Hz blinker for all pins except of RESET
 * @version 1.0
 * @date 2023 July 09
 */

#define F_CPU (8000000UL)

#include <stdbool.h>
#include <util/delay.h>
#include "drivers/gpio.h"

const uint8_t pins[] = 
{
    _GPIO_UNUSED_01, _GPIO_UNUSED_02, _GPIO_UNUSED_03, _GPIO_UNUSED_04,
    _GPIO_UNUSED_05, _GPIO_UNUSED_06, _GPIO_UNUSED_07, _GPIO_UNUSED_08,
    _GPIO_UNUSED_09, _GPIO_UNUSED_10, _GPIO_UNUSED_11, _GPIO_UNUSED_12,
    _GPIO_UNUSED_13, _GPIO_UNUSED_14,                  _GPIO_UNUSED_16, 
    _GPIO_UNUSED_17, _GPIO_UNUSED_18, _GPIO_UNUSED_19, _GPIO_UNUSED_20, 
    _GPIO_UNUSED_21, _GPIO_UNUSED_22, _GPIO_UNUSED_23
};

void set_pins_high(void)
{
    for (uint8_t i = 0; i < sizeof(pins)/sizeof(uint8_t); i++)
    {
        GPIO_HIGH(pins[i]);
    }
}

void set_pins_low(void)
{
    for (uint8_t i = 0; i < sizeof(pins)/sizeof(uint8_t); i++)
    {
        GPIO_LOW(pins[i]);
    }
}

int main(void)
{
    gpio_init();

    while (true)
    {
        set_pins_high();
        _delay_ms(250);

        set_pins_low();
        _delay_ms(250);
    }
}