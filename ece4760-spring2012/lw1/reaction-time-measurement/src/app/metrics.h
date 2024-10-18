#ifndef METRICS_H_
#define METRICS_H_

#include <stdint.h>

void init_metrics(void);
void increment_system_time(void);
uint32_t get_system_time(void);
uint16_t get_high_score(void);
void set_high_score(uint16_t high_score);
void set_reaction_time(uint16_t reaction_time);
uint16_t get_reaction_time(void);

#endif /* METRICS_H_ */