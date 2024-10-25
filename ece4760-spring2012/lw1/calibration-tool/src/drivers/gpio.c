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
    GPIO_LOW(INT0_GPIO);
    GPIO_SET_OUTPUT(BUTTON_TRIGGER);
    GPIO_HIGH(BUTTON_TRIGGER);

    GPIO_SET_OUTPUT(LED);
    GPIO_HIGH(LED);
}
