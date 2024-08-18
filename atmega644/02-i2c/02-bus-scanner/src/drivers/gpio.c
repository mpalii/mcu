/**
 * @author Maksym Palii
 * @brief GPIO driver for ATmega644
 * @version 1.0
*/

#include "gpio.h"
#include <stdio.h>

void init_gpio(void)
{
    printf("=> gpio initialization...\r\n");
    /**
     * @def disable JTAG interface in order to make pins 2, 3, 4, 5 (Port C) as general purpose
     * @see https://ww1.microchip.com/downloads/en/DeviceDoc/doc2593.pdf#G1.1375224
     */
    MCUCR |= _BV(JTD);
    MCUCR |= _BV(JTD);

    printf("<= ...success\r\n");
}
