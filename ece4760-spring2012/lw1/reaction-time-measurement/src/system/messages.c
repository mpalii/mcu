#include <stdint.h>
#include <stdlib.h>
#include "system/messages.h"
#include "system/metrics.h"

char* text_buffer_lcd       = NULL;
char* text_buffer_serial    = NULL;

char* lcd_pattern_ready              =   "\b\r  Best result:\nXXX.Xms";
char* lcd_pattern_wait               =   "\b\r    Wait for\n  the signal...";
char* lcd_pattern_timeout            =   "\b\r    Timeout!\n   Try again!";
char* lcd_pattern_false_start        =   "\b\r  False start!\n   Try again!";
char* lcd_pattern_result             =   "\b\r  Your result:\nXXX.Xms";
      
char* serial_pattern_ready           =   "READY\r\n";
char* serial_pattern_wait            =   "WAIT: XXXX.Xms\r\n";
char* serial_pattern_timeout         =   "TIMEOUT\r\n";
char* serial_pattern_false_start     =   "FALSE START\r\n";
char* serial_pattern_result          =   "RESULT\r\n";

char* serial_pattern_led_enabled     =   "-LED ENABLED\r\n";
char* serial_pattern_led_disabled    =   "-LED DISABLED\r\n";
char* serial_pattern_buzzer_enabled  =   "-BUZZER ENABLED\r\n";
char* serial_pattern_buzzer_disabled =   "-BUZZER DISABLED\r\n";
char* serial_pattern_unknown         =   "-UNKNOWN\r\n";

void init_messages(void)
{
    text_buffer_serial = serial_pattern_ready;

    // populate best result LCD pattern (fractional part)
    uint8_t high_score_fractional_part = high_score % 10;
    lcd_pattern_ready[21] = high_score_fractional_part + '0';

    // populate best result LCD pattern (integer part)
    uint16_t high_score_integer_part = high_score / 10;
    lcd_pattern_ready[19] = (high_score_integer_part % 10) + '0';
    high_score_integer_part /= 10;
    lcd_pattern_ready[18] = (high_score_integer_part % 10) + '0';
    high_score_integer_part /= 10;
    lcd_pattern_ready[17] = (high_score_integer_part % 10) + '0';
    high_score_integer_part /= 10;

    text_buffer_lcd = lcd_pattern_ready;
}

char* get_serial_wait_message(void)
{
    // populate serial delay value (fractional part)
    uint8_t delay_fractional_part = delay % 10;
    serial_pattern_wait[11] = delay_fractional_part + '0';

    // populate serial delay value (integer part)
    uint16_t delay_integer_part = delay / 10;
    serial_pattern_wait[9] = (delay_integer_part % 10) + '0';
    delay_integer_part /= 10;
    serial_pattern_wait[8] = (delay_integer_part % 10) + '0';
    delay_integer_part /= 10;
    serial_pattern_wait[7] = (delay_integer_part % 10) + '0';
    delay_integer_part /= 10;
    serial_pattern_wait[6] = (delay_integer_part % 10) + '0';
    delay_integer_part /= 10;

    return serial_pattern_wait;
}

char* get_lcd_result_message(void)
{
    // populate best result LCD pattern (fractional part)
    uint8_t reaction_time_fractional_part = user_reaction_time % 10;
    lcd_pattern_result[21] = reaction_time_fractional_part + '0';

    // populate best result LCD pattern (integer part)
    uint16_t reaction_time_integer_part = user_reaction_time / 10;
    lcd_pattern_result[19] = (reaction_time_integer_part % 10) + '0';
    reaction_time_integer_part /= 10;
    lcd_pattern_result[18] = (reaction_time_integer_part % 10) + '0';
    reaction_time_integer_part /= 10;
    lcd_pattern_result[17] = (reaction_time_integer_part % 10) + '0';
    reaction_time_integer_part /= 10;

    return lcd_pattern_result;
}
