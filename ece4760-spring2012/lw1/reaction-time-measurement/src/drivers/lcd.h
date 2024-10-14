#ifndef LCD1602_H_
#define LCD1602_H_

void init_lcd(void);
void lcd_add_to_rendering(char *message);
void lcd_render(void);

#endif /* LCD1602_H_ */