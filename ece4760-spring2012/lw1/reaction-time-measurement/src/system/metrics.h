#ifndef METRICS_H_
#define METRICS_H_

#include <stdint.h>

extern volatile uint32_t random_seed;
extern uint16_t user_reaction_time;
extern uint16_t high_score;
extern uint16_t delay;

void init_metrics(void);

#endif /* METRICS_H_ */