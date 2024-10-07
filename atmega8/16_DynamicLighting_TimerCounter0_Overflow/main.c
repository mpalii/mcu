/*
 * Created: 01.11.2021 20:43:23
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
#define TOTAL_DIGITS (4)

// 7SEG data port
#define DDR_7SEG	(DDRD)
#define PORT_7SEG	(PORTD)

// 7SEG common cathode port
#define DDR_CC		(DDRC)
#define PORT_CC		(PORTC)

#include <avr/io.h>
#include <avr/interrupt.h>

// Value to print
unsigned int value = 4321;

// Seven segment display digit index
unsigned char digit_index = 0;

/*
 * The DIGITS array stores values for displaying the digits 0-9 to a seven-segment display.
 *
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
 * Utility method to extract single decimal digit from initial value (starts from 0, see digit_index)
 */
unsigned char extract_digit(unsigned int initial_digit, unsigned char digit_position)
{
	for (int i = 0; i < digit_position; i++)
	{
		initial_digit /= 10;
	}
	
	return initial_digit % 10;
}

/*
 * Timer/Counter0 overflow interrupt handler function
 */
ISR(TIMER0_OVF_vect)
{
	if (digit_index >= TOTAL_DIGITS) 
	{
		digit_index = 0;
	}
	unsigned char extracted_digit = extract_digit(value, digit_index);
	// Disable all 7seg display cathodes
	PORT_CC |= (1 << PIN3) | (1 << PIN2) | (1 << PIN1) | (1 << PIN0);
	// Set port 7SEG state to display single digit
	PORT_7SEG = digits[extracted_digit];
	// Enable common cathode
	PORT_CC &= ~(1 << digit_index);
	digit_index++;
}

int main(void)
{
	// Configure data direction for pins 0-7 (port 7SEG) as OUTPUT
	DDR_7SEG |= (1 << PIN0) | (1 << PIN1) | (1 << PIN2) | (1 << PIN3) | (1 << PIN4) | (1 << PIN5) | (1 << PIN6) | (1 << PIN7);
	// Configure data direction for pins 0-3 (port CC) as OUTPUT
	DDR_CC |= (1 << PIN0) | (1 << PIN1) | (1 << PIN2) | (1 << PIN3);
	
	// Enable 8-bit	Timer/Counter0; CLK/8 (from prescaler)
	TCCR0 |= (1 << CS01);
	// Enable 8-bit Timer/Counter0 overflow interrupt
	TIMSK |= (1 << TOIE0);
	// Enable global interrupts
	sei();
	
	while (1) 
	{
		// No logic
	}
}
