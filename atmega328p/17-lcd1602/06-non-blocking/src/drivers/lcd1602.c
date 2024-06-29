#define F_CPU 8000000UL

#define MOVE_CURSOR_TO_POSITION_0_LINE_1 0x80
#define MOVE_CURSOR_TO_POSITION_0_LINE_2 0xC0
#define CLEAR_DISPLAY 0x01

#include "lcd1602.h"
#include "gpio.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stddef.h>

char *message_pointer = NULL;


static void data_bus_input(void)
{
    GPIO_SET_INPUT(DATA0);
    GPIO_SET_INPUT(DATA1);
    GPIO_SET_INPUT(DATA2);
    GPIO_SET_INPUT(DATA3);
    GPIO_SET_INPUT(DATA4);
    GPIO_SET_INPUT(DATA5);
    GPIO_SET_INPUT(DATA6);
    GPIO_SET_INPUT(DATA7);
}

static void data_bus_output(void)
{
    GPIO_SET_OUTPUT(DATA0);
    GPIO_SET_OUTPUT(DATA1);
    GPIO_SET_OUTPUT(DATA2);
    GPIO_SET_OUTPUT(DATA3);
    GPIO_SET_OUTPUT(DATA4);
    GPIO_SET_OUTPUT(DATA5);
    GPIO_SET_OUTPUT(DATA6);
    GPIO_SET_OUTPUT(DATA7);
}

static void data_bus_low(void)
{
    GPIO_LOW(DATA0);
    GPIO_LOW(DATA1);
    GPIO_LOW(DATA2);
    GPIO_LOW(DATA3);
    GPIO_LOW(DATA4);
    GPIO_LOW(DATA5);
    GPIO_LOW(DATA6);
    GPIO_LOW(DATA7);
}

static void send_byte(uint8_t data)
{
    data_bus_low();
    data_bus_output();
    
    GPIO_HIGH(EN);

    if (data & 0x01) GPIO_HIGH(DATA0);
    if (data & 0x02) GPIO_HIGH(DATA1);
    if (data & 0x04) GPIO_HIGH(DATA2);
    if (data & 0x08) GPIO_HIGH(DATA3);
    if (data & 0x10) GPIO_HIGH(DATA4);
    if (data & 0x20) GPIO_HIGH(DATA5);
    if (data & 0x40) GPIO_HIGH(DATA6);
    if (data & 0x80) GPIO_HIGH(DATA7);

	GPIO_LOW(EN);
}

static void initialize_by_instructions(void)
{
    _delay_ms(100);

    GPIO_LOW(RS);
    GPIO_LOW(RW);
    GPIO_LOW(EN);

    data_bus_output();
    GPIO_LOW(DATA7);
    GPIO_LOW(DATA6);
    GPIO_HIGH(DATA5);
    GPIO_HIGH(DATA4);

    // Special case of 'Function Set'
    GPIO_HIGH(EN);
    asm("nop"::);
    asm("nop"::);
    GPIO_LOW(EN);

    _delay_ms(5);

    // Special case of 'Function Set'
    GPIO_HIGH(EN);
    asm("nop"::);
    asm("nop"::);
    GPIO_LOW(EN);

    _delay_ms(100);

    // Special case of 'Function Set'
    GPIO_HIGH(EN);
    asm("nop"::);
    asm("nop"::);
    GPIO_LOW(EN);
}

static uint8_t read_bf_and_ac(void)
{
    data_bus_low();
    data_bus_input();

    GPIO_LOW(RS);
    GPIO_HIGH(RW);

    uint8_t result = 0;

    GPIO_HIGH(EN);
    asm("nop"::);
    asm("nop"::);
    if (GPIO_GET_INPUT(DATA0)) result |= 0b00000001;
    if (GPIO_GET_INPUT(DATA1)) result |= 0b00000010;
    if (GPIO_GET_INPUT(DATA2)) result |= 0b00000100;
    if (GPIO_GET_INPUT(DATA3)) result |= 0b00001000;
    if (GPIO_GET_INPUT(DATA4)) result |= 0b00010000;
    if (GPIO_GET_INPUT(DATA5)) result |= 0b00100000;
    if (GPIO_GET_INPUT(DATA6)) result |= 0b01000000;
    if (GPIO_GET_INPUT(DATA7)) result |= 0b10000000;
    GPIO_LOW(EN);

    return result;
}

static void send_command(uint8_t command)
{
	GPIO_LOW(RS);
    GPIO_LOW(RW);
	send_byte(command);
}

static void send_data(uint8_t data)
{
	GPIO_HIGH(RS);
    GPIO_LOW(RW);
	send_byte(data);
}

void init_lcd1602(void)
{
    initialize_by_instructions();
	while (read_bf_and_ac() & 0x80);    
	send_command(0b00111100);	// 'Function Set' - 8bit mode, 2 lines, 5x8 font
	while (read_bf_and_ac() & 0x80);    
	send_command(0b00001111);	// 'Display ON/OFF Control' display on, cursor off and not blink    0b00001100
	while (read_bf_and_ac() & 0x80);    
	send_command(0b00000001);	// 'Clear Display'
	while (read_bf_and_ac() & 0x80);
	send_command(0b00000110);	// 'Entry Mode Set' cursor shift to right
}


bool pass_to_rendering(char *msg)
{
	if (message_pointer == NULL)
	{
		message_pointer = msg;
		return true;
	}

	return false;
}


void print(void)
{
	if ((message_pointer != NULL) && !(read_bf_and_ac() & 0x80))
	{
		char data = *message_pointer;

		switch (data)
		{
			case '\0':
				message_pointer = NULL;
				return;
			case '#':
				send_command(CLEAR_DISPLAY);
				break;
			case '\r':
				send_command(MOVE_CURSOR_TO_POSITION_0_LINE_1);
				break;
			case '\n':
				send_command(MOVE_CURSOR_TO_POSITION_0_LINE_2);
				break;
			default:
				send_data(data);
		}

		message_pointer++;
	}
}
