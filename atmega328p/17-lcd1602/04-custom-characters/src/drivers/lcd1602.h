#ifndef LCD1602_H_
#define LCD1602_H_

#include <stdint.h>
#include <stdbool.h>

void init_lcd1602(void);
void send_command(uint8_t command);
void send_data(uint8_t data);

#endif /* LCD1602_H_ */