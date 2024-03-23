/**
 * @author Maksym Palii
 * @brief External interrupts, interrupts priority
 * @version 1.0
 * @date 2024 February 26
 */

#define F_CPU (8000000UL)

#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/delay.h>
#include "drivers/gpio.h"

ISR (INT0_vect)
{    
    GPIO_HIGH(LED_INT0);
    _delay_ms(2000);
    GPIO_LOW(LED_INT0);
}

ISR (INT1_vect)
{
    GPIO_HIGH(LED_INT1);
    _delay_ms(2000);
    GPIO_LOW(LED_INT1);
}

int main(void)
{
    gpio_init();

    EICRA |= _BV(ISC11) | _BV(ISC01);
    EIMSK |= _BV(INT1) | _BV(INT0);

    sei();
	
    while (true)
    {
        // NOP
    }
}
