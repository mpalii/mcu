#ifndef MESSAGES_H_
#define MESSAGES_H_

extern char text_buffer_lcd[33];
extern char text_buffer_serial[40];

extern char* lcd_pattern_ready;
extern char* lcd_pattern_wait;
extern char* lcd_pattern_timeout;
extern char* lcd_pattern_false_start;
extern char* lcd_pattern_result;
      
extern char* serial_pattern_ready;
extern char* serial_pattern_wait;
extern char* serial_pattern_timeout;
extern char* serial_pattern_false_start;
extern char* serial_pattern_result;

extern char* serial_pattern_led_enabled;
extern char* serial_pattern_led_disabled;
extern char* serial_pattern_buzzer_enabled;
extern char* serial_pattern_buzzer_disabled;
extern char* serial_pattern_unknown;


void init_messages(void);

#endif /* MESSAGES_H_ */