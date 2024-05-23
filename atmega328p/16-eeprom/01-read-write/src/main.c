/*
 * @author Maksym Palii
 * @brief EEPROM read/write
 * @version 1.0
 * @date 2024 May 21
 */

#include <avr/io.h>
#include <stdbool.h>

#define MEMORY_ADDRESS (0x03FF)
#define VALUE (7)

void EEPROM_write(unsigned int uiAddress, unsigned char ucData);
unsigned char EEPROM_read(unsigned int uiAddress);

int main(void)
{
    DDRD = 0xFF;

    EEPROM_write(MEMORY_ADDRESS, VALUE);
    PORTD = EEPROM_read(MEMORY_ADDRESS);

    while (true) 
    { 
        // NOP
    }
}

void EEPROM_write(unsigned int uiAddress, unsigned char ucData)
{
    /* Wait for completion of previous write */
    while(EECR & (1<<EEPE))
    ;
    /* Set up address and Data Registers */
    EEAR = uiAddress;
    EEDR = ucData;
    /* Write logical one to EEMPE */
    EECR |= (1<<EEMPE);
    /* Start eeprom write by setting EEPE */
    EECR |= (1<<EEPE);
}

unsigned char EEPROM_read(unsigned int uiAddress)
{
    /* Wait for completion of previous write */
    while(EECR & (1<<EEPE))
    ;
    /* Set up address register */
    EEAR = uiAddress;
    /* Start eeprom read by writing EERE */
    EECR |= (1<<EERE);
    /* Return data from Data Register */
    return EEDR;
}