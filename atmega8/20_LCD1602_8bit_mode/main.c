/*
 * Created: 16.12.2021 20:57:35
 * Author : Maksym Palii
 */

#define F_CPU (1000000)

// Register select (RS) pin
#define RS_HIGH (PORTC |= (1 << PC0))
#define RS_LOW	(PORTC &= ~(1 << PC0))

// Enable (E) pin
#define E_HIGH	(PORTC |= (1 << PC1))
#define E_LOW	(PORTC &= ~(1 << PC1))

#include <avr/io.h>
#include <util/delay.h>

void sendCommand(uint8_t command) {
	RS_LOW;
	PORTD = command;
	E_HIGH;
	_delay_us(37);
	E_LOW;
	_delay_us(37);
}

void sendData(uint8_t data) {
	RS_HIGH;
	PORTD = data;
	E_HIGH;
	_delay_us(37);
	E_LOW;
	_delay_us(37);
}

// LCD pin out config
void pinoutSetup1602(void) {
	// Control bus	 
	DDRC |= (1 << PC0) | (1 << PC1);
	// Data bus
	DDRD |= (1 << PD0) | (1 << PD1) | (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7);
}

// 8bit mode initialization
void init8BitMode(void) {
	_delay_ms(100);
	sendCommand(0b00110000);	// Special case of 'Function Set'
	_delay_ms(5);
	sendCommand(0b00110000);	// Special case of 'Function Set'
	_delay_us(100);
	sendCommand(0b00110000);	// Special case of 'Function Set'
 
	_delay_us(100);
	sendCommand(0b00111000);	// 'Function Set' - 8bit mode, 2 lines, 5x8 font
	_delay_us(53);
	sendCommand(0b00001100);	// 'Display ON/OFF Control' display on, cursor off and not blink
	_delay_us(53);
	sendCommand(0b00000001);	// 'Clear Display'
	_delay_ms(3);
	sendCommand(0b00000110);	// 'Entry Mode Set' cursor shift to right
	_delay_ms(53);
}

int main(void) {
	pinoutSetup1602();
	init8BitMode();
 
	sendData('L');
	sendData('C');
	sendData('D');
	sendData(' ');
	sendData('1');
	sendData('6');
	sendData('0');
	sendData('2');
 
	sendCommand(0xC0);
	
	sendData('8');
	sendData('-');
	sendData('b');
	sendData('i');
	sendData('t');
	sendData(' ');
	sendData('m');
	sendData('o');
	sendData('d');
	sendData('e');
 
	while (1)
	{
		// No logic
	}
}
