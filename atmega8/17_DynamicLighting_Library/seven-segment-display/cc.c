/*
 * Created: 06.11.2021 11:57:10
 *  Author: Maksym Palii
 */ 

#include <avr/io.h>
#include "cc.h"

// Seven-segment display pin abstraction
struct SEVEN_SEGMENT_DISPLAY_PIN
{
	volatile uint8_t * ddr;		// Only for configuration purposes
	volatile uint8_t * port;
	uint8_t pin;
};

// Segments
struct SEVEN_SEGMENT_DISPLAY_PIN seg_a = {&DDR_SEG_A, &PORT_SEG_A, PIN_SEG_A};
struct SEVEN_SEGMENT_DISPLAY_PIN seg_b = {&DDR_SEG_B, &PORT_SEG_B, PIN_SEG_B};
struct SEVEN_SEGMENT_DISPLAY_PIN seg_c = {&DDR_SEG_C, &PORT_SEG_C, PIN_SEG_C};
struct SEVEN_SEGMENT_DISPLAY_PIN seg_d = {&DDR_SEG_D, &PORT_SEG_D, PIN_SEG_D};
struct SEVEN_SEGMENT_DISPLAY_PIN seg_e = {&DDR_SEG_E, &PORT_SEG_E, PIN_SEG_E};
struct SEVEN_SEGMENT_DISPLAY_PIN seg_f = {&DDR_SEG_F, &PORT_SEG_F, PIN_SEG_F};
struct SEVEN_SEGMENT_DISPLAY_PIN seg_g = {&DDR_SEG_G, &PORT_SEG_G, PIN_SEG_G};
struct SEVEN_SEGMENT_DISPLAY_PIN seg_dp = {&DDR_SEG_DP, &PORT_SEG_DP, PIN_SEG_DP};

// Cathodes
struct SEVEN_SEGMENT_DISPLAY_PIN cc1 = {&DDR_CC1, &PORT_CC1, PIN_CC1};
struct SEVEN_SEGMENT_DISPLAY_PIN cc2 = {&DDR_CC2, &PORT_CC2, PIN_CC2};
struct SEVEN_SEGMENT_DISPLAY_PIN cc3 = {&DDR_CC3, &PORT_CC3, PIN_CC3};
struct SEVEN_SEGMENT_DISPLAY_PIN cc4 = {&DDR_CC4, &PORT_CC4, PIN_CC4};
	
// Segments group
struct SEVEN_SEGMENT_DISPLAY_PIN * segments[] = {&seg_a, &seg_b, &seg_c, &seg_d, &seg_e, &seg_f, &seg_g, &seg_dp};
// Cathodes group
struct SEVEN_SEGMENT_DISPLAY_PIN * cathodes[] = {&cc1, &cc2, &cc3, &cc4};

// Seven segment display digit index
unsigned char digit_index = 0;

/*
 * The DIGITS array stores values for displaying the digits 0-9 to a seven-segment display.
 *
 * The index of the array element is equivalent to a digit in decimal form,
 * each array element stores the state of the seven-segment port for this digit. 
 */
uint8_t digits [10] =
{
	0b00111111, //0
	0b00000110, //1
	0b01011011, //2
	0b01001111, //3
	0b01100110, //4
	0b01101101, //5
	0b01111101, //6
	0b00000111, //7
	0b01111111, //8
	0b01101111  //9
};

void disable_cathodes()
{
	for (int i = 0; i < TOTAL_DIGITS; i++)
	{
		struct SEVEN_SEGMENT_DISPLAY_PIN * cathode = cathodes[i];
		*(cathode -> port) |= (1 << (cathode -> pin));
	}
}

void enable_cathode(uint8_t index)
{
	struct SEVEN_SEGMENT_DISPLAY_PIN * cathode = cathodes[index];
	*(cathode -> port) &= ~(1 << (cathode -> pin));
}


/*
 * Utility method to extract single decimal digit from initial value (starts from 0, see digit_index)
 */
unsigned char extract_digit_in_position(uint16_t value, uint8_t digit_position)
{
	for (int i = 0; i < digit_position; i++)
	{
		value /= 10;
	}
	
	return value % 10;
}

void update_segments(uint8_t data)
{
	for (int i = 0; i < TOTAL_SEGMENTS; i++)
	{
		struct SEVEN_SEGMENT_DISPLAY_PIN * segment = segments[i];
		if (data & (1 << i))
		{
			*(segment -> port) |= (1 << (segment -> pin));
		}
		else
		{
			*(segment -> port) &= ~(1 << (segment -> pin));
		}
	}
}

void init7SEG()
{
	for (int i = 0; i < TOTAL_SEGMENTS; i++)
	{
		struct SEVEN_SEGMENT_DISPLAY_PIN * segment = segments[i];
		*(segment -> ddr) |= (1 << (segment -> pin));
	}
	for (int i = 0; i < TOTAL_DIGITS; i++)
	{
		struct SEVEN_SEGMENT_DISPLAY_PIN * cathode = cathodes[i];
		*(cathode -> ddr) |= (1 << (cathode -> pin));
	}
}

void print7SEG(uint16_t value)
{
	if (digit_index >= TOTAL_DIGITS)
	{
		digit_index = 0;
	}
	unsigned char extracted_digit = extract_digit_in_position(value, digit_index);
	uint8_t data = digits[extracted_digit];
	disable_cathodes();
	update_segments(data);
	enable_cathode(digit_index);
	digit_index++;
}
