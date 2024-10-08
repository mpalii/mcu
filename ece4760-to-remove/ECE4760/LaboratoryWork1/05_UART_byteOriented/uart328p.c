/*
 * uart328p.c
 *
 * Created: 12/02/2023 12:03:54
 *  Author: Maksym Palii
 */ 

#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include "uart328p.h"

void init_frame_format()
{
    /************************************************************************/
    /* Default frame format:                                                */
    /* 1 start bit, 8 data bits, no parity bit, 1 stop bit                  */
    /************************************************************************/
}

void UART_init(uint32_t f_cpu, uint32_t baud_rate, bool double_speed_enabled)
{
    // TODO add description
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
	
    init_frame_format();
}

void UART_transmit(int8_t data)
{
    // Wait for empty transmit buffer
    loop_until_bit_is_set(UCSR0A, UDRE0);
    // Put data into buffer, sends the data
    UDR0 = data;
}

int8_t UART_receive(void)
{
    // Wait for data to be received
    loop_until_bit_is_set(UCSR0A, RXC0);
    // Get and return received data from buffer
    return UDR0;
}
