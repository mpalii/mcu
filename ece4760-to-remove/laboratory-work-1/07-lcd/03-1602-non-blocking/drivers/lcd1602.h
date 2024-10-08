#ifndef LCD1602_H_
#define LCD1602_H_

#define MOVE_CURSOR_TO_POSITION_0_LINE_1 0x80
#define MOVE_CURSOR_TO_POSITION_0_LINE_2 0xC0
#define CLEAR_DISPLAY 0x01

void init_lcd1602(void);
void lcd1602_send_command(char data);
void lcd1602_print_char(char data);


void printMessage(char *msg);
void handleMessageChar(void);


#endif /* LCD1602_H_ */