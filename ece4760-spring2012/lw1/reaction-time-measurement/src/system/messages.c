#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "system/messages.h"
#include "system/metrics.h"

char text_buffer_lcd[33]            = { 0 };
char text_buffer_serial[40]         = { 0 };

char* lcd_pattern_ready              =   "\b\r  Best result:\n%4u.%03ums";
char* lcd_pattern_wait               =   "\b\r    Wait for\n  the signal...";
char* lcd_pattern_timeout            =   "\b\r    Timeout!\n   Try again!";
char* lcd_pattern_false_start        =   "\b\r  False start!\n   Try again!";
char* lcd_pattern_result             =   "\b\r  Your result:\n%4u.%03ums";
      
char* serial_pattern_ready           =   "READY\r\n";
char* serial_pattern_wait            =   "WAIT: %5ums\r\n";
char* serial_pattern_timeout         =   "TIMEOUT\r\n";
char* serial_pattern_false_start     =   "FALSE START\r\n";
char* serial_pattern_result          =   "RESULT: %5u\r\n";

char* serial_pattern_led_enabled     =   "-LED ENABLED\r\n";
char* serial_pattern_led_disabled    =   "-LED DISABLED\r\n";
char* serial_pattern_buzzer_enabled  =   "-BUZZER ENABLED\r\n";
char* serial_pattern_buzzer_disabled =   "-BUZZER DISABLED\r\n";
char* serial_pattern_unknown         =   "-UNKNOWN\r\n";

void init_messages(void)
{
    uint16_t high_score_ms = (((uint32_t) high_score) * 16) / 1000;
    uint16_t high_score_us = (((uint32_t) high_score) * 16) % 1000;
    sprintf(text_buffer_lcd, lcd_pattern_ready, high_score_ms, high_score_us);
    sprintf(text_buffer_serial, serial_pattern_ready);
}
