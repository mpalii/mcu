/*
 * WirelessGameController v2
 *
 * Created: 23/12/2022 19:43:20
 * Author : Maksym_Palii
 */ 

#define F_CPU 18432000UL

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stddef.h>
#include <util/delay.h>
#include "uart328p.h"

void handle_button(uint8_t port, uint8_t pin, bool *button_was_pressed, int high_code, int low_code);
void initialize(void);

bool button_1_was_pressed = false;
bool button_2_was_pressed = false;
bool button_3_was_pressed = false;
bool button_4_was_pressed = false;

//**********************************************************
// Task 1
#define t1 12
void task1(void);
volatile uint8_t time1;

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
	
	//printf("Start up...\n\r");
	//_delay_ms(4000);
	//printf("<00d;");
	
    while (true) 
    {
		if (time1 == 0) task1();
    }
}

void task1(void)
{
	// re-initialize timer 1
	time1 = t1;
	uint8_t port_state = PINB;
	handle_button(port_state, PINB1, &button_1_was_pressed, 1, 5);	// left top
	handle_button(port_state, PINB2, &button_2_was_pressed, 2, 6);	// left bottom
	handle_button(port_state, PINB4, &button_3_was_pressed, 3, 7);	// right top
	handle_button(port_state, PINB3, &button_4_was_pressed, 4, 8);	// right bottom
}

void handle_button(uint8_t port, uint8_t pin, bool *button_was_pressed, int high_code, int low_code)
{
	// check whether button was pressed
	if ((~port & _BV(pin)) && !*button_was_pressed)
	{
		*button_was_pressed = true;
		printf("<01%d;", high_code);	
	}

	// check whether button was released
	if ((port & _BV(pin)) && *button_was_pressed)
	{
		*button_was_pressed = false;
		printf("<01%d;", low_code);
	}
}

void initialize() 
{
	
	PORTB |= 0b00011110;
	
	//set up timer 0 for 1 mSec timebase
	TCCR0A= (1<<WGM01);				// turn on clear-on-match
	TCCR0B= (1<<CS02);				// set pre-scaler to divide by 256
	OCR0A =	71;  					// set the compare reg to 72 time ticks (include zero)
	TIMSK0= (1<<OCIE0A);			// turn on timer 0 cmp match ISR
	
	stdin = stdout = stderr = UART_init(F_CPU, 9600, false);
}

