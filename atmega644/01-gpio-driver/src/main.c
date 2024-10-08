/**
 * @author Maksym Palii
 * @brief 644 gpio driver test
 * @version 1.0
 * @date 2024 August 13
 */

#define F_CPU (16000000UL)
#define DELAY (100UL)
 
#include <util/delay.h>
#include "drivers/gpio.h"    

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

int main(void) 
{
    init_gpio();

    while (true)
    {
        for (uint8_t i = 0; i < sizeof(pins)/sizeof(uint8_t); i++)
        {
            uint8_t pin = pins[i];
            GPIO_TOGGLE(pin);
        }

        _delay_ms(DELAY);
    }
}   
  