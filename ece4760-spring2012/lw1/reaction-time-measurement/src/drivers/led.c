#include "gpio.h"

void init_led(void)
{
    _gpio_set_output(LED);
}

void led_on(void)
{
    _gpio_high(LED);
}

void led_off(void)
{
    _gpio_low(LED);
}