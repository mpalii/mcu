/*
 * @author Maksym Palii
 * @brief EEPROM
 * @version 1.0
 * @date 2023 July 01
 */

#define F_CPU (8000000UL)
#define CMD_BUFFER_SIZE 10

#include <avr/eeprom.h>
#include <stdlib.h>
#include <string.h>
#include "uart328p.h"

int main(void)
{
    uint16_t address = 0;

    // User input
    char input_command[CMD_BUFFER_SIZE];

    // Init UART
    stdin = stdout = stderr = uart_init(F_CPU, 9600, false);

    // Init message
    printf("Start up address: %04d\r\n", address);

    while (true) 
    {
        // wait for user input
        scanf("%9s", input_command);

        // print eeprom dump
        if (strcmp(input_command, "list") == 0)
        {
            for (uint16_t i = 0; i < 1023; i += 2)
            {
                //eeprom_busy_wait();
                printf("%04d : %04x\r\n", i, eeprom_read_word((const uint16_t *) i));
            }
        }


        // point to eeprom address
        else if (strncmp(input_command, "pt_", 3) == 0)
        {
            const char * address_sub_string = input_command + 3;
            long new_address = atol(address_sub_string);
            if (new_address < 0 || new_address > 1023)
            {
                printf("Address should be in range [0; 1023]\r\n");
            }
            else 
            {
                address = (uint16_t) new_address;
                printf("Current address: %04d\r\n", address);
            }
        }

        // read word
        else if (strcmp(input_command, "readword") == 0)
        {
            //eeprom_busy_wait();
            printf("%04d : %d\r\n", address, eeprom_read_word((const uint16_t *) address));
        }

        // read byte
        else if (strcmp(input_command, "readbyte") == 0)
        {
            //eeprom_busy_wait();
            uint8_t byte_dst = 0; 
            eeprom_read_block(&byte_dst, (const uint16_t *) address, sizeof(byte_dst));
            printf("%04d : %02x\r\n", address, byte_dst);
        }

        // write byte
        else if (strncmp(input_command, "wb_", 3) == 0)
        {
            const char * new_value_sub_string = input_command + 3;
            long new_value = atol(new_value_sub_string);
            if (new_value < 0 || new_value > 255)
            {
                printf("Value should be in range [0; 255]\r\n");
            }
            else
            {
                eeprom_write_block(&new_value, (uint16_t *) address, sizeof(uint8_t));
                printf("SUCCESS\r\n");
            }
        }

        // unknown command
        else
        {
            printf("UNKNOWN\r\n");
        }
    }
}
