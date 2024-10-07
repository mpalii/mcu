/*
 * Created: 31.10.2021 00:39:27
 * Author : Maksym Palii
 */ 

// LED port
#define DDR_LED		(DDRD)
#define PORT_LED	(PORTD)
#define PIN_LED		(0)

#include <avr/io.h>
#include <avr/interrupt.h>

/*
 * Timer/Counter2 overflow interrupt handler function
 */
ISR(TIMER2_OVF_vect)
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
	// Enable 8-bit Timer/Counter2; CLK/1024 (from prescaler)
	TCCR2 |= (1 << CS22) | (1 << CS21) | (1 << CS20);
	// Enable 8-bit Timer/Counter2 overflow interrupt
	TIMSK |= (1 << TOIE2);
	// Enable global interrupts
	sei();	
	
	while (1) 
	{
		// No logic
	}
}
