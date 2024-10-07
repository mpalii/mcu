/*
 * Created: 16.12.2021 21:30:18
 * Author : Maksym Palii
 */ 

#define F_CPU (8000000)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

// Register select (RS) pin
#define RS_HIGH (PORTB |= (1 << PB4))
#define RS_LOW	(PORTB &= ~(1 << PB4))

// Enable (E) pin
#define E_HIGH	(PORTB |= (1 << PB5))
#define E_LOW	(PORTB &= ~(1 << PB5))

uint8_t mode = 0;

volatile uint64_t current_time_in_ms = 0;
const uint64_t ms_per_day = 86400000;

char upper_string[] = "23:59:59.9"; 

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
	DDRB |= (1 << PB4) | (1 << PB5);
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

// Total period: (1/8000000) * 64 * (1 + 124) = 0.001000s.
ISR(TIMER2_COMP_vect)
{
	if (current_time_in_ms >= ms_per_day) {
		current_time_in_ms = 0;
	}
	current_time_in_ms++;
}

void print(char string []) {
	for (int index = 0; string[index] != '\0'; index++) {
		sendData(string[index]);
	}
}

/*
 * Render time
 */
void renderTime(uint32_t ms)
{
	uint32_t current_time_in_seconds = ms / 1000;
	
	uint8_t hours = current_time_in_seconds / 3600;
	uint8_t minutes = (current_time_in_seconds % 3600) / 60;
	uint8_t seconds = (current_time_in_seconds % 3600) % 60;
	uint8_t deciseconds = (ms % 1000) / 100;
	
	sprintf(upper_string, "%02d:%02d:%02d.%1d", hours, minutes, seconds, deciseconds);
	
//  	sendCommand(0x01);	// Clear Display
//  	_delay_ms(3);
 	sendCommand(0x83);	// Return cursor to 3 position of line 1
// 	_delay_ms(3);

	print(upper_string);
}

void renderMode() {
	switch (mode) {
		case 0 : sendCommand(0xC0); print("                "); break;
		case 1 : sendCommand(0xC0); print("- edit seconds  "); break;
		case 2 : sendCommand(0xC0); print("- edit minutes  "); break;
		case 3 : sendCommand(0xC0); print("- edit hours    "); break;
	}
}

uint8_t mode_button_pressed_event = 0;
uint8_t control_button_pressed_event = 0;

void increaseSecond() {
	uint64_t temporaryTime = current_time_in_ms;
	temporaryTime += 1000;
	if (temporaryTime > ms_per_day) {
		temporaryTime -= ms_per_day;
	}
	temporaryTime /= 1000;
	temporaryTime *= 1000;
	current_time_in_ms = temporaryTime;
}

void increaseMinute() {
	uint64_t temporaryTime = current_time_in_ms;
	temporaryTime += 60000;
	if (temporaryTime > ms_per_day) {
		temporaryTime -= ms_per_day;
	}
	temporaryTime /= 1000;
	temporaryTime *= 1000;
	current_time_in_ms = temporaryTime;
}

void increaseHour() {
	uint64_t temporaryTime = current_time_in_ms;
	temporaryTime += 3600000;
	if (temporaryTime > ms_per_day) {
		temporaryTime -= ms_per_day;
	}
	temporaryTime /= 1000;
	temporaryTime *= 1000;
	current_time_in_ms = temporaryTime;
}

void checkModeButton() {
	// Check whether occurred mode button press event
	if ((!mode_button_pressed_event) && (~PINB & (1 << PINB1)))
	{
		// If so then increment mode (on rising edge)
		if (mode < 3) mode++;
		else mode = 0;
		mode_button_pressed_event = 1;
	}
	
	// Check whether mode button was released
	if ((mode_button_pressed_event) && (PINB & (1 << PINB1)))
	{
		mode_button_pressed_event = 0;
	}
}

void checkControlButton() {
	// Check whether occurred control button press event
	if ((!control_button_pressed_event) && (~PINB & (1 << PINB2)))
	{
		// If so then process command depends on mode (on rising edge)
		switch (mode) {
			case 1: increaseSecond(); break;
			case 2: increaseMinute(); break;
			case 3: increaseHour(); break;
		}
		control_button_pressed_event = 1;
	}
	
	// Check whether control button was released
	if ((control_button_pressed_event) && (PINB & (1 << PINB2)))
	{
		control_button_pressed_event = 0;
	}
}

int main(void)
{
	// Control buttons
	DDRB &= ~((1 << PB1) | (1 << PB2));
	PORTB |= (1 << PB1) | (1 << PB2);
	
	// Enable 8-bit Timer/Counter2; CLK/64 (from prescaler)
	TCCR2 |= (1 << CS22);
	// Set Output Compare Register OCR2 value
	OCR2 = 124;
	// Enable Clear Timer on Compare (CTC) mode
	TCCR2 |= (1 << WGM21);
	// Enable 8-bit Timer/Counter2 output compare a match interrupt
	TIMSK |= (1 << OCIE2);
	// Enable global interrupts
	sei();
	
	pinoutSetup1602();
	init8BitMode();
	
    while (1) 
    {	    
		checkModeButton();
		checkControlButton();
		
		renderTime(current_time_in_ms);
		renderMode();
    }
}

