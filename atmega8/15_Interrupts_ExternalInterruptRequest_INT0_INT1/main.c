/*
 * Created: 31.10.2021 21:03:52
 * Author : Maksym Palii
 */ 

// 7SEG port
#define DDR_7SEG	(DDRB)
#define PORT_7SEG	(PORTB)

// PINs
#define PIN0		(0)
#define PIN1		(1)
#define PIN2		(2)
#define PIN3		(3)
#define PIN4		(4)
#define PIN5		(5)
#define PIN6		(6)
#define PIN7		(7)

#include <avr/io.h>
#include <avr/interrupt.h>

/*
 * The DIGITS array stores values for displaying the digits 0-F to a seven-segment display.
 
 * The index of the array element is equivalent to a digit in hexadecimal form,
 * each array element stores the state of the seven-segment port for this digit. 
 */
unsigned char DIGITS[] = {
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

unsigned char counter = 0;

/*
 * Increment button interrupt handler function
 */
ISR(INT0_vect)
{
	if (counter < 0xF) counter++;
}

/*
 * Decrement button interrupt handler function
 */
ISR(INT1_vect)
{
	if (counter > 0) counter--;
}

int main(void)
{
	// Configure data direction for pins 0-7 (port 7SEG) as OUTPUT
	DDR_7SEG |= (1 << PIN0) | (1 << PIN1) | (1 << PIN2) | (1 << PIN3) | (1 << PIN4) | (1 << PIN5) | (1 << PIN6) | (1 << PIN7);
	// The rising edge of INT1 generates an interrupt request
	MCUCR |= (1 << ISC11) | (1 << ISC10);
	// The rising edge of INT0 generates an interrupt request
	MCUCR |= (1 << ISC01) | (1 << ISC00);
	// Enable external interrupt INT1 and INT2
	GICR |= (1 << INT1) | (1 << INT0);
	// Enables global interrupts
	sei();
	
	while (1) 
	{
		// Set port 7SEG state to display counter value
		PORT_7SEG = DIGITS[counter];
	}
}
