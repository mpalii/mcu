/*
 * L30-UART.c
 *
 * Created: 19/12/2022 17:18:03
 * Author : Maksym_Palii
 */ 

#define F_CPU 8000000UL

#include <util/delay.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>

void UART_transmit_byte(char data)
{
	// Wait for empty transmit buffer
	loop_until_bit_is_set(UCSR0A, UDRE0);
	// Put data into buffer, sends the data
	UDR0 = data;
}

void UART_transmit_string(char *str)
{
	uint8_t i = 0;
	while (str[i] != '\0')
	{
		UART_transmit_byte(str[i]);
		i++;
	}
}

void UART_init(uint32_t f_cpu, uint32_t baud_rate, bool double_speed_enabled)
{
	// TODO description
	uint32_t baud_rate_divider = 16;
	
	// Check double speed (U2X) mode
	if (double_speed_enabled)
	{
		UCSR0A = _BV(U2X0);
		baud_rate_divider /= 2;
	}
	
	// Set baud rate
	UBRR0 = f_cpu / (baud_rate_divider * baud_rate) - 1;
	
	// Enable receiving and transmission
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);
}

char *message = "ATmega328p UART test ";

int main(void)
{
	UART_init(F_CPU, 9600, false);
	
    while (true) 
    {
		UART_transmit_string(message);
		_delay_ms(500);
    }
}

