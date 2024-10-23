#ifndef MESSAGES_H_
#define MESSAGES_H_

#define READY_SERIAL_PATTERN        "%010lums-READY\r\n"
#define READY_LCD_PATTERN           "\b\r  Best result:\n%3u.%ums"

#define WAIT_SERIAL_PATTERN         "%010lums-WAIT: %u.%ums\r\n"
#define WAIT_LCD_MESSAGE            "\b\r    Wait for\n  the signal..."

#define TIMEOUT_SERIAL_PATTERN      "%010lums-TIMEOUT\r\n"
#define TIMEOUT_LCD_MESSAGE         "\b\r    Timeout!\n   Try again!"

#define FALSE_START_SERIAL_PATTERN  "%010lums-FALSE START\r\n"
#define FALSE_START_LCD_MESSAGE     "\b\r  False start!\n   Try again!"

#define RESULT_SERIAL_PATTERN       "%010lums-RESULT %u.%ums\r\n"
#define RESULT_LCD_PATTERN          "\b\r  Your result:\n%3u.%ums"

extern char text_buffer_lcd[33];
extern char text_buffer_serial[40];

void init_messages(void);

#endif /* MESSAGES_H_ */