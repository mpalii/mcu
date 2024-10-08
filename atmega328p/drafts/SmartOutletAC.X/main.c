/* 
 * File:   main.c
 * Author: Maksym_Palii
 *
 * Created on 05 February 2023, 11:37
 */

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

void init_io_pins(void);
void init_tasks(void);
void init_timer_2(void);

// Task 1
#define T1 20
void task_1(void);
volatile uint8_t time1;

// Task 2
#define T2 1
void task_2(void);
volatile uint8_t time2;


bool ir_sensor_falling_edge = false;
bool ir_sensor_event_occured = false;

ISR (TIMER2_COMP_vect)
{
	if (time1 > 0) --time1;
	if (time2 > 0) --time2;
}

/*
 * 
 */
int main(int argc, char** argv) 
{
    init_io_pins();
    init_tasks();
    init_timer_2();
    sei();
    
    while(true) {
		if (time1 == 0) { task_1(); }
        if (time2 == 0) { task_2(); }
    }
}


void init_io_pins(void)
{
    // Set port B pin 1 as output
	DDRB |= _BV(DDB1);
}

void init_tasks(void)
{
	time1 = T1;
}

/****************************************************************************/
/* Set up timer 0 for 1 mSec timebase										*/
/* (64 (prescaler) * 125 (OCR2 + 1)) / 8_000_000 MHz = 0.001Sec = 1mSec	    */
/****************************************************************************/
void init_timer_2(void)
{	
	// TCCR2 ? Timer/Counter2 Control Register
    // Clear Timer on Compare Match (CTC) mode
    // clk/64 (From prescaler)
	TCCR2 = _BV(WGM21) | _BV(CS22);
	
	// OCR2 ? Timer/Counter2 Output Compare Register
    //set the compare register to 125 time ticks (zero based)
	OCR2 =	124;
	
	// TIMSK ? Timer/Counter Interrupt Mask Register
    // Timer/Counter2 Output Compare Match channel A Interrupt Enable
	TIMSK = _BV(OCIE2);
}

void task_1(void)
{
	// re-initialize task 1 timer
	time1 = T1;
	// IR sensor handling
	// check IR sensor
	if (bit_is_clear(PINB, PINB0) && !ir_sensor_falling_edge)
	{
		ir_sensor_falling_edge = true;
		// button push handling
        ir_sensor_event_occured = true;
	}
	
	// check whether button was released
	if (bit_is_set(PINB, PINB0) && ir_sensor_falling_edge)
	{
		ir_sensor_falling_edge = false;
		// NOP on button release
	}
}

void task_2(void)
{
	// re-initialize task 2 timer
	time2 = T2;
    if (ir_sensor_event_occured)
    {
        // Toggle pin 1 port B
        PORTB ^= _BV(PORTB1);
        // reset ir event flag
        ir_sensor_event_occured = false;
    }
}
