/**
 * @author Maksym Palii
 * @brief Seven-segment display with common cathode driver (4 digits) 
 * @version 1.0
*/

#include "cc56.h"
#include "gpio.h"

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
    GPIO_LOW(SEGMENT_a);
    GPIO_LOW(SEGMENT_b);
    GPIO_LOW(SEGMENT_c);
    GPIO_LOW(SEGMENT_d);
    GPIO_LOW(SEGMENT_e);
    GPIO_LOW(SEGMENT_f);
    GPIO_LOW(SEGMENT_g);
    GPIO_LOW(SEGMENT_dp);
    
    GPIO_HIGH(DIGIT_1);
    GPIO_HIGH(DIGIT_2);
    GPIO_HIGH(DIGIT_3);
    GPIO_HIGH(DIGIT_4);

    if (current_digit >= sizeof(DIGITS)) 
	{
		current_digit = 0;
	}

	for (int i = 0; i < current_digit; i++)
	{
		number /= 10;
	}
	
	number %= 10;


    uint8_t mapped_number = NUMBERS[number];

    if (mapped_number & 0x01) GPIO_HIGH(SEGMENT_a); 
    if (mapped_number & 0x02) GPIO_HIGH(SEGMENT_b); 
    if (mapped_number & 0x04) GPIO_HIGH(SEGMENT_c); 
    if (mapped_number & 0x08) GPIO_HIGH(SEGMENT_d); 
    if (mapped_number & 0x10) GPIO_HIGH(SEGMENT_e); 
    if (mapped_number & 0x20) GPIO_HIGH(SEGMENT_f); 
    if (mapped_number & 0x40) GPIO_HIGH(SEGMENT_g); 
    if (mapped_number & 0x80) GPIO_HIGH(SEGMENT_dp); 

    GPIO_LOW(DIGITS[current_digit]);

    current_digit++;
}
