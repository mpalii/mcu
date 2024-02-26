/**
 * @author Maksym Palii
 * @brief Seven-segment display with common cathode driver (4 digits) 
 * @version 1.0
*/

#define BASE 10
#define DIGIT_WITH_DECIMAL_POINT DIGIT_3

#include "cx56.h"

// Digits placed from lower to higher
const uint8_t DIGITS[] = { DIGIT_4, DIGIT_3, DIGIT_2, DIGIT_1 };

const uint8_t NUMBERS[] = {
    0b00111111, 0b00000110, 0b01011011,	0b01001111,	// 0, 1, 2, 3
    0b01100110, 0b01101101,	0b01111101,	0b00000111,	// 4, 5, 6, 7
    0b01111111, 0b01101111,	0b01110111,	0b01111100,	// 8, 9, A, B
    0b00111001,	0b01011110,	0b01111001, 0b01110001	// C, D, E, F
};

uint8_t current_digit = 0;

void render(uint16_t number) 
{
    _SEGMENT_DISABLE(SEGMENT_a);
    _SEGMENT_DISABLE(SEGMENT_b);
    _SEGMENT_DISABLE(SEGMENT_c);
    _SEGMENT_DISABLE(SEGMENT_d);
    _SEGMENT_DISABLE(SEGMENT_e);
    _SEGMENT_DISABLE(SEGMENT_f);
    _SEGMENT_DISABLE(SEGMENT_g);
    _SEGMENT_DISABLE(SEGMENT_dp);
    
    _DIGIT_DISABLE(DIGIT_1);
    _DIGIT_DISABLE(DIGIT_2);
    _DIGIT_DISABLE(DIGIT_3);
    _DIGIT_DISABLE(DIGIT_4);

    if (current_digit >= sizeof(DIGITS)) 
	{
		current_digit = 0;
	}

	for (int i = 0; i < current_digit; i++)
	{
		number /= BASE;
	}

    #ifdef NO_LEADING_ZEROS_MODE
    if (current_digit > 1 && number == 0) {
        current_digit++;
        return;
    }
    #endif
	
	number %= BASE;


    uint8_t mapped_number = NUMBERS[number];

    if (mapped_number & 0x01) _SEGMENT_ENABLE(SEGMENT_a); 
    if (mapped_number & 0x02) _SEGMENT_ENABLE(SEGMENT_b); 
    if (mapped_number & 0x04) _SEGMENT_ENABLE(SEGMENT_c); 
    if (mapped_number & 0x08) _SEGMENT_ENABLE(SEGMENT_d); 
    if (mapped_number & 0x10) _SEGMENT_ENABLE(SEGMENT_e); 
    if (mapped_number & 0x20) _SEGMENT_ENABLE(SEGMENT_f); 
    if (mapped_number & 0x40) _SEGMENT_ENABLE(SEGMENT_g); 

    uint8_t digit_pin = DIGITS[current_digit];

    if (digit_pin == DIGIT_WITH_DECIMAL_POINT) 
    {
        _SEGMENT_ENABLE(SEGMENT_dp); 
    }

    _DIGIT_ENABLE(digit_pin);

    current_digit++;
}
