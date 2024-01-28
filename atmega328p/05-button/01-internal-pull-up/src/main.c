/**
 * @author Maksym Palii
 * @brief Button with internal PULL-UP resistor, no debounce
 * @version 1.0
 * @date 2024 January 25
 */

#include <avr/io.h>
#include <stdbool.h>    

int main(void)
{
    // Configure data direction for pin 0, 1 (port B) as OUTPUT
    DDRB |= (_BV(DDB0) | _BV(DDB1));
    // Enable internal pull-up resistor pin 0 (port C)
    PORTC |= _BV(PORTC0);

    bool button_was_pressed = false;

    while (true)
    {
        // check whether button was pressed
        if (bit_is_clear(PINC, PINC0) && !button_was_pressed)
        {
            button_was_pressed = true;
            PORTB ^= _BV(PORTB0);
            // some event start
        }
        
        // check whether button was released
        if (bit_is_set(PINC, PINC0) && button_was_pressed)
        {
            button_was_pressed = false;
            PORTB ^= _BV(PORTB1);
            // some event finish
        }
    }
}