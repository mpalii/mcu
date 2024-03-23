/**
 * @author Maksym Palii
 * @brief Dynamic lighting, 4-digits seven-segment display with common cathode
 * @version 1.0
 * @date 2024 February 20
 */

#define F_CPU 8000000UL
#define DELAY 1000

#include <stdbool.h>
#include <util/delay.h>
#include "drivers/sn74hc595.h"
#include "drivers/gpio.h"

uint16_t alphabet[] = 
{
    0b0110100111111001,     // a
    
    0b1000111010011110,     // b

    0b1111100010001111,     // c
    0b1110100110011110,     // d
    0b1111110010001111,     // e
    0b1111100011101000,     // f
    0b1110100010011111,     // g
    0b1001111110011001,     // h
    0b1111011001101111,     // i
    0b1111000110010110,     // j
    0b1001111011101011,     // k
    0b1000100010001111,     // l 
    0b1011111111011001,     // m
    0b1001110110111001,     // n
    0b1111100110011111,     // o
    0b1111100111111000,     // p
    0b1111100110111111,     // q
    0b1111100111101011,     // r
    0b1111110000111111,     // s
    0b1111011001100110,     // t
    0b1001100110011111,     // u
    0b1001100110010110,     // v
    0b1001101111111101,     // w
    0b1001011001101001,     // x
    0b1001111101100110,     // y
    0b1111001111001111      // z
};

int main(void)
{
    gpio_init();

    char *message  = "b";
    
    uint16_t i = 0;
    while (message[i] != '\0')
    {
        if (message[i] == ' ') 
        {
            shift_data(0);
        }
        else
        {
            uint8_t letter = message[i] - 97;
            shift_data(alphabet[letter]);
        }

        i++;
        _delay_ms(DELAY);
    }

    shift_data(0);

    while (true)
    {
        // NOP
    }
}
