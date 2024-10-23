#include <avr/eeprom.h>
#include <stdbool.h>
#include <stdint.h>

static uint16_t score_to_save;
static uint8_t data_index = 0;
static bool busy = false;

void eeprom_write_score(void)
{	
    if (busy && eeprom_is_ready())
    {
        uint8_t *first_byte_address = (uint8_t *) &score_to_save;
		
        if (data_index == 0)
        {
            eeprom_update_byte((uint8_t*) SCORE_EEPROM_ADDRESS, *first_byte_address);
            data_index = 1;
        }
        else if (data_index == 1)
        {
            eeprom_update_byte((uint8_t*) (SCORE_EEPROM_ADDRESS + 1), *(first_byte_address + 1));
            data_index = 0;
            busy = false;
        }
    }
}

void eeprom_save_score(uint16_t score)
{
    if (!busy)
    {
        score_to_save = score;
        busy = true;
    }
}