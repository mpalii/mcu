#include <stdio.h>
#include "system/messages.h"
#include "system/metrics.h"

char text_buffer_lcd[33] = { 0 };
char text_buffer_serial[40] = { 0 };

void init_messages(void)
{
    sprintf(text_buffer_serial, READY_SERIAL_PATTERN, (mcu_operating_time / 10));
    sprintf(text_buffer_lcd, READY_LCD_PATTERN, (high_score / 10), (high_score % 10));
}