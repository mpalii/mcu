/*
 * Created: 06.11.2021 11:48:41
 * Author : Maksym Palii
 */ 

#include <avr/interrupt.h>
#include "seven-segment-display/cc.h"

// Value to print
uint16_t value = 1990;

/*
 * Timer/Counter0 overflow interrupt handler function
 */
ISR(TIMER0_OVF_vect)
{
	print7SEG(value);
}

int main(void)
{
	init7SEG();
	
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
