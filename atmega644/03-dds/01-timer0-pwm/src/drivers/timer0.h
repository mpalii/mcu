#ifndef TIMER0_H_
#define TIMER0_H_

#include <stdint.h>

void init_timer0(void);
void set_duty(uint8_t duty);

#endif /* TIMER0_H_ */