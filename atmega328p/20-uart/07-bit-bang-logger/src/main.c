/*
 * @author Maksym Palii
 * @brief bit banging UART logger
 * @version 1.0
 * @date 2024 August 04
 */

#define F_CPU (8000000UL)
#define BAUD_RATE (9600UL)

#include "serial.h"

int main(void)
{
    serial_init();
    serial_transmit("Bit-banging serial communication...\r\n");
 
    while (true)
    {    
        // NOP
    }
}
