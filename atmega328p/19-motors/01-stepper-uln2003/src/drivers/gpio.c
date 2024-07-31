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
    //
    GPIO_SET_OUTPUT(LED);

    //
    GPIO_SET_OUTPUT(IN1);
    GPIO_SET_OUTPUT(IN2);
    GPIO_SET_OUTPUT(IN3);
    GPIO_SET_OUTPUT(IN4);
}
