#ifndef UART644_H_
#define UART644_H_

#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

FILE* init_uart(uint32_t f_cpu, uint32_t baud_rate, bool double_speed_enabled);

#endif /* UART644_H_ */
