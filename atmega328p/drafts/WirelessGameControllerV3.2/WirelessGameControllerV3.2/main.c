/*
 * WirelessGameControllerV3.2.c
 *
 * Created: 28/02/2023 18:04:47
 * Author : Maksym_Palii
 */ 

#include <avr/io.h>


#define F_CPU 18432000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <util/delay.h>
#include "uart328p.h"

void handle_sensor(uint8_t port, uint8_t pin, bool *sensor_was_triggered, int high_code, int low_code);
void initialize(void);

bool sensor_1_was_triggered = false;
bool sensor_2_was_triggered = false;

//**********************************************************
// Task 1
#define t1 40
void task1(void);
volatile uint8_t time1;
uint8_t state = 1;

//**********************************************************
//timer 0 compare ISR
ISR(TIMER0_COMPA_vect)
{      
  //Decrement buttons handler task timer if it is not already zero
  if (time1 > 0) --time1;
}

int main(void)
{
	initialize();
	sei();
	
    while (true) 
    {
		if (time1 == 0) task1();
    }
}

void task1(void)
{
	// re-initialize timer 1
	time1 = t1;
	
	if (state == 1)
	{
		// send 10 us pulse to trigger pin
		PORTB &= ~_BV(PORTB1);  // set low
		_delay_us(2);
		PORTB |= _BV(PORTB1);   // set high
		_delay_us(10);
		PORTB &= ~_BV(PORTB1);  // set low
		
		while ((PINB & _BV(PINB2)) == 0);
		_delay_us(2000);
		handle_sensor(PINB, PINB2, &sensor_1_was_triggered, 1, 5);	// left top
		
		state = 0;
	}
	else
	{
		// send 10 us pulse to trigger pin
		PORTD &= ~_BV(PORTD6);  // set low
		_delay_us(2);
		PORTD |= _BV(PORTD6);   // set high
		_delay_us(10);
		PORTD &= ~_BV(PORTD6);  // set low
		
		while ((PIND & _BV(PIND7)) == 0);
		_delay_us(2000);
		handle_sensor(PIND, PIND7, &sensor_2_was_triggered, 3, 7);	// right top
		
		state = 1;
	}
}


void handle_sensor(uint8_t port, uint8_t pin, bool *sensor_was_triggered, int high_code, int low_code)
{
	// check whether button was pressed
	if ((~port & _BV(pin)) && !*sensor_was_triggered)
	{
		*sensor_was_triggered = true;
		printf("<01%d;", high_code);
	}

	// check whether button was released
	if ((port & _BV(pin)) && *sensor_was_triggered)
	{
		*sensor_was_triggered = false;
		printf("<01%d;", low_code);
	}
}

void initialize()
{
	// init port
	DDRB |= (1 << DDB1);		// set trigger pin as output
	DDRD |= (1 << DDD6);		// set trigger pin as output
	DDRB &= ~(1 << DDB2);		// set echo pin as input
	DDRD &= ~(1 << DDD7);		// set echo pin as input
	
	//set up timer 0 for 1 mSec timebase
	TCCR0A= (1<<WGM01);				// turn on clear-on-match
	TCCR0B= (1<<CS02);				// set pre-scaler to divide by 256
	OCR0A =	71;  					// set the compare reg to 72 time ticks (include zero)
	TIMSK0= (1<<OCIE0A);			// turn on timer 0 cmp match ISR
	
	stdin = stdout = stderr = UART_init(F_CPU, 9600, false);
}
