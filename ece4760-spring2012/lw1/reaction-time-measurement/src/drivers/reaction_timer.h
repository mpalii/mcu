#ifndef TIMER1_H_
#define TIMER1_H_

#include <stdint.h>

void init_reaction_timer(void);
void reaction_timer_start(void);
uint16_t reaction_timer_stop(void);

#endif /* TIMER1_H_ */