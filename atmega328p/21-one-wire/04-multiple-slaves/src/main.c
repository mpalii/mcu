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

uint8_t sensor_rom_1[] = { 0x28, 0xdd, 0x86, 0x44, 0xd4, 0xe1, 0x3c, 0x02 };
uint8_t sensor_rom_2[] = { 0x28, 0x15, 0xa0, 0x57, 0x04, 0xe1, 0x3c, 0xf1 };

int main(void)
{
    init_gpio();
    stdin = stdout = stderr = uart_init(F_CPU, 9600, false);
    printf("Start up...\r\n");

    while (true)
    {
        // TRANSACTION 1 - begin temperature conversion (for all devices)
        onewire_reset();
        onewire_write(CMD_SKIP_ROM);
        onewire_write(CMD_CONVERT_T);
        _delay_ms(750);

        // TRANSACTION 2 - read scratchpad memory (for sensor 1)
        onewire_reset();
        onewire_write(CMD_MATCH_ROM);
        // write address
        for (uint8_t i = 0; i < 8; i++)
        {
            onewire_write(sensor_rom_1[i]);
        }
 
        onewire_write(CMD_READ_SCRATCHPAD);
        for (uint8_t i = 0; i < SCRATCHPAD_SIZE; i++)
        {
            scratchpad_buffer[i] = onewire_read();
        }

        // Print memory dump
        printf("Sensor #1\r\n");
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

        // TRANSACTION 3 - read scratchpad memory (for sensor 2)
        onewire_reset();
        onewire_write(CMD_MATCH_ROM);
        // write address
        for (uint8_t i = 0; i < 8; i++)
        {
            onewire_write(sensor_rom_2[i]);
        }
 
        onewire_write(CMD_READ_SCRATCHPAD);
        for (uint8_t i = 0; i < SCRATCHPAD_SIZE; i++)
        {
            scratchpad_buffer[i] = onewire_read();
        }

        // Print memory dump
        printf("Sensor #2\r\n");
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
