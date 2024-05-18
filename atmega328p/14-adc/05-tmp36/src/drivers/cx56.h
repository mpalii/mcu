#ifndef CX56_H_
#define CX56_H_

#include "gpio.h"
#include <stdint.h>

// Common cathode mode
#define _SEGMENT_ENABLE(GPIO) GPIO_HIGH(GPIO)
#define _SEGMENT_DISABLE(GPIO) GPIO_LOW(GPIO)
#define _DIGIT_ENABLE(GPIO) GPIO_LOW(GPIO)
#define _DIGIT_DISABLE(GPIO) GPIO_HIGH(GPIO)

void init_cx56(void);
void cx56_split(int16_t number);
void cx56_render(void);

#endif /* CX56_H_ */