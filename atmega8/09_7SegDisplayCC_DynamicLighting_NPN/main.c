/*
 * Created: 24.10.2021 22:12:02
 * Author : Maksym Palii
 */ 
 
 // PINs
#define PIN0		(0)
#define PIN1		(1)
#define PIN2		(2)
#define PIN3		(3)
#define PIN4		(4)
#define PIN5		(5)
#define PIN6		(6)
#define PIN7		(7)

// 7SEG number of digits
#define TOTAL_DIGITS 4

// 7SEG data port
#define DDR_7SEG	(DDRD)
#define PORT_7SEG	(PORTD)

// 7SEG common cathode port
#define DDR_CC		(DDRC)
#define PORT_CC		(PORTC)

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

// Value to print
unsigned int value = 2021;

/*
 * The DIGITS array stores values for displaying the digits 0-9 to a seven-segment display.
 
 * The index of the array element is equivalent to a digit in decimal form,
 * each array element stores the state of the seven-segment port for this digit. 
 */
int digits [10] =
{
	0b00111111, //0
	0b00000110, //1
	0b01011011, //2
	0b01001111, //3
	0b01100110, //4
	0b01101101, //5
	0b01111101, //6
	0b00000111, //7
	0b01111111, //8
	0b01101111  //9
};

/*
 * Print integer value to the seven-segment display
 */
void print(unsigned int value)
{
	// Extract and print a single target digit to the appropriate segment of the display
	for (int i = 0; i < TOTAL_DIGITS; i++)
	{
		// Disable all 7seg display cathodes
		PORT_CC &= ~((1 << PIN3) | (1 << PIN2) | (1 << PIN1) | (1 << PIN0));
		
		// Remove zeros before digit
// 		if (i > 0 && value == 0) {
// 			continue;
// 		}

		// Set port 7SEG state to display unit
		PORT_7SEG = digits[value % 10];
		// Enable common cathode
		PORT_CC |= (1 << i);
		// Cut unit from initial digit before next iteration (e.g. number 2021 turns to 202, number 202 to 20 etc.)
		value /= 10;
		_delay_ms(5);
	}
}

int main(void)
{
	// Configure data direction for pins 0-7 (port 7SEG) as OUTPUT
	DDR_7SEG |= (1 << PIN0) | (1 << PIN1) | (1 << PIN2) | (1 << PIN3) | (1 << PIN4) | (1 << PIN5) | (1 << PIN6) | (1 << PIN7);
	// Configure data direction for pins 0-3 (port CC) as OUTPUT
	DDR_CC |= (1 << PIN0) | (1 << PIN1) | (1 << PIN2) | (1 << PIN3);
	
	while (1) 
	{
		print(value);
	}
}
