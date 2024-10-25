#if !defined(F_CPU)
/* terminate compilation if not specified */
# error "F_CPU must be specified for \"uart.h\""
#endif

#if !defined(BAUD_RATE)
/* terminate compilation if not specified */
# error "BAUD_RATE must be specified for \"uart.h\""
#endif

#ifdef U2X
    #define BAUD_RATE_RATIO 8UL
#else 
    #define BAUD_RATE_RATIO 16UL
#endif

#define BUFFER_SIZE     (9)

#include <stdbool.h>
#include <stdlib.h>
#include "gpio.h"

void uart_transmit(char* message);

// TX
static char* output_buffer = NULL;

/************************************************************************/
/* Default frame format:                                                */
/* 1 start bit, 8 data bits, no parity bit, 1 stop bit					*/
/************************************************************************/
void init_uart(void)
{
    // Set baud rate
    UBRR0 = F_CPU / (BAUD_RATE_RATIO * BAUD_RATE) - 1;

    #ifdef U2X
        UCSR0A |= _BV(U2X0);
    #endif
 
    // Enable receiving and transmission
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);

    uart_transmit("- UART ready\r\n");
}

/**
 * @warning blocking method, use only during initialization
 */
void uart_transmit(char* message)
{
    uint8_t i = 0;

    // Send characters until zero byte
    while (message[i] != '\0')
    {
        // Wait for empty transmit buffer
        loop_until_bit_is_set(UCSR0A, UDRE0);
    
        // Put data into buffer, sends the data
        UDR0 = message[i++];
    }
}

void uart_add_to_buffer(char* message)
{
    output_buffer = message;
}

void uart_write(void)
{
    if (output_buffer != NULL && bit_is_set(UCSR0A, UDRE0))
    {
        char data = *output_buffer;

        if (data == '\0')
        {
            output_buffer = NULL;
            return;
        }

        UDR0 = data;

        output_buffer++;
    }
}

char uart_read(void)
{
    return bit_is_set(UCSR0A, RXC0) ? UDR0 : 0;
}

void uart_enable_rx(void)
{
    UCSR0B |= _BV(RXEN0);
}

void uart_disable_rx(void)
{
    UCSR0B &= ~_BV(RXEN0);
}
