#ifndef UART328P_H_
#define UART328P_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

FILE* uart_init(uint32_t f_cpu, uint32_t baud_rate, bool double_speed_enabled);

#endif /* UART328P_H_ */
