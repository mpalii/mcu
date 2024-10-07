/*
 * Created: 31.10.2021 00:51:29
 * Author : Maksym Palii
 */ 

// LED port
#define DDR_LED			(DDRD)
#define PORT_LED		(PORTD)
#define PIN_LED			(0)
#define MAX_ITERATIONS	(10)

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t counter = 0;

/*
 * Timer/Counter1 output compare a match interrupt handler function
 */
ISR(TIMER1_COMPA_vect)
{
	if (counter == MAX_ITERATIONS) 
	{
		counter = 0;
		// Toggle led
		PORT_LED ^= (1 << PIN_LED);
	}
	counter++;
}

int main(void)
{
	// Configure data direction for pin led (port LED) as OUTPUT
	DDR_LED |= (1 << PIN_LED);
	// Set pin led (port LED) driven low (zero)
	PORT_LED &= ~(1 << PIN_LED);
	// Enable 16-bit Timer/Counter1; CLK/8 (from prescaler)
	TCCR1B |= (1 << CS11);
	// Set Output Compare Register 1A value
	OCR1A = 12499;
	// Enable Clear Timer on Compare (CTC) mode
	TCCR1B |= (1 << WGM12);
	// Enable 16-bit Timer/Counter1 output compare a match interrupt
	TIMSK |= (1 << OCIE1A);
	// Enable global interrupts
	sei();	
	
	while (1) 
	{
		// No logic
	}
}
