/*
 * @author Maksym Palii
 * @brief LCD 1608 - 8bit mode
 * @version 1.0
 * @date 2024 June 26
 */
#define F_CPU (8000000UL)

#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>
#include "drivers/gpio.h"
#include "drivers/lcd1602.h"

void print_lcd(char* array)
{
    uint8_t i = 0;
	while (array[i] != '\0')
	{
		send_data(array[i]);
		i++;	
	}
}

void set_cursor_position(uint8_t position)
{
	send_command(0x80 | position);
}

int main(void)
{
	init_gpio();
	init_lcd1602();
 
	print_lcd("8-bit data bus");
	set_cursor_position(0x40);
    print_lcd("HD44780");
 
	while (true)
	{
		// No logic
	}
}