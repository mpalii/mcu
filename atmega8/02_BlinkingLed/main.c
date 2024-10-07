/*
 * Created: 23.10.2021 14:00:45
 * Author : Maksym Palii
 */ 

#define F_CPU (1000000UL)
#define DELAY_PERIOD (500)

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// Configure data direction for pins 0-7 (port B) as OUTPUT
	DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5) | (1 << DDB6) | (1 << DDB7);
	
	while (1) 
	{
		PORTB |= (1 << PB0);			// Set pin 0 (port B) driven high (one)
		_delay_ms(DELAY_PERIOD);		// Delay
		PORTB &= ~(1 << PB0);			// Set pin 0 (port B) driven low (zero)
		
		PORTB |= (1 << PB1);			// Set pin 1 (port B) driven high (one)
		_delay_ms(DELAY_PERIOD);		// Delay
		PORTB &= ~(1 << PB1);			// Set pin 1 (port B) driven low (zero)
		
		PORTB |= (1 << PB2);			// Set pin 2 (port B) driven high (one)
		_delay_ms(DELAY_PERIOD);		// Delay
		PORTB &= ~(1 << PB2);			// Set pin 2 (port B) driven low (zero)
		
		PORTB |= (1 << PB3);			// Set pin 3 (port B) driven high (one)
		_delay_ms(DELAY_PERIOD);		// Delay
		PORTB &= ~(1 << PB3);			// Set pin 3 (port B) driven low (zero)
		
		PORTB |= (1 << PB4);			// Set pin 4 (port B) driven high (one)
		_delay_ms(DELAY_PERIOD);		// Delay
		PORTB &= ~(1 << PB4);			// Set pin 4 (port B) driven low (zero)
		
		PORTB |= (1 << PB5);			// Set pin 5 (port B) driven high (one)
		_delay_ms(DELAY_PERIOD);		// Delay
		PORTB &= ~(1 << PB5);			// Set pin 5 (port B) driven low (zero)
		
		PORTB |= (1 << PB6);			// Set pin 6 (port B) driven high (one)
		_delay_ms(DELAY_PERIOD);		// Delay
		PORTB &= ~(1 << PB6);			// Set pin 6 (port B) driven low (zero)
		
		PORTB |= (1 << PB7);			// Set pin 7 (port B) driven high (one)
		_delay_ms(DELAY_PERIOD);		// Delay
		PORTB &= ~(1 << PB7);			// Set pin 7 (port B) driven low (zero)
	}
}
