#ifndef TASK_MANAGER_H_
#define TASK_MANAGER_H_

#include <avr/interrupt.h>
#include <stdint.h>
#include "drivers/cx56.h"
#include "drivers/adc.h"

void init_tasks(void);
void handle_tasks(void);

#endif /* TASK_MANAGER_H_ */