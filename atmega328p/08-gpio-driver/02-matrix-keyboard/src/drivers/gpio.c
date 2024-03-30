/**
 * @author Maksym Palii
 * @brief GPIO driver for ATmega328P
 * @version 1.0
 * 
 * Inspired by Niklas Nilsson 
 * @link https://github.com/niklasab
 * @link https://www.artfulbytes.com
 * @link https://www.youtube.com/@artfulbytes
*/

#include "gpio.h"

void gpio_init(void)
{
    GPIO_SET_OUTPUT(LED1);
    GPIO_SET_OUTPUT(LED2);
    GPIO_SET_OUTPUT(LED3);
    GPIO_SET_OUTPUT(LED4);
    GPIO_SET_OUTPUT(LED5);
    GPIO_SET_OUTPUT(LED6);
    GPIO_SET_OUTPUT(LED7);
    GPIO_SET_OUTPUT(LED8);
    GPIO_SET_OUTPUT(LED9);

    GPIO_SET_OUTPUT(COLUMN1);
    GPIO_SET_OUTPUT(COLUMN2);
    GPIO_SET_OUTPUT(COLUMN3);
}
