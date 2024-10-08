/*
 * WirelessGameController
 *
 * Created: 23/12/2022 19:43:20
 * Author : Maksym_Palii
 */ 

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stddef.h>
#include "uart328p.h"

bool button_was_pressed(uint8_t port, uint8_t pin, bool *button_was_pressed);
void initialize(void);

bool button_1_was_pressed = false;
bool button_2_was_pressed = false;
bool button_3_was_pressed = false;
bool button_4_was_pressed = false;

//**********************************************************
// Task 1
#define t1 20
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
	PORTB |= 0b00001111;	
	
	//set up timer 0 for 1 mSec timebase
	TCCR0A= (1<<WGM01);				// turn on clear-on-match
	TCCR0B= (1<<CS02);				// set pre-scaler to divide by 256
	OCR0A =	71;  					// set the compare reg to 72 time ticks (include zero)
	TIMSK0= (1<<OCIE0A);			// turn on timer 0 cmp match ISR
	
	stdin = stdout = stderr = UART_init(18432000, 9600, false);
	
	sei();
	
	printf("Start up...\n\r");
	
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
	uint8_t btn1 = button_was_pressed(port_state, PINB0, &button_1_was_pressed) ? 1 : 0;
	uint8_t btn2 = button_was_pressed(port_state, PINB1, &button_2_was_pressed) ? 1 : 0;
	uint8_t btn3 = button_was_pressed(port_state, PINB2, &button_3_was_pressed) ? 1 : 0;
	uint8_t btn4 = button_was_pressed(port_state, PINB3, &button_4_was_pressed) ? 1 : 0;
	
	if (btn1 != 0 || btn2 != 0 || btn3 != 0 || btn4 != 0) 
	{
		printf("%d%d%d%d\n", btn1, btn2, btn3, btn4);	
	}
}

bool button_was_pressed(uint8_t port, uint8_t pin, bool *button_was_pressed)
{
	// check whether button was pressed
	if ((~port & _BV(pin)) && !*button_was_pressed)
	{
		*button_was_pressed = true;
		return true;
	}

	// check whether button was released
	if ((port & _BV(pin)) && *button_was_pressed)
	{
		*button_was_pressed = false;
	}
	return false;
}



