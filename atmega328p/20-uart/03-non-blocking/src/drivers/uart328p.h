#ifndef UART328P_H_
#define UART328P_H_

#include <avr/io.h>
#include <stdbool.h>
#include <stddef.h>

void uart_init(uint32_t f_cpu, uint32_t baud_rate, bool double_speed_enabled);
char* uart_receive_data(void);
void uart_transmit_data(char* data);
void uart_set_ready_for_recieve(void);

// Interrupt specific methods
void uart_receive(void);
void uart_transmit(void);

#endif /* UART328P_H_ */