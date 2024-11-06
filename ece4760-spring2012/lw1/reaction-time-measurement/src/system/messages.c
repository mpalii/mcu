#include <stdint.h>
#include <stdlib.h>
#include "system/messages.h"
#include "system/metrics.h"

char* text_buffer_lcd       = NULL;
char* text_buffer_serial    = NULL;

char* lcd_pattern_ready              =   "\b\r  Best result:\nXXXXX";
char* lcd_pattern_wait               =   "\b\r    Wait for\n  the signal...";
char* lcd_pattern_timeout            =   "\b\r    Timeout!\n   Try again!";
char* lcd_pattern_false_start        =   "\b\r  False start!\n   Try again!";
char* lcd_pattern_result             =   "\b\r  Your result:\nXXXXX";
      
char* serial_pattern_ready           =   "READY\r\n";
char* serial_pattern_wait            =   "WAIT: XXXXXms\r\n";
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

    // populate best result LCD pattern
    uint16_t best_result = high_score;

    lcd_pattern_ready[21] = (best_result % 10) + '0';
    best_result /= 10;
    lcd_pattern_ready[20] = (best_result % 10) + '0';
    best_result /= 10;
    lcd_pattern_ready[19] = (best_result % 10) + '0';
    best_result /= 10;
    lcd_pattern_ready[18] = (best_result % 10) + '0';
    best_result /= 10;
    lcd_pattern_ready[17] = (best_result % 10) + '0';

    text_buffer_lcd = lcd_pattern_ready;
}

char* get_serial_wait_message(void)
{
    // populate serial delay value
    uint16_t delay_value = delay;

    serial_pattern_wait[10] = (delay_value % 10) + '0';
    delay_value /= 10;
    serial_pattern_wait[9] = (delay_value % 10) + '0';
    delay_value /= 10;
    serial_pattern_wait[8] = (delay_value % 10) + '0';
    delay_value /= 10;
    serial_pattern_wait[7] = (delay_value % 10) + '0';
    delay_value /= 10;
    serial_pattern_wait[6] = (delay_value % 10) + '0';

    return serial_pattern_wait;
}

char* get_lcd_result_message(void)
{
    // populate result LCD pattern
    uint16_t reaction_time_value = user_reaction_time;

    lcd_pattern_result[21] = (reaction_time_value % 10) + '0';
    reaction_time_value /= 10;
    lcd_pattern_result[20] = (reaction_time_value % 10) + '0';
    reaction_time_value /= 10;
    lcd_pattern_result[19] = (reaction_time_value % 10) + '0';
    reaction_time_value /= 10;
    lcd_pattern_result[18] = (reaction_time_value % 10) + '0';
    reaction_time_value /= 10;
    lcd_pattern_result[17] = (reaction_time_value % 10) + '0';

    return lcd_pattern_result;
}
