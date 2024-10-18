#include "../drivers/reset.h"
#include "../drivers/uart.h"
#include <stdint.h>
#include <avr/eeprom.h>

#define DEFAULT_SCORE           (999U)
#define SCORE_EEPROM_ADDRESS    (0x0000)

static volatile uint32_t system_time;
static uint16_t high_score;
static uint16_t reaction_time;

void init_metrics(void)
{
    system_time = 0;
    reaction_time = 0;
    high_score = eeprom_read_word(SCORE_EEPROM_ADDRESS);

    if (reset_probe() && high_score != DEFAULT_SCORE)
    {
        eeprom_write_word(SCORE_EEPROM_ADDRESS, DEFAULT_SCORE);
        high_score = DEFAULT_SCORE;
        uart_transmit("RESET\r\n");
    }

    uart_transmit("- Metrics ready\r\n");
}

void increment_system_time(void)
{
    system_time++;
}

uint32_t get_system_time(void)
{
    return system_time;
}

uint16_t get_high_score(void)
{
    return high_score;
}

void set_high_score(uint16_t new_high_score)
{
    high_score = new_high_score;
}

void set_reaction_time(uint16_t user_reaction)
{
    reaction_time = user_reaction;
}

uint16_t get_reaction_time(void)
{
    return reaction_time;
}
