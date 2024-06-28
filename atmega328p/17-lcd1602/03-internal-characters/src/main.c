/*
 * @author Maksym Palii
 * @brief LCD 1608 - 4bit mode
 * @version 1.0
 * @date 2024 June 28
 */
#define F_CPU (8000000UL)

#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>
#include "drivers/gpio.h"
#include "drivers/lcd1602.h"

void set_cursor_position(uint8_t position)
{
	send_command(0b10000000 | position);
}

int main(void)
{
	init_gpio();
	init_lcd1602();

    for (uint8_t i = 0; i < 26; i++)
	{
		uint8_t cursor_position = (i % 2 == 0) ? 0x00 : 0x40;
		set_cursor_position(cursor_position);

		for (uint8_t j = 0; j < 10; j++)
		{
			uint8_t data = i * 10 + j;
			send_data(data);
			// _delay_ms(750);
		}

		_delay_ms(1500);
	}
	
 
	while (true)
	{
		// No logic
	}
}