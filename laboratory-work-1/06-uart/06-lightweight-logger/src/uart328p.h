#ifndef UART328P_H_
#define UART328P_H_

#if !defined(F_CPU)
/* terminate compilation if not specified */
# error "F_CPU must be specified for \"uart328p.h\""
#endif

#if !defined(BAUD_RATE)
/* terminate compilation if not specified */
# error "BAUD_RATE must be specified for \"uart328p.h\""
#endif

#ifdef U2X
    #define BAUD_RATE_RATIO 8UL
#else 
    #define BAUD_RATE_RATIO 16UL
#endif       

#define UBRR_VALUE (F_CPU / (BAUD_RATE_RATIO * BAUD_RATE) - 1)

#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>

/************************************************************************/
/* Default frame format:                                                */
/* 1 start bit, 8 data bits, no parity bit, 1 stop bit					*/
/************************************************************************/

static inline void uart_init()
{
    // Set baud rate
    UBRR0 = UBRR_VALUE;

    #ifdef U2X
        UCSR0A = _BV(U2X0);
    #endif
 
    // Enable transmission only
    UCSR0B = _BV(TXEN0);
}

void uart_transmit(char* array)
{
    uint16_t i = 0;

    // Send characters until zero byte
    while (array[i] != '\0')
    {
        // Wait for empty transmit buffer
        loop_until_bit_is_set(UCSR0A, UDRE0);
    
        // Put data into buffer, sends the data
        UDR0 = array[i++];
    }
}

#endif /* UART328P_H_ */