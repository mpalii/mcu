/*
 * @author Maksym Palii
 * @brief DS18B20
 * @version 1.0
 * @date 2024 August 10
 */

#include "drivers/gpio.h"
#include "drivers/uart328p.h"
#include "drivers/onewire.h"

uint8_t rom_code[8] = { 0 };
bool is_previously_identified_device;

int main(void)
{
    init_gpio();
    stdin = stdout = stderr = uart_init(F_CPU, 9600, false);
    printf("Start up...\r\n");

    // to make flag correct at the beginning
    /* just for estetic */
    is_previously_identified_device = onewire_reset() ? false : true;

    while (true)
    {
        bool is_device_present = onewire_reset();

        if(is_device_present && !is_previously_identified_device)
        {
            onewire_write(CMD_READ_ROM);

            // read ROM
            for (uint8_t i = 0; i < sizeof(rom_code); i++)
            {
                rom_code[i] = onewire_read();
            }

            // print ROM
            printf("{ 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x }\r\n", 
                rom_code[0], rom_code[1], rom_code[2], rom_code[3], rom_code[4], rom_code[5], rom_code[6], rom_code[7]
            );

            // reset flag
            is_previously_identified_device = true;
        }

        else if (!is_device_present && is_previously_identified_device)
        {
            is_previously_identified_device = false;
            printf("Onewire bus is empty\r\n");
        }

        // short delay for "debounce"
        _delay_ms(500);
    }
}