/*
 * @author Maksym Palii
 * @brief UART blocking byte-oriented approach
 * @version 1.0
 * @date 2023 June 11
 */

#define F_CPU 8000000UL

// Serial communication responses
// No response if success
#define ALREADY_DISABLED  0x64  // ASCII 'd' character
#define ALREADY_ENABLED   0x65  // ASCII 'e' character
#define UNKNOWN_COMMAND   0x75  // ASCII 'u' character

#include "uart328p.h"

void init_io_pins(void);

int main(void)
{
    init_io_pins();
    uart_init(F_CPU, 9600, false);

    int8_t error_response = UNKNOWN_COMMAND;
    bool pin_enabled = false;
	
    while (true) 
    {
        // Wait for user command
        int8_t cmd = uart_receive();
        
        // Handle user command
        switch (cmd)
        {
            // E/e - set pin driven HIGH
            case 'E':
            case 'e':   
                if (!pin_enabled)
                {
                    PORTB |= _BV(PORTB0);
                    pin_enabled = true;
                    continue;
                }
                error_response = ALREADY_ENABLED;
                break;

            // D/d - set pin driven LOW
            case 'D':
            case 'd':	
                if (pin_enabled)
                {
                    PORTB &= ~_BV(PORTB0);
                    pin_enabled = false;
                    continue;
                }
                error_response = ALREADY_DISABLED;
                break;

            // T/t - toggle pin state
            case 'T':
            case 't':
                PORTB ^= _BV(PORTB0);
                pin_enabled = pin_enabled ? false : true;
                continue;

            // CRLF handling - no actions for these symbols
            case '\r':
            case '\n':
                continue;

            // Unknown command     
            default:
                error_response = UNKNOWN_COMMAND;	
        }

        // Send response
        uart_transmit(error_response);
    }
}

void init_io_pins(void)
{
    // Set port D pin 0 as output
    DDRB |= _BV(DDB0);
}
