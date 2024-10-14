#include "gpio.h"
#include "uart.h"
#include <stdbool.h>
#include <avr/eeprom.h>

#define DEFAULT_SCORE           (999U)
#define SCORE_EEPROM_ADDRESS    (0x0000)

void init_reset(void)
{
    _gpio_set_input(RESET);
    _gpio_high(RESET);     // Enable internal pull-up resistor

    uart_transmit("- Reset ready\r\n");
}

bool reset(void)
{
    bool is_default_score = (eeprom_read_word(SCORE_EEPROM_ADDRESS) == DEFAULT_SCORE);
    bool is_score_reset = (_gpio_get_input(RESET) == 0);
	
    if (is_score_reset && !is_default_score)
    {
        eeprom_write_word(SCORE_EEPROM_ADDRESS, DEFAULT_SCORE);
        return true;
    }

    return false;
}