/*
 * SmartOutletAC.c
 *
 * Created: 11/03/2023 20:15:58
 * Author : Maksym_Palii
 */

 #define F_CPU 18432000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "uart328p.h"

void init_io_pins(void);
void init_tasks(void);
void init_timer_0(void);

// Task 1
#define T1 15
void task_1(void);
volatile uint8_t time1;

ISR(USART_RX_vect)
{
	UART_receive();
}

ISR(USART_TX_vect)
{
	UART_transmit();
}

ISR (TIMER0_COMPA_vect)
{
	if (time1 > 0) --time1;
}


int main(void)
{
	init_io_pins();
	init_tasks();
	init_timer_0();
	UART_init(F_CPU, 9600, false);
	sei();
	
	UART_transmit_data("Start up...\r\n");
	
	while (true)
	{
		if (time1 == 0) task_1();
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
/* Set up timer 0 for 1 mSec timebase                                       */
/* (256 (prescaler) * 72 (OCR0A + 1)) / 18_432_000 MHz = 0.001Sec = 1mSec   */
/****************************************************************************/
void init_timer_0(void)
{
	// TCCR0A – Timer/Counter0 Control Register channel A
	TCCR0A = _BV(WGM01);             // Clear Timer on Compare Match (CTC) mode (only works with channel)
	
	// TCCR0B – Timer/Counter0 Control Register channel B
	TCCR0B = _BV(CS02);  // clk/256 (From prescaler)
	
	// OCR0A – Timer/Counter0 Output Compare Register channel A
	OCR0A =	71;                     //set the compare reg to 72 time ticks (zero based)
	
	// TIMSK0 – Timer/Counter0 Interrupt Mask Register
	TIMSK0 = _BV(OCIE0A);            // Timer/Counter0 Output Compare Match channel A Interrupt Enable
}

/****************************************************************************/
/* Tasks implementation section                                             */
/****************************************************************************/
void task_1(void)
{
	// re-initialize task 4 timer
	time1 = T1;
	// UART income handling
	int8_t* income_command = UART_receive_data();
	if (income_command != NULL)
	{
		if (strcmp(income_command, "_EN") == 0)
		{
			PORTB |= _BV(PORTB1);
			UART_transmit_data("OK\r\n");
		}
		else if (strcmp(income_command, "_DIS") == 0)
		{
			PORTB &= ~_BV(PORTB1);
			UART_transmit_data("OK\r\n");
		}
		else
		{
			UART_transmit_data("UNKNOWN\r\n");
		}
	}
}