/*
 * Delay example, visual perception
 *
 * Created: 21/01/2023 21:21:47
 * Author : Maksym Palii
 */ 

#define F_CPU 8000000UL
#define half_period_for(frequency) (1000000 / (2.0 * frequency))	// us (microsecond)

/* Test frequencies for researching */
//#define TEST_FREQUENCY     1	// 1Hz - just a period of one second
//#define TEST_FREQUENCY    24	// 24Hz - frame rate standard for 35 mm sound films
//#define TEST_FREQUENCY    50	// 50Hz - AC frequency standard (use camera of a smartphone to see blinking)
//#define TEST_FREQUENCY   240	// 240Hz - display matrix refresh rate
#define TEST_FREQUENCY 50000	// 50kHz - something really fast :)

#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

const double HALF_PERIOD = half_period_for(TEST_FREQUENCY);

void init_io_pins(void)
{
    // Configure data direction for pin 0 (port D) as OUTPUT
    DDRD |= _BV(DDD0);
}

int main(void)
{
    init_io_pins();
	
    while (true) 
    {
        PORTD ^= _BV(PORTD0);
        _delay_us(HALF_PERIOD);
    }
}
