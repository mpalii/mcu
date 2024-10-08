/*
 * WirelessGameControllerV3.c
 *
 * Created: 25/02/2023 15:24:01
 * Author : Maksym_Palii
 */

#define F_CPU 18432000UL
#define TRIGGER_PIN PB1
#define ECHO_PIN PB2

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdio.h>
#include "uart328p.h"

int main(void) {
	UART_init(F_CPU, 9600, false);
	//UART_transmit_array("Start up...\r\n");
	char message[22];
	
	// measure duration of echo pulse
	uint16_t pulse_width = 0;
	
	DDRB |= (1 << TRIGGER_PIN);  // set trigger pin as output
	DDRB &= ~(1 << ECHO_PIN);    // set echo pin as input
	
	
	while (true) {
		// send 10 us pulse to trigger pin
		PORTB &= ~(1 << TRIGGER_PIN);  // set low
		_delay_us(2);
		PORTB |= (1 << TRIGGER_PIN);   // set high
		_delay_us(10);
		PORTB &= ~(1 << TRIGGER_PIN);  // set low
		
		
		while ((PINB & (1 << ECHO_PIN)) == 0);  // wait for echo pulse to start
		while ((PINB & (1 << ECHO_PIN)) != 0) {  // measure pulse width
			pulse_width++;
			_delay_us(1);
		}
		
		// calculate distance in cm
		uint16_t distance = pulse_width / 44;  // 44 fine for Proteus 58 ratio
		
		// do something with distance data
		// for example, print it to serial monitor
		
		sprintf(message, "%ucm - ", distance);
		UART_transmit_array(message);
		sprintf(message, "%uus\r\n", pulse_width);
		UART_transmit_array(message);
		
		pulse_width = 0;
		
		_delay_ms(40);  // wait for 1 second
	}
	
	return 0;
}