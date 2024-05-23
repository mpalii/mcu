#ifndef CX56_H_
#define CX56_H_

#include "gpio.h"
#include <stdint.h>

void init_cx56(void);
void cx56_split(uint16_t number);
void cx56_render(void);

#endif /* CX56_H_ */