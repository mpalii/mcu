/*
 * @author Maksym Palii
 * @brief DS18B20
 * @version 1.0
 * @date 2024 August 08
 */

#define F_CPU (8000000UL)
#define BAUD_RATE (9600UL)

#include <stdlib.h>
#include <util/delay.h>
#include "drivers/gpio.h"
#include "drivers/uart328p.h"

#include <avr/interrupt.h>

bool reset_line(void);
void write_byte(uint8_t byte);
uint8_t read_byte(void);
uint16_t read_temperature(void);
void print_temperature(void);

char uart_buffer[32];
uint8_t rom_code[8] = { 0 };

int main(void)
{
	init_gpio();
	uart_init();

	uart_transmit("Start up...\r\n");

	reset_line();
	write_byte(0x33);

	for (uint8_t i = 0; i < sizeof(rom_code); i++)
	{
		rom_code[i] = read_byte();
		itoa(rom_code[i], uart_buffer, 16);
		uart_transmit(uart_buffer);
	}

	uart_transmit("\r\n");

	while (true)
	{
		print_temperature();
	}
}

void write_byte(uint8_t byte)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		if (byte & _BV(i))
		{
			GPIO_SET_OUTPUT(LINE_1_WIRE);
			_delay_us(2);
			GPIO_SET_INPUT(LINE_1_WIRE);
			_delay_us(58);
		}
		else
		{
			GPIO_SET_OUTPUT(LINE_1_WIRE);
			_delay_us(65);
			GPIO_SET_INPUT(LINE_1_WIRE);
		}
	}
}

bool reset_line(void)
{
	
	GPIO_SET_OUTPUT(LINE_1_WIRE);
	_delay_us(500);
	GPIO_SET_INPUT(LINE_1_WIRE);
	_delay_us(120);

	bool is_ready = GPIO_GET_INPUT(LINE_1_WIRE) ? false : true;
	_delay_us(380);

	return is_ready;
}

uint8_t read_byte(void)
{
	uint8_t result = 0b00000000;

	for (int i = 0; i < 8; i++)
	{
		GPIO_SET_OUTPUT(LINE_1_WIRE);
		_delay_us(2);
		GPIO_SET_INPUT(LINE_1_WIRE);
		_delay_us(13);

		if (GPIO_GET_INPUT(LINE_1_WIRE))
		{
			result |= _BV(i);
		}

		_delay_us(45);
	}
	
	return result ;
}

uint16_t read_temperature(void)
{
	reset_line();		// reset line
	write_byte(0xCC);	// skip ROM
	write_byte(0x44);	// start conversion
	_delay_ms(750);		// conversion time for 12-bit resolution mode 

	reset_line();		// reset line
	write_byte(0xCC);	// skip ROM
	write_byte(0xBE);	// read temeperature data from sensor

	// uint16_t result = 0x0000;
	// *((uint8_t *) &result) = read_byte();
	// *(((uint8_t *) &result) + 1) = read_byte();

	uint8_t l_byte = read_byte();
	uint8_t h_byte = read_byte();

	uint16_t result = l_byte | (h_byte << 8);
	return result;
}

void print_temperature(void)
{
	uint16_t temperature = read_temperature();

	int8_t integer_part = temperature >> 4;
	int8_t fraction_part =  (temperature & 8000) ? (-1 * temperature) : temperature;
	fraction_part = ((fraction_part & 0x0f) * 10) / 16;

	itoa(integer_part, uart_buffer, 10);
	uart_transmit(uart_buffer);
	uart_transmit(".");
	itoa(fraction_part, uart_buffer, 10);
	uart_transmit(uart_buffer);
	uart_transmit(" ºC\r\n");
}
