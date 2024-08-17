/**
 * @author Maksym Palii
 * @brief GPIO driver for ATmega644
 * @version 1.0
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

    // Trace (debug) port
    DDRA = 0xFF;
    // Counter port
    DDRB = 0xFF;
    // Result port
    DDRD = 0xFF;
}
