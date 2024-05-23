/**
 * @author Maksym Palii
 * @brief Seven-segment display
 * @version 2.0
*/

#include "cx56.h"

#define PROPERTY_ADDRESS (0x00)
#define DIGITS_NUMBER (4)
#define RADIX (10)

void (*segment_enable)(int);
void (*segment_disable)(int);
void (*digit_enable)(int);
void (*digit_disable)(int);

void gpio_low(int pin)
{
    GPIO_LOW(pin);  
}

void gpio_high(int pin)
{
    GPIO_HIGH(pin);
}

const uint8_t DIGIT_TO_MASK_TABLE[] = {
    0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110,	    // 0, 1, 2, 3, 4
    0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111	    // 5, 6, 7, 8, 9
};

uint8_t buffer[DIGITS_NUMBER] = { };

uint8_t current_digit = 0;

void cx56_split(uint16_t number)
{
    for (uint8_t i = 0; i < DIGITS_NUMBER; i++)
    {
        uint8_t extracted_digit = number % RADIX;
        number /= RADIX;
        buffer[i] = DIGIT_TO_MASK_TABLE[extracted_digit];
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
            (*digit_disable)(SER);
        }
        else
        {
            (*digit_enable)(SER);
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
            (*segment_enable)(SER);
        }
        else
        {
            (*segment_disable)(SER);
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
    /* Set up address register */
    EEAR = PROPERTY_ADDRESS;
    /* Start eeprom read by writing EERE */
    EECR |= _BV(EERE);
    // property
    char property = EEDR;

    if (property == 'A' || property == 'a')
    {
        segment_enable = &gpio_low;
        segment_disable = &gpio_high;
        digit_enable = &gpio_high;
        digit_disable = &gpio_low;
    }
    else 
    {
        segment_enable = &gpio_high;
        segment_disable = &gpio_low;
        digit_enable = &gpio_low;
        digit_disable = &gpio_high;
    }
}
