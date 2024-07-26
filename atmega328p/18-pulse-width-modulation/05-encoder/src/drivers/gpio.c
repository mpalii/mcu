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
    // Encoder
    // GPIO_HIGH(INT0_GPIO);
    // GPIO_HIGH(ENCODER_2ND);

    // LCD control bus
    GPIO_SET_OUTPUT(RS);
    GPIO_SET_OUTPUT(RW);
    GPIO_SET_OUTPUT(EN);
}
