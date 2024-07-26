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
    // PD6 Alternate Function - OC0A (Timer/Counter0 Output Compare Match A Output)
    // Configure data direction for pin 6 (port D) as OUTPUT
    GPIO_SET_OUTPUT(OC0A);
}
