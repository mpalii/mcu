/*
 * @author Maksym Palii
 * @brief DS18B20
 * @version 1.0
 * @date 2024 August 10
 */

#define SCRATCHPAD_SIZE     (9)

#include "drivers/gpio.h"
#include "drivers/uart328p.h"
#include "drivers/onewire.h"

void print_temperature(uint8_t temperature_lsb, uint8_t temperature_msb);

uint8_t scratchpad_buffer[SCRATCHPAD_SIZE] = { 0 };

int main(void)
{
    init_gpio();
    stdin = stdout = stderr = uart_init(F_CPU, 9600, false);
    printf("Start up...\r\n");

    while (true)
    {
        // TRANSACTION 1 - begin temperature conversion
        onewire_reset();
        onewire_write(CMD_SKIP_ROM);
        onewire_write(CMD_CONVERT_T);
        _delay_ms(750);

        // TRANSACTION 2 - read scratchpad memory
        onewire_reset();
        onewire_write(CMD_SKIP_ROM);
        onewire_write(CMD_READ_SCRATCHPAD);
        for (uint8_t i = 0; i < SCRATCHPAD_SIZE; i++)
        {
            scratchpad_buffer[i] = onewire_read();
        }

        // Print memory dump
        printf("TEMPERATURE LSB:    0x%02X\r\n", scratchpad_buffer[0]);
        printf("TEMPERATURE MSB:    0x%02X\r\n", scratchpad_buffer[1]);
        printf("TH/USER BYTE 1:     0x%02X\r\n", scratchpad_buffer[2]);
        printf("TH/USER BYTE 2:     0x%02X\r\n", scratchpad_buffer[3]);
        printf("CONFIG:             0x%02X\r\n", scratchpad_buffer[4]);
        printf("RESERVED:           0x%02X\r\n", scratchpad_buffer[5]);
        printf("RESERVED:           0x%02X\r\n", scratchpad_buffer[6]);
        printf("RESERVED:           0x%02X\r\n", scratchpad_buffer[7]);
        printf("CRC:                0x%02X\r\n", scratchpad_buffer[8]);
        print_temperature(scratchpad_buffer[0], scratchpad_buffer[1]);
        printf("\r\n");
    }
}

void print_temperature(uint8_t temperature_lsb, uint8_t temperature_msb)
{
    uint16_t temperature = temperature_lsb | (temperature_msb << 8);

    int8_t integer_part = temperature >> 4;
    int8_t fraction_part =  (temperature & 8000) ? (-1 * temperature) : temperature;
    fraction_part = ((fraction_part & 0x0f) * 10) / 16;

    printf("Temperature: %3d.%1dºC\r\n", integer_part, fraction_part);
}
