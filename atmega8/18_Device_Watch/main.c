/*
 * Created: 13.11.2021 07:57:55
 * Author : Maksym Palii
 */ 

// TODO need refactoring and external device control (button to choose time)

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
 #define PORT_CC	(PORTC)

 #define DISPLAY_DELAY (2)

 #define F_CPU 1000000UL

////////////////////////////////////////////////////////////////

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

////////////////////////////////////////////////////////////////

uint64_t current_time_in_ms = 60300000;
uint64_t ms_per_day = 86400000;

// Total period: (1/1000000) * 8 * (1 + 124) = 0.001000s.
ISR(TIMER2_COMP_vect)
{
	if (current_time_in_ms >= ms_per_day) {
		current_time_in_ms = 0;
	}
	current_time_in_ms++;
}

////////////////////////////////////////////////////////////////

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
 * Render time
 */
void render(uint32_t current_time_in_seconds)
{
	uint16_t current_time_in_minutes = current_time_in_seconds / 60;
	// Extract and print a single target digit to the appropriate segment of the display
	for (int i = 0; i < TOTAL_DIGITS; i++)
	{
		// Disable all 7seg display cathodes
		PORT_CC |= (1 << PIN3) | (1 << PIN2) | (1 << PIN1) | (1 << PIN0);
		uint8_t value = 0;
		switch (i)
		{
			case 0 : value = (current_time_in_minutes % 60) % 10; break;
			case 1 : value = (current_time_in_minutes % 60) / 10; break;
			case 2 : value = (current_time_in_minutes / 60) % 10; break;
			case 3 : value = (current_time_in_minutes / 60) / 10; break;
		}
		// Set port 7SEG state to display unit
		PORT_7SEG = digits[value];
		if (i == 2 && current_time_in_seconds % 2 != 0)
		{
			PORT_7SEG |= 0b10000000;
		}
		// Enable common cathode
		PORT_CC &= ~(1 << i);
		_delay_ms(DISPLAY_DELAY);
	}
}

int main(void)
{
	// Configure data direction for pins 0-7 (port 7SEG) as OUTPUT
	DDR_7SEG |= (1 << PIN0) | (1 << PIN1) | (1 << PIN2) | (1 << PIN3) | (1 << PIN4) | (1 << PIN5) | (1 << PIN6) | (1 << PIN7);
	// Configure data direction for pins 0-3 (port CC) as OUTPUT
	DDR_CC |= (1 << PIN0) | (1 << PIN1) | (1 << PIN2) | (1 << PIN3);
	
	// Enable 8-bit Timer/Counter2; CLK/8 (from prescaler)
	TCCR2 |= (1 << CS21);
	// Set Output Compare Register OCR2 value
	OCR2 = 124;
	// Enable Clear Timer on Compare (CTC) mode
	TCCR2 |= (1 << WGM21);
	// Enable 8-bit Timer/Counter2 output compare a match interrupt
	TIMSK |= (1 << OCIE2);
	// Enable global interrupts
	sei();
	
	while (1)
	{
		uint32_t current_time_in_seconds = current_time_in_ms / 1000;
		render(current_time_in_seconds);
	}
}

