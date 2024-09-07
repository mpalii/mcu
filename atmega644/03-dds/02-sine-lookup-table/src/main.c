/*
 * @author Maksym Palii
 * @brief SIN lookup table (full period)
 * @version 1.0
 * @date 2024 September 07
 */

#define F_CPU               (16000000UL)
#define BAUD_RATE           (9600UL)
#define SINE_VALUES_POOL    (256UL)
#define SINE_SCALE_FACTOR   (100UL)

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "drivers/gpio.h"
#include "drivers/uart.h"

char text_buffer[5];
int8_t sine_table[SINE_VALUES_POOL];

int main(void)
{
    init_gpio();
    init_uart();
    uart_transmit("Start up...\r\n");

    for (uint16_t i = 0; i < SINE_VALUES_POOL; i++)
    {
        itoa(i, text_buffer, 10);
        uart_transmit(text_buffer);
        uart_transmit(" : ");

        sine_table[i] = sin((2 * M_PI * i) / SINE_VALUES_POOL) * SINE_SCALE_FACTOR;

        itoa(sine_table[i], text_buffer, 10);
        uart_transmit(text_buffer);
        uart_transmit("\r\n");
    }
    
    while (true);
}