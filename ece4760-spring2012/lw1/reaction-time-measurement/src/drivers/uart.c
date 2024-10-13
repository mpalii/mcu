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

#include "gpio.h"

/**
 * Blocking call, only use during initialization (before SEI)
 */
void uart_transmit(char* array)
{
    uint8_t i = 0;

    // Send characters until zero byte
    while (array[i] != '\0')
    {
        // Wait for empty transmit buffer
        loop_until_bit_is_set(UCSR0A, UDRE0);
    
        // Put data into buffer, sends the data
        UDR0 = array[i++];
    }
}

/************************************************************************/
/* Default frame format:                                                */
/* 1 start bit, 8 data bits, no parity bit, 1 stop bit					*/
/************************************************************************/
void init_uart(void)
{
    // Set baud rate
    UBRR0 = F_CPU / (BAUD_RATE_RATIO * BAUD_RATE) - 1;

    #ifdef U2X
        UCSR0A = _BV(U2X0);
    #endif
 
    // Enable transmission only
    UCSR0B = _BV(TXEN0);

    uart_transmit("- UART ready\r\n");
}