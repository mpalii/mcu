/*
 * Created: 30.10.2021 00:32:54
 * Author : Maksym Palii
 */ 

// LED port
#define DDR_LED		(DDRD)
#define PORT_LED	(PORTD)
#define PIN_LED		(0)

#include <avr/io.h>
#include <avr/interrupt.h>

/*
 * Timer/Counter0 overflow interrupt handler function
 */
ISR(TIMER0_OVF_vect)
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
	// Enable 8-bit	Timer/Counter0; CLK/1024 (from prescaler)
	TCCR0 |= (1 << CS02) | (1 << CS00);
	// Enable 8-bit Timer/Counter0 overflow interrupt
	TIMSK |= (1 << TOIE0);
	// Enable global interrupts
	sei();
	
	while (1) 
	{
		// No logic
	}
}
