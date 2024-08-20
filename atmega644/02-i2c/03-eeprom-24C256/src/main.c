/**
 * @author Maksym Palii
 * @brief TWI (I2C) with 24C02 (https://ww1.microchip.com/downloads/en/DeviceDoc/doc0670.pdf)
 * @version 1.0
 * @date 2024 August 18
 */

#define F_CPU           (16000000UL)
#define DEVICE_ADDRESS  (0xA0)      // TWI scanner shows A0 and B0 as valid addresses
 
#include "drivers/gpio.h"
#include "drivers/i2c.h"
#include "drivers/uart644.h"
#include <util/delay.h>

void initialize(void);
void print_i2c_status(void);
void byte_write_24c256(uint8_t byte, uint16_t memory_address);
uint8_t byte_read_24c256(uint16_t memory_address);

uint8_t data = 105;
uint16_t memory_address = 0x0008;

int main(void) 
{
    initialize();
    printf("EEPROM 24C256 example\r\n\r\n");

    // printf("\tInitial TWI status\r\n");
    print_i2c_status();

    printf("1. Write byte:\r\n\r\n");
    byte_write_24c256(data, memory_address);
    _delay_ms(5); // or use the device polling as in the 01-eeprom-24C02 example
    printf("2. Read byte:\r\n\r\n");
    uint8_t result = byte_read_24c256(memory_address);
    printf("3. Result is :%d\r\n\r\n", result);

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

/**
 * Byte Write (see Figure 8 from datasheet)
 */
void byte_write_24c256(uint8_t byte, uint16_t memory_address)
{
    // START
    printf("\tSTART\r\n");
    i2c_start();
    print_i2c_status();

    // DEVICE ADDRESS + WRITE
    printf("\tDEVICE ADDRESS + WRITE\r\n");
    i2c_set_data(DEVICE_ADDRESS & WRITE_BIT_MASK);
    i2c_continue();
    print_i2c_status();

    // FIRST WORD ADDRESS (MSB)
    printf("\tFIRST WORD ADDRESS (MSB)\r\n");
    i2c_set_data(memory_address >> 8);
    i2c_continue();
    print_i2c_status();

    // SECOND WORD ADDRESS (LSB)
    printf("\tSECOND WORD ADDRESS (LSB)\r\n");
    i2c_set_data(memory_address & 0xFF);
    i2c_continue();
    print_i2c_status();

    // DATA
    printf("\tDATA\r\n");
    i2c_set_data(byte);
    i2c_continue();
    print_i2c_status();

    // STOP
    printf("\tSTOP\r\n");
    i2c_stop();
    print_i2c_status();
}

/**
 * Byte Read (see Figure 11 from datasheet)
 */
uint8_t byte_read_24c256(uint16_t memory_address)
{
    // START
    printf("\tSTART\r\n");
    i2c_start();
    print_i2c_status();

    // DEVICE ADDRESS + WRITE
    printf("\tDEVICE ADDRESS + WRITE\r\n");
    i2c_set_data(DEVICE_ADDRESS & WRITE_BIT_MASK);
    i2c_continue();
    print_i2c_status();

    // FIRST WORD ADDRESS (MSB)
    printf("\tFIRST WORD ADDRESS (MSB)\r\n");
    i2c_set_data(memory_address >> 8);
    i2c_continue();
    print_i2c_status();

    // SECOND WORD ADDRESS (LSB)
    printf("\tSECOND WORD ADDRESS (LSB)\r\n");
    i2c_set_data(memory_address & 0xFF);
    i2c_continue();
    print_i2c_status();

    // REPEATED START
    printf("\tREPEATED START\r\n");
    i2c_start();
    print_i2c_status();

    // DEVICE ADDRESS + READ
    printf("\tDEVICE ADDRESS + READ\r\n");
    i2c_set_data(DEVICE_ADDRESS | READ_BIT_MASK);
    i2c_continue();
    print_i2c_status();

    // DATA
    printf("\tDATA\r\n");
    i2c_continue();
    print_i2c_status();
    uint8_t result = i2c_get_data();

    // STOP
    printf("\tSTOP\r\n");
    i2c_stop();
    print_i2c_status();

    return result;
}
