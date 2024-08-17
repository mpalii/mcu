/**
 * @author Maksym Palii
 * @brief TWI (I2C) with 24C02 (https://ww1.microchip.com/downloads/en/DeviceDoc/doc0180.pdf)
 * @version 1.0
 * @date 2024 August 18
 */

#define F_CPU (16000000UL)
#define DEVICE_ADDRESS (0b10100000)
 
#include "drivers/gpio.h"
#include "drivers/i2c.h"
#include <util/delay.h>

void byte_write_24c02(uint8_t byte, uint8_t memory_address);
uint8_t byte_read_24c02(uint8_t memory_address);
inline void trace_to_port_a(uint8_t data);
inline void trace_to_port_b(uint8_t data);
inline void trace_to_port_d(uint8_t data);
uint8_t poll_till_busy(void);

uint8_t data = 105;
uint8_t memory_address = 0x0F;

int main(void) 
{
    init_gpio();
    init_i2c();

    // trace_to_port_a(i2c_get_status());                  // 0xF8 Initial status
    byte_write_24c02(data, memory_address);
    trace_to_port_d(poll_till_busy());                  // 0b00100100 or 36
    trace_to_port_b(byte_read_24c02(memory_address));   // 0b01101001 or 105

    while (true)
    {
        // NOP
    }
}

inline void trace_to_port_a(uint8_t data)
{
    PORTA = data;
}

inline void trace_to_port_b(uint8_t data)
{
    PORTB = data;
}

inline void trace_to_port_d(uint8_t data)
{
    PORTD = data;
}

uint8_t poll_till_busy(void)
{
    uint8_t poll_counter = 0;

    while (true)
    {
        poll_counter++;
        trace_to_port_d(poll_counter);

        // START
        i2c_start();

        // DEVICE ADDRESS + WRITE
        i2c_set_data(DEVICE_ADDRESS & WRITE_BIT_MASK);
        i2c_continue();

        uint8_t result = i2c_get_status();

        // STOP
        i2c_stop();

        if (result == 0x18)
        {
            return poll_counter;
        }        
    }
}

/**
 * Byte Write (see Figure 8 from datasheet)
 */
void byte_write_24c02(uint8_t byte, uint8_t memory_address)
{
    // START
    i2c_start();
    // trace_to_port_a(i2c_get_status());      // 0x08 A START condition has been transmitted

    // DEVICE ADDRESS + WRITE
    i2c_set_data(DEVICE_ADDRESS & WRITE_BIT_MASK);
    i2c_continue();
    // trace_to_port_a(i2c_get_status());      // 0x18 SLA+W has been transmitted; ACK has been received

    // WORD ADDRESS
    i2c_set_data(memory_address);
    i2c_continue();
    // trace_to_port_a(i2c_get_status());      // 0x28 Data byte has been transmitted; ACK has been received

    // DATA
    i2c_set_data(byte);
    i2c_continue();
    // trace_to_port_a(i2c_get_status());      // 0b28 Data byte has been transmitted; ACK has been received

    // STOP
    i2c_stop();
    // trace_to_port_a(i2c_get_status());      // 0xF8 Initial status
}

/**
 * Byte Read (see Figure 11 from datasheet)
 */
uint8_t byte_read_24c02(uint8_t memory_address)
{
    // START
    i2c_start();
    // trace_to_port_a(i2c_get_status());      // 0x08 A START condition has been transmitted

    // DEVICE ADDRESS + WRITE
    i2c_set_data(DEVICE_ADDRESS & WRITE_BIT_MASK);
    i2c_continue();
    // trace_to_port_a(i2c_get_status());      // 0x18 SLA+W has been transmitted; ACK has been received

    // WORD ADDRESS
    i2c_set_data(memory_address);
    i2c_continue();
    // trace_to_port_a(i2c_get_status());      // 0x28 Data byte has been transmitted; ACK has been received

    // REPEATED START
    i2c_start();
    // trace_to_port_a(i2c_get_status());      // 0x10 A repeated START condition has been transmitted

    // DEVICE ADDRESS + READ
    i2c_set_data(DEVICE_ADDRESS | READ_BIT_MASK);
    i2c_continue();
    // trace_to_port_a(i2c_get_status());      // 0x40 SLA+R has been transmitted; ACK has been received

    // DATA
    i2c_continue();
    uint8_t result = i2c_get_data();
    // trace_to_port_a(i2c_get_status());      // 0x58 Data byte has been received; NOT ACK has been returned

    // STOP
    i2c_stop();
    // trace_to_port_a(i2c_get_status());      // 0xF8 Initial status

    return result;
}
