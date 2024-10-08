/**
 * @author Maksym Palii (maksympalii.dev@gmail.com)
 * @brief Delay example
 * @version 0.1
 * @date 2022-04-18
 */

#define F_CPU (8000000UL/8)

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    // Configure data direction for pins 0 and 1 (port B) as OUTPUT
    DDRB = 0b00000011;
    // Set pin 0 driven high (one) and pin 1 driven low (zero) (port B)
    PORTB = 0b00000001;

    while (1) 
    {
        _delay_ms(2000);
        PORTB ^= _BV(PORTB0) | _BV(PORTB1);    // toggle pins
    }
}
