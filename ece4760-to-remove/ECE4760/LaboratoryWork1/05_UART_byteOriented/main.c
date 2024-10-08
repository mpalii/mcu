/*
 * 05_UART_charOriented.c
 *
 * Created: 12/02/2023 11:58:24
 * Author : Maksym Palii
 */

 #define F_CPU 8000000UL

#include <avr/io.h>
#include <stdbool.h>
#include "uart328p.h"

int8_t response = 0;

void init_io_pins(void);

int main(void)
{
    init_io_pins();
    UART_init(F_CPU, 9600, false);
	
    while (true) 
    {
        // Wait for user command
        int8_t data = UART_receive();
		
        // Handle command
        switch (data)
        {
            case 'e':   // e - enable
                PORTB |= _BV(PORTB0);
                response = 0;
                break;
            case 'd':	// d - disable
                PORTB &= ~_BV(PORTB0);
                response = 0;
                break;
            case '\r':
            case '\n':
                continue
            default:
                response = -1;	
        }
		
        // Send response
        UART_transmit(response);
    }
}

void init_io_pins(void)
{
    // Set port D pin 0 as output
    DDRB |= _BV(DDB0);
}
