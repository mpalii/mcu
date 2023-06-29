/*
 * @author Maksym Palii
 * @brief LCD 1608 - 4bit mode
 * @version 1.0
 * @date 2023 June 25
 */

#define F_CPU (18432000UL)

#define MOVE_CURSOR_TO_0_POSITION_LINE_1 0x80
#define MOVE_CURSOR_TO_3_POSITION_LINE_2 0xC3
#define CLEAR_DISPLAY 0x01

// Register select (RS) pin
#define RS_HIGH (PORTC |= (1 << PC0))
#define RS_LOW	(PORTC &= ~(1 << PC0))

// Enable (E) pin
#define E_HIGH	(PORTC |= (1 << PC1))
#define E_LOW	(PORTC &= ~(1 << PC1))

#include <avr/io.h>
#include <util/delay.h>

char *message1 = "LCD 1602";
char *message2 = "4-bit mode";

void sendCommand4BitMode(uint8_t command) {
	RS_LOW;
	PORTD = command;
	E_HIGH;
	_delay_us(37);
	E_LOW;
	_delay_us(37);
	PORTD = command << 4;
	E_HIGH;
	_delay_us(37);
	E_LOW;
	_delay_us(37);
}

void sendCommand8BitMode(uint8_t command) {
	RS_LOW;
	PORTD = command;
	E_HIGH;
	_delay_us(37);
	E_LOW;
	_delay_us(37);
}

// First need to send 4 higher bits, and then 4 lower bits
void sendData(uint8_t data) {
	RS_HIGH;
	PORTD = data;
	E_HIGH;
	_delay_us(37);
	E_LOW;
	_delay_us(37);
	PORTD = data << 4;
	E_HIGH;
	_delay_us(37);
	E_LOW;
	_delay_us(37);
}

void sendMessage(char message[])
{
	uint8_t i = 0;
	while (message[i] != '\0')
	{
		sendData(message[i++]);
	}
}

void sendMessageWithDelay(char* message)
{
    uint8_t i = 0;
    while (message[i] != '\0')
    {
        sendData(message[i++]);
		_delay_ms(100);
    }
}

// LCD pin out config
void pinoutSetup1602(void) {
	DDRC |= (1 << PC0) | (1 << PC1);							// Control bus
	DDRD |= (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7);	// Data bus
}

// 4bit mode initialization
void init4BitMode(void) {
	_delay_ms(100);
	sendCommand8BitMode(0b00110000);	// Special case of 'Function Set'
	_delay_ms(5);	
	sendCommand8BitMode(0b00110000);	// Special case of 'Function Set'
	_delay_us(100);
	sendCommand8BitMode(0b00110000);	// Special case of 'Function Set'
	
	_delay_us(100);
	sendCommand8BitMode(0b00100000);	// Initial 'Function Set' - 4bit mode
	_delay_us(100);
	sendCommand4BitMode(0b00101000);	// Real 'Function Set' - 4bit mode, 2 lines, 5x8 font
	_delay_us(53);
	sendCommand4BitMode(0b00001100);	// 'Display ON/OFF Control' display on, cursor off and not blink
	_delay_us(53);
	sendCommand4BitMode(0b00000001);	// 'Clear Display'
	_delay_ms(3);
	sendCommand4BitMode(0b00000110);	// 'Entry Mode Set' cursor shift to right
	_delay_ms(53);
}

int main(void)
{
	pinoutSetup1602();
	init4BitMode();
	
    while (1) 
    {
		sendCommand4BitMode(CLEAR_DISPLAY);
	    _delay_ms(500);

		sendCommand4BitMode(MOVE_CURSOR_TO_0_POSITION_LINE_1);
		sendMessageWithDelay("LCD 1602 4-bit mode");
	    _delay_ms(500);

	    sendCommand4BitMode(MOVE_CURSOR_TO_3_POSITION_LINE_2);
		sendMessageWithDelay("Simple text message");
	    _delay_ms(500);

        // DISPLAY shifting
		for (uint8_t i = 0; i < 10; i++)
		{
			sendCommand4BitMode(0x18);
	        _delay_ms(250);
		}

		for (uint8_t i = 0; i < 10; i++)
		{
			sendCommand4BitMode(0x1C);
	        _delay_ms(250);
		}

	    _delay_ms(500);
    }
}
