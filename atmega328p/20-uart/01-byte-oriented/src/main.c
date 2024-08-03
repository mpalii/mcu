/*
 * @author Maksym Palii
 * @brief UART blocking byte-oriented approach
 * @version 1.0
 * @date 2024 August 01
 */

#define F_CPU (8000000UL)

// Serial communication responses
// No response if success
#define ALREADY_DISABLED  0x64  // ASCII 'd' character
#define ALREADY_ENABLED   0x65  // ASCII 'e' character
#define UNKNOWN_COMMAND   0x75  // ASCII 'u' character

#include "drivers/gpio.h"
#include "drivers/uart328p.h"

int8_t error_response = UNKNOWN_COMMAND;
bool pin_enabled = false;

int main(void)
{
    init_gpio();
    uart_init(F_CPU, 9600, false);
	
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
                    GPIO_HIGH(LED);
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
                    GPIO_LOW(LED);
                    pin_enabled = false;
                    continue;
                }
                error_response = ALREADY_DISABLED;
                break;

            // T/t - toggle pin state
            case 'T':
            case 't':
                GPIO_TOGGLE(LED);
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
