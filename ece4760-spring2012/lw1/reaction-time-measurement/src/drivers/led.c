#include <stdbool.h>
#include "gpio.h"
#include "uart.h"

static bool is_enabled = true;

void init_led(void)
{
    _gpio_set_output(LED);
    _gpio_high(LED);
    uart_transmit("- LED ready\r\n");
}

void led_on(void)
{
    if (is_enabled)
    {
        _gpio_low(LED);
    }
}

void led_off(void)
{
    _gpio_high(LED);
}

bool led_toggle_enable_flag(void)
{
    is_enabled = is_enabled ? false : true;
    return is_enabled;
}