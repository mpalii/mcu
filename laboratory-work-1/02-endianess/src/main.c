/*
 * @author Maksym Palii
 * @brief Endianess: Little
 * @version 1.0
 * @date 2023 May 23
 */

#include <avr/io.h>
#include <stdbool.h>

void init_io_pins(void)
{
    // Configure data direction for pins 0-7 (port D) as OUTPUT
    DDRD = 0xFF;

    // Configure data direction for pins 0-7 (port B) as OUTPUT
    DDRB = 0xFF;
}

int main(void)
{
    init_io_pins();
    
    // MSB[0000 0010] LSB[0100 0000] or (512 + 64)
    uint16_t value = 576;

    // get pointer of value
    uint8_t *first_byte_address = (uint8_t *) &value;

    // show results
    PORTB = *first_byte_address;        // LSB[0100 0000]
    PORTD = *(first_byte_address + 1);  // MSB[0000 0010]

    while (true)
    {
        // NOP
    }
}

