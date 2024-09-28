#ifndef UART_H_
#define UART_H_

#include <stdio.h>

static FILE uart_stream;

static int uart_transmit(char data, FILE* stream)
{
    // Wait for empty transmit buffer
    loop_until_bit_is_set(UCSR0A, UDRE0);
    // Put data into buffer, sends the data
    UDR0 = data;
 
    return 0;
}

static int uart_receive(FILE* stream)
{
    // Wait for data to be received
    loop_until_bit_is_set(UCSR0A, RXC0);
    // Get and return received data from buffer
    return UDR0;
}

static void init_frame_format()
{
    /************************************************************************/
    /* Default frame format:                                                */
    /* 1 start bit, 8 data bits, no parity bit, 1 stop bit                  */
    /************************************************************************/
}

void init_uart(uint32_t f_cpu, uint16_t baud_rate, bool double_speed_enabled)
{
    // Baud rate calculation ratio
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
 
    // Initialize UART-related IO stream
    fdev_setup_stream(&uart_stream, uart_transmit, uart_receive, _FDEV_SETUP_RW);

    // assign standard IO streams with UART channel 
    stdin = stdout = stderr = &uart_stream;
}

#endif /* UART_H_ */