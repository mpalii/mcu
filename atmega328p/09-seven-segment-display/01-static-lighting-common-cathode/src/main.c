/**
 * @author Maksym Palii
 * @brief seven-segment display with common anode, static lighting
 * @version 1.0
 * @date 2024 February 14
 */

#define F_CPU (8000000UL)

#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

/*
 * The DIGITS array stores values for displaying the digits 0-F to a seven-segment display.
 *
 * The index of the array element is equivalent to a digit in hexadecimal form,
 * each array element stores the state of the seven-segment port for this digit. 
 */
const char DIGITS[] = {
    0b00111111,		// 0
    0b00000110,		// 1
    0b01011011,		// 2
    0b01001111,		// 3
    0b01100110,		// 4
    0b01101101,		// 5
    0b01111101,		// 6
    0b00000111,		// 7
    0b01111111,		// 8
    0b01101111,		// 9
    0b01110111,		// A (decimal 10)
    0b01111100,		// B (decimal 11)
    0b00111001,		// C (decimal 12)
    0b01011110,		// D (decimal 13)
    0b01111001,		// E (decimal 14)
    0b01110001		// F (decimal 15)
};

int main(void)
{
    // Configure data direction for pins 0-7 (port D) as OUTPUT
    DDRD |= 0xFF;
	
    // Set port D state to display digit
    while (true) 
    {
        for (uint8_t i = 0; i < 16; i++)
        {
            PORTD = DIGITS[i];
            _delay_ms(1000);
        }

        for (int8_t i = 15; i >= 0; i--)
        {
            PORTD = DIGITS[i];
            _delay_ms(250);
        }
    }
}