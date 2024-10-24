#ifndef TIMER2_H_
#define TIMER2_H_

#include <stdbool.h>

void init_buzzer(void);
void buzzer_on(void);
void buzzer_off(void);
bool buzzer_toggle_enable_flag(void);

#endif /* TIMER2_H_ */