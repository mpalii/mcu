/*
 * Created: 23.10.2021 12:36:19
 * Author : Maksym Palii
 */ 

#include <avr/io.h>

int main(void)
{
	// Configure data direction for pins 0-6 (port B) as OUTPUT
	DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5) | (1 << DDB6);
	// Configure data direction for pins 0-5 (port C) as OUTPUT
	DDRC |= (1 << DDC0) | (1 << DDC1) | (1 << DDC2) | (1 << DDC3) | (1 << DDC4) | (1 << DDC5);
	// Configure data direction for pins 0-7 (port D) as OUTPUT
	DDRD |= (1 << DDD0) | (1 << DDD1) | (1 << DDD2) | (1 << DDD3) | (1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7);
		
	// Set pins 0-6 (port B) driven high (one)
	PORTB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3) | (1 << PB4) | (1 << PB5) | (1 << PB6);
	// Set pins 0-5 (port C) driven low (zero)
	PORTC &= ~((1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3) | (1 << PC4) | (1 << PC5));
	// Set pins 0-7 (port D) driven high (one)
	PORTD |= (1 << PD0) | (1 << PD1) | (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7);
	
	while (1) 
	{
		// No logic
	}
}
