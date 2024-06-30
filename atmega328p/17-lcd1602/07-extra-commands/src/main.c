/*
 * @author Maksym Palii
 * @brief LCD 1608 - 8bit mode
 * @version 1.0
 * @date 2024 June 29
 */
#define F_CPU (8000000UL)
#define MOVE_CURSOR_TO_0_POSITION_LINE_1 0x80
#define MOVE_CURSOR_TO_3_POSITION_LINE_2 0xC3
#define CLEAR_DISPLAY 0x01
#define SHIFT_DISPLAY_RIGHT 0x18
#define SHIFT_DISPLAY_LEFT 0x1C

#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>
#include "drivers/gpio.h"
#include "drivers/lcd1602.h"

void print_lcd_with_delay(char* array)
{
    uint8_t i = 0;
	while (array[i] != '\0')
	{
		send_data(array[i++]);
		_delay_ms(100);
	}
}

int main(void)
{
	init_gpio();
	init_lcd1602();
 
	while (true)
	{
		send_command(CLEAR_DISPLAY);
		_delay_ms(500);

		send_command(MOVE_CURSOR_TO_0_POSITION_LINE_1);
		print_lcd_with_delay("LCD 1602 8-bit mode");
		_delay_ms(500);

		send_command(MOVE_CURSOR_TO_3_POSITION_LINE_2);
		print_lcd_with_delay("Simple text message");
		_delay_ms(500);

		for (uint8_t i = 0; i < 10; i++)
		{
			send_command(SHIFT_DISPLAY_RIGHT);
	        _delay_ms(250);
		}

		for (uint8_t i = 0; i < 10; i++)
		{
			send_command(SHIFT_DISPLAY_LEFT);
	        _delay_ms(250);
		}

	    _delay_ms(500);
	}
}