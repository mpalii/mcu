/*
 * @author Maksym Palii
 * @brief UART small size logger
 * @version 1.0
 * @date 2023 June 17
 */

#define F_CPU 8000000UL
#define BAUD_RATE 9600UL

#include "uart328p.h"

int main(void)
{
    uart_init();
    uart_transmit("Start up...\r\n");
 
    while (true)
    {    
        // NOP
    }
}
