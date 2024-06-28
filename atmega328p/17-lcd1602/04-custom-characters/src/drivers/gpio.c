/**
 * @author Maksym Palii
 * @brief GPIO driver for ATmega328P
 * @version 2.0
 * 
 * Inspired by Niklas Nilsson 
 * @link https://github.com/niklasab
 * @link https://www.artfulbytes.com
 * @link https://www.youtube.com/@artfulbytes
*/

#include "gpio.h"

void init_gpio(void)
{
    // LCD control bus
    GPIO_SET_OUTPUT(RS);
    GPIO_SET_OUTPUT(RW);
    GPIO_SET_OUTPUT(EN);
}
