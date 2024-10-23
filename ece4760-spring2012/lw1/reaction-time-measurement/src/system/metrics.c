#include <stdint.h>
#include <avr/eeprom.h>
#include "drivers/reset.h"
#include "drivers/uart.h"

volatile uint32_t mcu_operating_time;
uint16_t user_reaction_time;
uint16_t delay;
uint16_t high_score;

void init_metrics(void)
{
    mcu_operating_time = 0;
    user_reaction_time = 0;
    delay = 0;
    high_score = eeprom_read_word(SCORE_EEPROM_ADDRESS);

    if (reset_probe() && high_score != DEFAULT_SCORE)
    {
        uart_transmit("- HIGH SCORE reset...\r\n");
        eeprom_write_word(SCORE_EEPROM_ADDRESS, DEFAULT_SCORE);
        high_score = DEFAULT_SCORE;
    }

    uart_transmit("- METRICS ready\r\n");
}