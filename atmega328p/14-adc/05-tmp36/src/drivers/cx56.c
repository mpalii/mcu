/**
 * @author Maksym Palii
 * @brief Seven-segment display
 * @version 2.0
*/

#include "cx56.h"
#include <stdbool.h>

#define DECIMAL_POINT_BIT   (7)
#define DIGITS_NUMBER       (4)
#define EMPTY_MASK          (0)
#define RADIX               (10)

const uint8_t DIGIT_TO_MASK_TABLE[] = {
    0b00111111, 0b00000110, 0b01011011, 0b01001111,	// 0, 1, 2, 3
    0b01100110, 0b01101101, 0b01111101, 0b00000111,	// 4, 5, 6, 7
    0b01111111, 0b01101111, 0b01110111, 0b01111100,	// 8, 9, A, B
    0b00111001, 0b01011110, 0b01111001, 0b01110001	// C, D, E, F
};

uint8_t buffer[DIGITS_NUMBER] = { };

uint8_t current_digit = 0;

void cx56_split(int16_t number)
{
    bool is_negative = false;
    if (number < 0)
    {
        number = ~number + 1;
        is_negative = true;
    }

    for (uint8_t i = 0; i < DIGITS_NUMBER; i++)
    {
        uint8_t extracted_digit = number % RADIX;
        number /= RADIX;
        buffer[i] = DIGIT_TO_MASK_TABLE[extracted_digit];

        if (i == 1)
        {
            buffer[i] |= _BV(DECIMAL_POINT_BIT);
        }

        if (i == 3 && is_negative)
        {
            buffer[i] = 0b01000000;
        }
    }
}

void cx56_render(void) 
{

    if (current_digit >= DIGITS_NUMBER) 
    {
        current_digit = 0;
    }

    // Shift digit related byte
    uint8_t digit_byte = ~_BV(current_digit);
    for (int8_t i = 7; i >= 0; i--)
    {
        GPIO_LOW(SRCLK);

        if (digit_byte & (1 << i))
        {
            _DIGIT_DISABLE(SER);
        }
        else
        {
            _DIGIT_ENABLE(SER);
        }

        GPIO_HIGH(SRCLK);
    }

    // Shift number related byte
    uint8_t number_mask = buffer[current_digit];

    for (int8_t i = 7; i >= 0; i--)
    {
        GPIO_LOW(SRCLK);

        if (number_mask & (_BV(i)))
        {
            _SEGMENT_ENABLE(SER);
        }
        else
        {
            _SEGMENT_DISABLE(SER);
        }

        GPIO_HIGH(SRCLK);
    }

    GPIO_LOW(SRCLK);

    GPIO_HIGH(RCLK);
    GPIO_LOW(RCLK);

    current_digit++;
}

void init_cx56(void)
{
    cx56_split(0);
}
