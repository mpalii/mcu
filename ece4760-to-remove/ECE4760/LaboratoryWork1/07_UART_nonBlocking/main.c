/*
 * 07_UART_nonBlocking.c
 *
 * Created: 12/02/2023 17:44:44
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
#define T1 250
void task_1(void);
volatile uint8_t time1;

// Task 2
#define T2 100
void task_2(void);
volatile uint8_t time2;

// Task 3
#define T3 20
void task_3(void);
volatile uint8_t time3;

// Task 4
#define T4 15
void task_4(void);
volatile uint8_t time4;

bool double_speed_enabled = false;

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
	if (time2 > 0) --time2;
	if (time3 > 0) --time3;
	if (time4 > 0) --time4;
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
		if (time2 == 0) task_2();
		if (time3 == 0) task_3();
		if (time4 == 0) task_4();
	}
}

void init_io_pins(void)
{
	// Set port B pin 1, 2 and 3 as output
	DDRB |= _BV(DDB1) | _BV(DDB2) | _BV(DDB3);
}

void init_tasks(void)
{
	time1 = T1;
	time2 = T2;
	time3 = T3;
	time4 = T4;
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
	// re-initialize task 1 timer
	time1 = T1;
	// Toggle pin 0 port D
	PORTB ^= _BV(PORTB1);
}

void task_2(void)
{
	// re-initialize task 2 timer
	time2 = T2;
	// Toggle pin 1 port D
	PORTB ^= _BV(PORTB2);
}

void task_3(void)
{
	// re-initialize task 3 timer
	time3 = double_speed_enabled ? (T3 / 2) : T3;
	// Toggle pin 2 port D
	PORTB ^= _BV(PORTB3);
}

void task_4(void)
{
	// re-initialize task 4 timer
	time4 = T4;
	// UART income handling
	int8_t* income_command = UART_receive_data();
	if (income_command != NULL)
	{
		if (strcmp(income_command, "2Xen") == 0)
		{
			double_speed_enabled = true;
			UART_transmit_data("OK\r\n");
		} 
		else if (strcmp(income_command, "2Xdis") == 0)
		{
			double_speed_enabled = false;
			UART_transmit_data("OK\r\n");
		}
		else 
		{
			UART_transmit_data("UNKNOWN\r\n");
		}
	}
}


	/*
    while (true) 
    {
		int8_t* income = UART_receive_data();
		if (income != NULL)
		{
			UART_transmit_data(income);
		}
    }
	*/