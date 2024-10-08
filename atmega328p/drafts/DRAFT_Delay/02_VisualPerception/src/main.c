/**
 * @author Maksym Palii (maksympalii.dev@gmail.com)
 * @brief Visual perception
 * @version 0.1
 * @date 2022-10-23
 */

#define F_CPU (8000000UL/8)
#define half_period_for_frequency(FR) (F_CPU/(2.0 * FR))

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

int main(void)
{
    // Configure data direction for pins 0 (port D) as OUTPUT
    DDRD |= _BV(PIND0);

    // Set pin 0 (port D) driven high (one)
    PORTD |= _BV(PIND0);

    // Half-period
    //const double HALF_PERIOD = half_period_for_frequency(1);
    //const double HALF_PERIOD = half_period_for_frequency(24);
    //const double HALF_PERIOD = half_period_for_frequency(50);
    const double HALF_PERIOD = half_period_for_frequency(240);

    while (true) 
    {
        _delay_us(HALF_PERIOD);
        PORTD ^= _BV(PIND0);    // toggle pin
    }
}
