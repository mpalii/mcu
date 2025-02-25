/*
 * General purpose IO pins assignment and handling
 * ATmega644 has 32 general purpose IO lines
 * Four 8bit ports (A, B, C, and D)
 */

#include "gpio.h"

void init_gpio(void)
{
    /**
     * @def disable JTAG interface in order to make pins 2, 3, 4, 5 (Port C) as general purpose
     * @see https://ww1.microchip.com/downloads/en/DeviceDoc/doc2593.pdf#G1.1375224
     */
    MCUCR |= _BV(JTD);
    MCUCR |= _BV(JTD);

    // _gpio_set_output(_PA1);
    // _gpio_high(_PA1);
}
