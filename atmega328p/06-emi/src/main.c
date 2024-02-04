/**
 * @author Maksym Palii
 * @brief EMI (electromagnetic interference)  
 * @version 1.0
 * @date 2024 February 4
 */

#include <avr/io.h>

int main(void)
{
    // Configure data direction for pin 0 (port D) as OUTPUT
    DDRD |= _BV(DDD0);

    start:
        // Check the PB0 state
        if (bit_is_set(PINB, PINB0)) 
        {
            PORTD |= _BV(PORTD0);
        }
        else 
        {
            PORTD &= ~(_BV(PORTD0));
        }
    goto start;
}
