#ifndef TIMER1_H_
#define TIMER1_H_

#include <stdint.h>

void init_timer1(void);
void timer1_start(void);
uint16_t timer1_stop(void);

#endif /* TIMER1_H_ */