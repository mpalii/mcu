#ifndef SERIAL_H_
#define SERIAL_H_

#define SERIAL_DDR      (DDRB)
#define SERIAL_PORT     (PORTB)
#define SERIAL_PIN      (PB0)

#if !defined(F_CPU)
/* terminate compilation if not specified */
# error "F_CPU must be specified for \"serial.h\""
#endif

#if !defined(BAUD_RATE)
/* terminate compilation if not specified */
# error "BAUD_RATE must be specified for \"serial.h\""
#endif

#define SERIAL_DELAY (1000000.0 / BAUD_RATE)

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>

void serial_init(void)
{
    SERIAL_DDR |= _BV(SERIAL_PIN);
    SERIAL_PORT |= _BV(SERIAL_PIN);
}

void serial_transmit_byte(int8_t byte)
{
    int8_t mask = 1;

    // START BIT
    SERIAL_PORT &= ~_BV(SERIAL_PIN);
    _delay_us(SERIAL_DELAY);

    // DATA
    for (uint8_t i = 0; i < 8; i++)
    {
        if (byte & (mask << i))
        {
            SERIAL_PORT |= _BV(SERIAL_PIN);
        }
        else
        {
            SERIAL_PORT &= ~_BV(SERIAL_PIN);
        }

        _delay_us(SERIAL_DELAY);
    }
    
    // STOP BIT
    SERIAL_PORT |= _BV(SERIAL_PIN);
    _delay_us(SERIAL_DELAY);
}

void serial_transmit(char* array)
{
    uint16_t i = 0;

    // Send characters until zero byte
    while (array[i] != '\0')
    {
        serial_transmit_byte(array[i++]);
    }
}

#endif /* SERIAL_H_ */