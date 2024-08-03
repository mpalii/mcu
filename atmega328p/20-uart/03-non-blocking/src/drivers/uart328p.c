#include "uart328p.h"

#define BUFFER_SIZE 9

// RX
char input_buffer[BUFFER_SIZE] = {'\0'};
unsigned char index_input = 0;
bool rx_in_progress = false;

// TX
char* output_buffer;
unsigned char index_output = 0;
bool tx_in_progress = false;

void init_frame_format(void)
{
    /************************************************************************/
    /* Default frame format:                                                */
    /* 1 start bit, 8 data bits, no parity bit, 1 stop bit                  */
    /************************************************************************/
}

void uart_init(uint32_t f_cpu, uint32_t baud_rate, bool double_speed_enabled)
{
    // Baud rate calculation ratio
    uint32_t baud_rate_divider = 16;
	
    // Check double speed (U2X) mode
    if (double_speed_enabled)
    {
        UCSR0A = _BV(U2X0);
        baud_rate_divider /= 2;
    }
	
    // Set baud rate
    UBRR0 = f_cpu / (baud_rate_divider * baud_rate) - 1;
	
    // Enable receiving and transmission
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);
	
    init_frame_format();
	
    // enable interrupt on receive and transmit 
    UCSR0B |= _BV(RXCIE0) | _BV(TXCIE0);
}

void uart_receive(void)
{
    if (rx_in_progress)
    {
        int8_t data = UDR0;
		
        if (index_input >= BUFFER_SIZE)
        {
            index_input = 0;
        }
		
        if (data == '\r' || data == '\n')
        {
            input_buffer[index_input] = '\0';
            rx_in_progress = false;
            index_input = 0;
        }
        else
		{
            input_buffer[index_input] = data;
            index_input++;
        }
    }
}

/**
 * After handling recieved data call the uart_set_ready_for_recieve()
 */
char* uart_receive_data(void)
{
    return rx_in_progress ? NULL : input_buffer;
}

void uart_transmit(void) 
{
    if (tx_in_progress)
    {
        int8_t data = output_buffer[index_output];
        if (data != '\0')
        {
            UDR0 = data;
            index_output++;
        } 
        else
        {
            rx_in_progress = true;
            tx_in_progress = false;
            index_output = 0;
        }
    }
}

void uart_transmit_data(char* data)
{
    if (tx_in_progress)
    {
        return;
    }
    
    output_buffer = data;
    tx_in_progress = true;
    uart_transmit();
}

void uart_set_ready_for_recieve(void)
{
    rx_in_progress = true;
}
