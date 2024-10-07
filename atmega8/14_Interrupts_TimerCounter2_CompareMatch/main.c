/*
 * Created: 31.10.2021 19:27:48
 * Author : Maksym Palii
 */ 

// LED port
#define DDR_LED			(DDRD)
#define PORT_LED		(PORTD)
#define PIN_LED			(0)
#define MAX_ITERATIONS	(250)

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint16_t counter = 0;

/*
 * Timer/Counter2 output compare a match interrupt handler function
 */
ISR(TIMER2_COMP_vect)
{
	if (counter == MAX_ITERATIONS) {
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
	// Enable 8-bit Timer/Counter2; CLK/8 (from prescaler)
	TCCR2 |= (1 << CS21);
	// Set Output Compare Register OCR2 value
	OCR2 = 249;
	// Enable Clear Timer on Compare (CTC) mode
	TCCR2 |= (1 << WGM21);
	// Enable 8-bit Timer/Counter2 output compare a match interrupt
	TIMSK |= (1 << OCIE2);
	// Enable global interrupts
	sei();	
	
	while (1) 
	{
		// No logic
	}
}
