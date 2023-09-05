#define F_CPU 18432000UL

#include "lcd1602.h"
#include "gpio.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stddef.h>

void strobe(void);

char *message_pointer = NULL;

void init_lcd1602(void)
{
	_delay_ms(100);
	lcd1602_send_command(0b00110000);	// Special case of 'Function Set'
	_delay_ms(5);
	lcd1602_send_command(0b00110000);	// Special case of 'Function Set'
	_delay_us(100);
	lcd1602_send_command(0b00110000);	// Special case of 'Function Set'
	
	_delay_us(100);
	lcd1602_send_command(0b00111000);	// 'Function Set' - 8bit mode, 2 lines, 5x8 font
	_delay_us(53);
	lcd1602_send_command(0b00001100);	// 'Display ON/OFF Control' display on, cursor off and not blink
	_delay_us(53);
	lcd1602_send_command(0b00000001);	// 'Clear Display'
	_delay_ms(3);
	lcd1602_send_command(0b00000110);	// 'Entry Mode Set' cursor shift to right
	_delay_ms(53);
}

void lcd1602_print_char(char data)
{
    GPIO_HIGH(LCD_1602_RS);
	PORTD = data;
	strobe();
}

void lcd1602_send_command(char command)
{
    GPIO_LOW(LCD_1602_RS);
	PORTD = command;
	strobe();
}

void strobe(void)
{
	GPIO_HIGH(LCD_1602_E);
	_delay_us(1000);
	GPIO_LOW(LCD_1602_E);
	//_delay_us(37);
}



void printMessage(char *msg)
{
	message_pointer = msg;
}


void handleMessageChar(void)
{
	if (message_pointer != NULL)
	{
		GPIO_LOW(LCD_1602_E);
		char data = *message_pointer;
		
		if (data == '\0')
		{
			message_pointer = NULL;
			return;
		}
		
		if (data == '#')
		{
			GPIO_LOW(LCD_1602_RS);
			PORTD = CLEAR_DISPLAY;
		}
		else if (data == '\r')
		{
			GPIO_LOW(LCD_1602_RS);
			PORTD = MOVE_CURSOR_TO_POSITION_0_LINE_1;
		}
		else if (data == '\n')
		{
			GPIO_LOW(LCD_1602_RS);
			PORTD = MOVE_CURSOR_TO_POSITION_0_LINE_2;
		}
		else
		{
			GPIO_HIGH(LCD_1602_RS);
			PORTD = data;
		}
		
		GPIO_HIGH(LCD_1602_E);
		message_pointer++;
	}
}


/* 
void handleMessageChar(void)
{
	if (message_pointer != NULL)
	{
		GPIO_LOW(LCD_1602_E);
		char data = *message_pointer;
		
		if (data != '\0')
		{
			//GPIO_LOW(LCD_1602_E);
			GPIO_HIGH(LCD_1602_RS);
			PORTD = data;
			GPIO_HIGH(LCD_1602_E);
			message_pointer++;
		}
		else 
		{
			//GPIO_LOW(LCD_1602_E);
			message_pointer = NULL;
		}
	}
}
*/