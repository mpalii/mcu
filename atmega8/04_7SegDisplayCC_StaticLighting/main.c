/*
 * Created: 24.10.2021 14:11:15
 * Author : Maksym Palii
 */ 

// 7SEG port
#define DDR_7SEG	(DDRB)
#define PORT_7SEG	(PORTB)

#define PIN0		(0)
#define PIN1		(1)
#define PIN2		(2)
#define PIN3		(3)
#define PIN4		(4)
#define PIN5		(5)
#define PIN6		(6)
#define PIN7		(7)

#include <avr/io.h>

/*
 * The DIGITS array stores values for displaying the digits 0-F to a seven-segment display.
 
 * The index of the array element is equivalent to a digit in hexadecimal form,
 * each array element stores the state of the seven-segment port for this digit. 
 */
char DIGITS[] = {
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
	// Configure data direction for pins 0-7 (port 7SEG) as OUTPUT
	DDR_7SEG |= (1 << PIN0) | (1 << PIN1) | (1 << PIN2) | (1 << PIN3) | (1 << PIN4) | (1 << PIN5) | (1 << PIN6) | (1 << PIN7);
	
	// Set port 7SEG state to display E (decimal 14)
	PORT_7SEG = DIGITS[0xE];
		
	while (1) 
	{
		// No logic
	}
}

