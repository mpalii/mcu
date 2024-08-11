/*
 * @author Maksym Palii
 * @brief DS18B20
 * @version 1.0
 * @date 2024 August 11
 */

#define SCRATCHPAD_SIZE     (9)

#include "drivers/gpio.h"
#include "drivers/uart328p.h"
#include "drivers/onewire.h"

uint16_t poll_conversion_result_from_sensor(uint8_t *sensor_address, uint8_t sensor_number);
uint8_t calculate_crc(uint8_t *scratchpad_buffer);
void print_temperature(uint16_t temperature);

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
        uint16_t temperature_1 = poll_conversion_result_from_sensor(sensor_rom_1, 1);
        print_temperature(temperature_1);
        printf("\r\n");

        // TRANSACTION 3 - read scratchpad memory (for sensor 2)
        uint16_t temperature_2 = poll_conversion_result_from_sensor(sensor_rom_2, 2);
        print_temperature(temperature_2);
        printf("\r\n");
    }
}

uint16_t poll_conversion_result_from_sensor(uint8_t *sensor_address, uint8_t sensor_number)
{
    onewire_reset();
    onewire_write(CMD_MATCH_ROM);
    // write address
    for (uint8_t i = 0; i < 8; i++)
    {
        onewire_write(sensor_address[i]);
    }

    onewire_write(CMD_READ_SCRATCHPAD);
    for (uint8_t i = 0; i < SCRATCHPAD_SIZE; i++)
    {
        scratchpad_buffer[i] = onewire_read();
    }

    // Print memory dump
    printf("Sensor #%d\r\n", sensor_number);
    printf("TEMPERATURE LSB:    0x%02X\r\n", scratchpad_buffer[0]);
    printf("TEMPERATURE MSB:    0x%02X\r\n", scratchpad_buffer[1]);
    printf("TH/USER BYTE 1:     0x%02X\r\n", scratchpad_buffer[2]);
    printf("TH/USER BYTE 2:     0x%02X\r\n", scratchpad_buffer[3]);
    printf("CONFIG:             0x%02X\r\n", scratchpad_buffer[4]);
    printf("RESERVED:           0x%02X\r\n", scratchpad_buffer[5]);
    printf("RESERVED:           0x%02X\r\n", scratchpad_buffer[6]);
    printf("RESERVED:           0x%02X\r\n", scratchpad_buffer[7]);
    printf("====CRC:            0x%02X\r\n", scratchpad_buffer[8]);
    
    uint8_t crc = calculate_crc(scratchpad_buffer);
    printf("====Calculated CRC: 0x%02X\r\n", crc);

    return scratchpad_buffer[0] | (scratchpad_buffer[1] << 8);
}

uint8_t calculate_crc(uint8_t *scratchpad_buffer)
{
    uint8_t crc = 0;

    for (uint8_t i = 0; i < SCRATCHPAD_SIZE - 1; i++)
    {
        uint8_t byte = scratchpad_buffer[i];
        // for (uint8_t j = 0; j < 8; j++)
        // {
        //     uint8_t mix = (crc ^ byte) & 1;
        //     crc >>= 1;
        //     if (mix) crc ^= 0x8C;
        //     byte >>= 1;
        // }

        for (uint8_t j = 0; j < 8; j++)
        {
            uint8_t xor = crc ^ byte;
            crc >>= 1;
            byte >>= 1;
            
            if (xor & 1)
            {
                crc ^= 0x8C;
            }
        }
    }
    
    return crc;
}

void print_temperature(uint16_t temperature)
{
    int8_t integer_part = temperature >> 4;
    int8_t fraction_part =  (temperature & 8000) ? (-1 * temperature) : temperature;
    fraction_part = ((fraction_part & 0x0f) * 10) / 16;

    printf("Temperature: %3d.%1dºC\r\n", integer_part, fraction_part);
}
