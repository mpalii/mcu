#ifndef LCD1602_H_
#define LCD1602_H_

#include <stdbool.h>

void init_lcd1602(void);
bool pass_to_rendering(char *message);
void print(void);


#endif /* LCD1602_H_ */