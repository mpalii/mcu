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
    GPIO_SET_OUTPUT(SEGMENT_a);
    GPIO_SET_OUTPUT(SEGMENT_b);
    GPIO_SET_OUTPUT(SEGMENT_c);
    GPIO_SET_OUTPUT(SEGMENT_d);
    GPIO_SET_OUTPUT(SEGMENT_e);
    GPIO_SET_OUTPUT(SEGMENT_f);
    GPIO_SET_OUTPUT(SEGMENT_g);
    GPIO_SET_OUTPUT(SEGMENT_dp);

    GPIO_SET_OUTPUT(DIGIT_1);
    GPIO_SET_OUTPUT(DIGIT_2);
    GPIO_SET_OUTPUT(DIGIT_3);
    GPIO_SET_OUTPUT(DIGIT_4);

    GPIO_SET_OUTPUT(LED);
}
