/*
 * @author Maksym Palii
 * @brief LCD 1608 - 8bit mode
 * @version 1.0
 * @date 2024 June 28
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
		uint8_t busy_flag_and_address_counter = read_bf_and_ac();

		if (busy_flag_and_address_counter & 0x01) GPIO_HIGH(AC0);
		else GPIO_LOW(AC0);

		if (busy_flag_and_address_counter & 0x02) GPIO_HIGH(AC1);
		else GPIO_LOW(AC1);

		if (busy_flag_and_address_counter & 0x04) GPIO_HIGH(AC2);
		else GPIO_LOW(AC2);

		if (busy_flag_and_address_counter & 0x08) GPIO_HIGH(AC3);
		else GPIO_LOW(AC3);

		if (busy_flag_and_address_counter & 0x10) GPIO_HIGH(AC4);
		else GPIO_LOW(AC4);

		if (busy_flag_and_address_counter & 0x20) GPIO_HIGH(AC5);
		else GPIO_LOW(AC5);

		if (busy_flag_and_address_counter & 0x40) GPIO_HIGH(AC6);
		else GPIO_LOW(AC6);

		if (busy_flag_and_address_counter & 0x80) GPIO_HIGH(BF);
		else GPIO_LOW(BF);

		send_data(array[i]);
		i++;
		_delay_ms(1000);
	}
}

void set_cursor_position(uint8_t position)
{
	send_command(0b10000000 | position);
}

int main(void)
{
	init_gpio();
	init_lcd1602();

	// print_lcd("1xxxxxxxxx");
	// print_lcd("2xxxxxxxxx");
	// print_lcd("3xxxxxxxxx");
	// print_lcd("4xxxxxxxxx");
	// print_lcd("5xxxxxxxxx");
	// print_lcd("6xxxxxxxxx");
	// print_lcd("7xxxxxxxxx");
	// print_lcd("8xxxxxxxxx");
	// print_lcd("9xxxxxxxxx");
	// print_lcd("Axxxxxxxxx");

 
	set_cursor_position(0x40);
	print_lcd("8-bit data bus");
	set_cursor_position(0x00);
    print_lcd("HD44780");
 
	while (true)
	{
		// No logic
	}
}