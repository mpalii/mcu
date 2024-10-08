/*
 * Created: 20/12/2022 15:44:10
 * Author : Maksym_Palii
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <avr/interrupt.h>
#include "uart328p.h"

#define BUFFER_SIZE 50

volatile char input_buffer[BUFFER_SIZE] = {'\0'};
volatile int input_buffer_index = 0;
volatile bool rx_completed = false;


ISR(USART_RX_vect)
{
	char ch = UDR0;
	if (!rx_completed)
	{
		if (input_buffer_index >= BUFFER_SIZE)
		{
			input_buffer_index = 0;
		}
		if (ch == '\n' || ch == '\r')
		{
			input_buffer[input_buffer_index] = '\0';
			rx_completed = true;
			input_buffer_index = 0;
		}
		else
		{
			input_buffer[input_buffer_index] = ch;
			input_buffer_index++;
		}
	}
	
	/*
	if (!rx_completed) 
	{
		if (input_buffer_index >= BUFFER_SIZE)
		{
			input_buffer_index = 0;
		}
		if (UDR0 == '\n' || UDR0 == '\r')
		{
			input_buffer[input_buffer_index] = '\0';
			rx_completed = true;
		} 
		else
		{
			input_buffer[input_buffer_index] = UDR0;
			input_buffer_index++;
		}
	}
	*/
}

int main(void)
{
    stdin = stdout = stderr = UART_init(18432000, 9600, false);
	printf("Start up...\n");
	
	sei();

    while (true) 
    {
		if (rx_completed) 
		{
			printf("INPUT:'%s'\n", input_buffer);
			input_buffer_index = 0;
			rx_completed = false;
		}
    }
}

