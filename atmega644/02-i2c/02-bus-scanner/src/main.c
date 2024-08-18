/**
 * @author Maksym Palii
 * @brief TWI (I2C) bus check
 * @version 1.0
 * @date 2024 August 18
 */

#define F_CPU           (16000000UL)
#define ADDRESS_SPACE   (128)
 
#include "drivers/gpio.h"
#include "drivers/i2c.h"
#include "drivers/uart644.h"

void initialize(void)
{
    stdin = stdout = stderr = init_uart(F_CPU, 9600, false);
    init_gpio();
    init_i2c();
    printf("== system initialized\r\n");
}

int main(void) 
{
    initialize();

    printf("TWI(I2C) bus scanning:\r\n");
    printf("0x20 - SLA+W has been transmitted; NOT ACK has been received\r\n");
    printf("0x18 - SLA+W has been transmitted; ACK has been received\r\n");

    for (uint8_t i = 0; i < ADDRESS_SPACE; i++) 
    {
        uint8_t device_address = i << 1;

        // START
        i2c_start();

        // DEVICE ADDRESS + WRITE
        i2c_set_data(device_address & WRITE_BIT_MASK);
        i2c_continue();

        uint8_t status = i2c_get_status();

        // STOP
        i2c_stop(); 

        printf("\taddress: 0x%02X | %3d; status: 0x%02X\r\n", device_address, device_address, status);
    }

    while (true)
    {
        // NOP
    }
}
