#include "gpio.h"
#include "uart.h"
#include <stdbool.h>
#include <stddef.h>
#include <util/delay.h>

#define MOVE_CURSOR_TO_POSITION_0_LINE_1 0x80
#define MOVE_CURSOR_TO_POSITION_0_LINE_2 0xC0
#define CLEAR_DISPLAY 0x01

static char *message_pointer = NULL;

static void data_bus_input(void)
{
    _gpio_set_input(LCD_PD0);
    _gpio_set_input(LCD_PD1);
    _gpio_set_input(LCD_PD2);
    _gpio_set_input(LCD_PD3);
    _gpio_set_input(LCD_PD4);
    _gpio_set_input(LCD_PD5);
    _gpio_set_input(LCD_PD6);
    _gpio_set_input(LCD_PD7);
}

static void data_bus_output(void)
{
    _gpio_set_output(LCD_PD0);
    _gpio_set_output(LCD_PD1);
    _gpio_set_output(LCD_PD2);
    _gpio_set_output(LCD_PD3);
    _gpio_set_output(LCD_PD4);
    _gpio_set_output(LCD_PD5);
    _gpio_set_output(LCD_PD6);
    _gpio_set_output(LCD_PD7);
}

static void data_bus_low(void)
{
    _gpio_low(LCD_PD0);
    _gpio_low(LCD_PD1);
    _gpio_low(LCD_PD2);
    _gpio_low(LCD_PD3);
    _gpio_low(LCD_PD4);
    _gpio_low(LCD_PD5);
    _gpio_low(LCD_PD6);
    _gpio_low(LCD_PD7);
}

static void send_byte(uint8_t data)
{
    data_bus_low();
    data_bus_output();
    
    _gpio_high(LCD_EN);

    if (data & 0x01) _gpio_high(LCD_PD0);
    if (data & 0x02) _gpio_high(LCD_PD1);
    if (data & 0x04) _gpio_high(LCD_PD2);
    if (data & 0x08) _gpio_high(LCD_PD3);
    if (data & 0x10) _gpio_high(LCD_PD4);
    if (data & 0x20) _gpio_high(LCD_PD5);
    if (data & 0x40) _gpio_high(LCD_PD6);
    if (data & 0x80) _gpio_high(LCD_PD7);

    _gpio_low(LCD_EN);
}

static void initialize_by_instructions(void)
{
    _delay_ms(100);

    _gpio_low(LCD_RS);
    _gpio_low(LCD_RW);
    _gpio_low(LCD_EN);

    data_bus_output();
    _gpio_low(LCD_PD7);
    _gpio_low(LCD_PD6);
    _gpio_high(LCD_PD5);
    _gpio_high(LCD_PD4);

    // Special case of 'Function Set'
    _gpio_high(LCD_EN);
    asm("nop"::);
    asm("nop"::);
    _gpio_low(LCD_EN);

    _delay_ms(5);

    // Special case of 'Function Set'
    _gpio_high(LCD_EN);
    asm("nop"::);
    asm("nop"::);
    _gpio_low(LCD_EN);

    _delay_ms(100);

    // Special case of 'Function Set'
    _gpio_high(LCD_EN);
    asm("nop"::);
    asm("nop"::);
    _gpio_low(LCD_EN);
}

static uint8_t read_bf_and_ac(void)
{
    data_bus_low();
    data_bus_input();

    _gpio_low(LCD_RS);
    _gpio_high(LCD_RW);

    uint8_t result = 0;

    _gpio_high(LCD_EN);
    asm("nop"::);
    asm("nop"::);
    if (_gpio_get_input(LCD_PD0)) result |= 0b00000001;
    if (_gpio_get_input(LCD_PD1)) result |= 0b00000010;
    if (_gpio_get_input(LCD_PD2)) result |= 0b00000100;
    if (_gpio_get_input(LCD_PD3)) result |= 0b00001000;
    if (_gpio_get_input(LCD_PD4)) result |= 0b00010000;
    if (_gpio_get_input(LCD_PD5)) result |= 0b00100000;
    if (_gpio_get_input(LCD_PD6)) result |= 0b01000000;
    if (_gpio_get_input(LCD_PD7)) result |= 0b10000000;
    _gpio_low(LCD_EN);

    return result;
}

static void send_command(uint8_t command)
{
    _gpio_low(LCD_RS);
    _gpio_low(LCD_RW);
    send_byte(command);
}

static void send_data(uint8_t data)
{
    _gpio_high(LCD_RS);
    _gpio_low(LCD_RW);
    send_byte(data);
}

void init_lcd(void)
{
    // LCD control bus
    _gpio_set_output(LCD_RS);
    _gpio_set_output(LCD_RW);
    _gpio_set_output(LCD_EN);

    initialize_by_instructions();
    while (read_bf_and_ac() & 0x80);    
    send_command(0b00111100);	// 'Function Set' - 8bit mode, 2 lines, 5x8 font
    while (read_bf_and_ac() & 0x80);    
    send_command(0b00001111);	// 'Display ON/OFF Control' display on, cursor off and not blink    0b00001100
    while (read_bf_and_ac() & 0x80);    
    send_command(0b00000001);	// 'Clear Display'
    while (read_bf_and_ac() & 0x80);
    send_command(0b00000110);	// 'Entry Mode Set' cursor shift to right

    uart_transmit("- LCD ready\r\n");
}

void lcd_add_to_rendering(char *msg)
{
    message_pointer = msg;
}


void lcd_render(void)
{
    if ((message_pointer != NULL) && !(read_bf_and_ac() & 0x80))
    {
        char data = *message_pointer;

        switch (data)
        {
            case '\0':
                message_pointer = NULL;
                return;
            case '\b':
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