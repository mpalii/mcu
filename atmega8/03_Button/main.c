/*
 * Created: 23.10.2021 14:14:23
 * Author : Maksym Palii
 */ 

// LED port
#define DDR_LED		(DDRB)
#define PORT_LED	(PORTB)

// BUTTON port
#define DDR_BUTTON	(DDRC)
#define PIN_BUTTON	(PINC)

#define PIN0		(0)
#define PIN1		(1)
#define PIN2		(2)
#define PIN3		(3)

#include <avr/io.h>

/*
 * This method checks the input signal on the target pin of the button port (PIN BUTTON)
 * and sets this value to the appropriate pin of the led port (PORT_LED)
 */
void update_led_state_for(unsigned char target_pin)
{
	if (PIN_BUTTON & (1 << target_pin))
	{
		PORT_LED |= (1 << target_pin);
	}
	else
	{
		PORT_LED &= ~(1 << target_pin);
	}
}

int main(void)
{
	// Configure data direction for pins 0-3 (port LED) as OUTPUT
	DDR_LED |= (1 << PIN0) | (1 << PIN1) | (1 << PIN2) | (1 << PIN3);
	// Configure data direction for pins 0-3 (port BUTTON) as INPUT
	DDR_BUTTON &= ~((1 << PIN0) | (1 << PIN1) | (1 << PIN2) | (1 << PIN3));

	while (1) 
	{
		update_led_state_for(PIN0);
		update_led_state_for(PIN1);
		update_led_state_for(PIN2);
		update_led_state_for(PIN3);
	}
}
