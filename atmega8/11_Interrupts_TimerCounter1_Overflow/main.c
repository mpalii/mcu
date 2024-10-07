/*
 * Created: 31.10.2021 00:17:51
 * Author : Maksym Palii
 */ 

// LED port
#define DDR_LED		(DDRD)
#define PORT_LED	(PORTD)
#define PIN_LED		(0)

#include <avr/io.h>
#include <avr/interrupt.h>

/*
 * Timer/Counter1 overflow interrupt handler function
 */
ISR(TIMER1_OVF_vect)
{
	// Toggle led
	PORT_LED ^= (1 << PIN_LED);
}

int main(void)
{
	// Configure data direction for pin led (port LED) as OUTPUT
	DDR_LED |= (1 << PIN_LED);
	// Set pin led (port LED) driven low (zero)
	PORT_LED &= ~(1 << PIN_LED);
	// Enable 16-bit Timer/Counter1; CLK/64 (from prescaler)
	TCCR1B |= (1 << CS11) | (1 << CS10);
	// Enable 16-bit Timer/Counter1 overflow interrupt
	TIMSK |= (1 << TOIE1);
	// Enable global interrupts
	sei();	
	
	while (1) 
	{
		// No logic
	}
}
