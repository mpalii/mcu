/**
 * @author Maksym Palii
 * @brief TWI (I2C) with SHT3x Single Shot Data Acquisition Mode, clock stretching 
 * (https://sensirion.com/media/documents/213E6A3B/63A5A569/Datasheet_SHT3x_DIS.pdf)
 * @version 1.0
 * @date 2024 August 20
 */

#define F_CPU           (16000000UL)
#define DEVICE_ADDRESS  (0x88)      // TWI scanner shows 00 and 88 as valid addresses
#define CMD_RL_CSE      (0x2C10)    // Repeatability - LOW with clock stretching ENABLED
 
#include "drivers/gpio.h"
#include "drivers/i2c.h"
#include "drivers/uart644.h"
#include <util/delay.h>

void initialize(void);
void print_i2c_status(void);
void init_sht3x(void);
struct SHT3xResult read_sht3x(void);
void print_sht3x_result(struct SHT3xResult result);

struct SHT3xResult
{
    uint16_t raw_temperature;
    uint8_t temperature_crc;
    uint16_t raw_humidity;
    uint8_t humidity_crc;
};

int main(void) 
{
    initialize();
    printf("Temperature/humidity sensor SHT3X example\r\n\r\n");

    print_i2c_status();

    printf("1. Configure SHT3X with Single Shot Data Acquisition Mode and enabled clock stretching:\r\n\r\n");
    init_sht3x();
    printf("2. Init measurement and read results:\r\n\r\n");
    struct SHT3xResult measurement_result = read_sht3x();
    printf("3. Measurement results:\r\n\r\n");
    print_sht3x_result(measurement_result);

    while (true)
    {
        // NOP
    }
}

void initialize(void)
{
    init_gpio();
    stdin = stdout = stderr = init_uart(F_CPU, 9600, false);
    init_i2c();
}

void print_i2c_status(void)
{
    uint8_t i2c_status = i2c_get_status();
    printf("======= TWSR:0x%02X\r\n\r\n", i2c_status);
}


void init_sht3x(void)
{
    /**
     * Single Shot Data Acquisition Mode
     */
    // START
    printf("\tSTART\r\n");
    i2c_start();
    print_i2c_status();

    // DEVICE ADDRESS + WRITE
    printf("\tDEVICE ADDRESS + WRITE\r\n");
    i2c_set_data(DEVICE_ADDRESS & WRITE_BIT_MASK);
    i2c_continue_no_ack();
    print_i2c_status();

    // COMMAND (MSB)
    printf("\tCOMMAND (MSB)\r\n");
    i2c_set_data(CMD_RL_CSE >> 8);
    i2c_continue_no_ack();
    print_i2c_status();

    // COMMAND (LSB)
    printf("\tCOMMAND (LSB)\r\n");
    i2c_set_data(CMD_RL_CSE & 0xFF);
    i2c_continue_no_ack();
    print_i2c_status();

    // STOP
    printf("\tSTOP\r\n");
    i2c_stop();
    print_i2c_status();
}

struct SHT3xResult read_sht3x(void)
{
    struct SHT3xResult result;

    /** 
     * Measurement
     */
    // START
    printf("\tSTART\r\n");
    i2c_start();
    print_i2c_status();

    // DEVICE ADDRESS + READ
    printf("\tDEVICE ADDRESS + READ\r\n");
    i2c_set_data(DEVICE_ADDRESS | READ_BIT_MASK);
    i2c_continue_no_ack();
    print_i2c_status();

    // SCL pulled low

    // TEMPERATURE MSB
    printf("\tTEMPERATURE MSB\r\n");
    i2c_continue_ack();
    print_i2c_status();
    result.raw_temperature = i2c_get_data() << 8;

    // TEMPERATURE LSB
    printf("\tTEMPERATURE LSB\r\n");
    i2c_continue_ack();
    print_i2c_status();
    result.raw_temperature |= i2c_get_data();

    // TEMPERATURE CRC
    printf("\tTEMPERATURE CRC\r\n");
    i2c_continue_ack();
    print_i2c_status();
    result.temperature_crc = i2c_get_data();

    // HUMIDITY MSB
    printf("\tHUMIDITY MSB\r\n");
    i2c_continue_ack();
    print_i2c_status();
    result.raw_humidity = i2c_get_data() << 8;

    // HUMIDITY LSB
    printf("\tHUMIDITY LSB\r\n");
    i2c_continue_ack();
    print_i2c_status();
    result.raw_humidity |= i2c_get_data();

    // HUMIDITY CRC
    printf("\tHUMIDITY CRC\r\n");
    i2c_continue_no_ack();
    print_i2c_status();
    result.humidity_crc = i2c_get_data();

    // STOP
    printf("\tSTOP\r\n");
    i2c_stop();
    print_i2c_status();

    return result;
}

void print_sht3x_result(struct SHT3xResult result)
{
    // results
    int8_t converted_temperature = (int8_t) ((int32_t) 175 * result.raw_temperature / 0xFFFF) - 45;
    int8_t converted_humidity = (int8_t) ((int32_t) 100 * result.raw_humidity / 0xFFFF);

    printf("Raw temperature: 0x%4X, crc: 0x%X\r\n", result.raw_temperature, result.temperature_crc);
    printf("Converted temperature: %dºC\r\n", converted_temperature);
    printf("Raw humidity: 0x%4X, crc: 0x%X\r\n", result.raw_humidity, result.humidity_crc);
    printf("Converted humidity: %d%%\r\n", converted_humidity);
}
