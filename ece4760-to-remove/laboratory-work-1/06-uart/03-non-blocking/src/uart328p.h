#ifndef UART328P_H_
#define UART328P_H_

#include <avr/io.h>
#include <stdbool.h>
#include <stddef.h>

void uart_init(uint32_t f_cpu, uint32_t baud_rate, bool double_speed_enabled);
void uart_receive(void);
char* uart_receive_data(void);
void uart_transmit(void);
void uart_transmit_data(char* data);

#endif /* UART328P_H_ */