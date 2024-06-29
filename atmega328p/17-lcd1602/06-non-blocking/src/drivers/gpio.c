#include "gpio.h"

void init_gpio(void)
{
    // LCD control bus
    GPIO_SET_OUTPUT(RS);
    GPIO_SET_OUTPUT(RW);
    GPIO_SET_OUTPUT(EN);
}