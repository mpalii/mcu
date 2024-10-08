/**
 * @author Maksym Palii (maksympalii.dev@gmail.com)
 * @brief Visual perception
 * @version 0.1
 * @date 2022-10-23
 */

#define F_CPU (8000000UL/8)
#define FREQUENCY (1)

#include <avr/io.h>
#include <stdbool.h>
#include "custom_delay.h"

int main(void)
{
    // Configure data direction for pins 0 (port D) as OUTPUT
    DDRD |= _BV(PIND0);

    // Set pin 0 (port D) driven high (one)
    PORTD |= _BV(PIND0);

    while (true) 
    {
        _delay_with_frequency();
        PORTD ^= _BV(PIND0);    // toggle pin
    }
}
