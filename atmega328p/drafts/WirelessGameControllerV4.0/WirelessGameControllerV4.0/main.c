/*
 * WirelessGameControllerV4.0.c
 *
 * Created: 24/03/2023 23:33:38
 * Author : Maksym_Palii
 */ 

#define F_CPU 18432000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>
#include "uart328p.h"

void generate_ultrasonic_impulse(volatile unsigned char* trigger_port, uint8_t trigger_pin, volatile unsigned char* echo_port, uint8_t echo_pin);
void handle_sensor(uint8_t port, uint8_t pin, bool *sensor_was_triggered, char *high_code, char *low_code);
void initialize(void);


enum EUltrasonicSensor{TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};
enum EUltrasonicSensor current_sensor = TOP_LEFT;

bool sensor_1_was_triggered = false;
bool sensor_2_was_triggered = false;
bool sensor_3_was_triggered = false;
bool sensor_4_was_triggered = false;

//**********************************************************
// Task 1
#define t1 25		// 40(38) - regular delay; 30 - works fine
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
	
    while (true) 
    {
		if (time1 == 0) task1();
    }
}

void task1(void)
{
	// re-initialize timer 1
	time1 = t1;
	
	if (current_sensor == BOTTOM_RIGHT)
	{
		generate_ultrasonic_impulse(&PORTB, PORTB1, &PINB, PINB2);
		handle_sensor(PINB, PINB2, &sensor_1_was_triggered, "<014;", "<018;");
		current_sensor = BOTTOM_LEFT;
		return;
	}
	
	if (current_sensor == BOTTOM_LEFT)
	{		
		generate_ultrasonic_impulse(&PORTD, PORTD6, &PIND, PIND7);
		handle_sensor(PIND, PIND7, &sensor_2_was_triggered, "<012;", "<016;");
		current_sensor = TOP_LEFT;
		return;
	}
	
	if (current_sensor == TOP_LEFT)
	{
		generate_ultrasonic_impulse(&PORTD, PORTD3, &PIND, PIND4);
		handle_sensor(PIND, PIND4, &sensor_3_was_triggered, "<011;", "<015;");
		current_sensor = TOP_RIGHT;
		return;
	}
	
	if (current_sensor == TOP_RIGHT)
	{		
		generate_ultrasonic_impulse(&PORTC, PORTC0, &PINC, PINC1);
		handle_sensor(PINC, PINC1, &sensor_4_was_triggered, "<013;", "<017;");
		current_sensor = BOTTOM_RIGHT;
		return;
	}
}


void generate_ultrasonic_impulse(volatile unsigned char* trigger_port, uint8_t trigger_pin, volatile unsigned char* echo_port, uint8_t echo_pin)
{
	// send 10 us pulse to trigger pin
	*trigger_port &= ~_BV(trigger_pin);  // set low
	_delay_us(2);
	*trigger_port |= _BV(trigger_pin);   // set high
	_delay_us(10);
	*trigger_port &= ~_BV(trigger_pin);  // set low
	
	loop_until_bit_is_set(*echo_port, echo_pin);	// AKA "while ((*echo_port & _BV(echo_pin)) == 0);"
	//while ((*echo_port & _BV(echo_pin)) == 0);
	//while(bit_is_clear(*echo_port, echo_pin));				// works fine
	_delay_us(2000);
}

void handle_sensor(uint8_t port, uint8_t pin, bool *sensor_was_triggered, char *high_code, char *low_code)
{
	// check whether button was pressed
	if ((~port & _BV(pin)) && !*sensor_was_triggered)
	{
		*sensor_was_triggered = true;
		UART_transmit(high_code);
	}

	// check whether button was released
	if ((port & _BV(pin)) && *sensor_was_triggered)
	{
		*sensor_was_triggered = false;
		UART_transmit(low_code);
    }
}

void initialize()
{
	// delay for stabilization
	_delay_ms(1000);
	
	// init port
	DDRB |= (1 << DDB1);		// set trigger pin as output
	DDRD |= (1 << DDD6);		// set trigger pin as output
	DDRD |= (1 << DDD3);		// set trigger pin as output
	DDRC |= (1 << DDC0);
	
	
	DDRB &= ~(1 << DDB2);		// set echo pin as input
	DDRD &= ~(1 << DDD7);		// set echo pin as input
	DDRD &= ~(1 << DDD4);		// set echo pin as input
	DDRC &= ~(1 << DDC1);
	
	//set up timer 0 for 1 mSec timebase
	TCCR0A= (1<<WGM01);				// turn on clear-on-match
	TCCR0B= (1<<CS02);				// set pre-scaler to divide by 256
	OCR0A =	71;  					// set the compare reg to 72 time ticks (include zero)
	TIMSK0= (1<<OCIE0A);			// turn on timer 0 cmp match ISR
	
	UART_init(F_CPU, 9600, false);
}
