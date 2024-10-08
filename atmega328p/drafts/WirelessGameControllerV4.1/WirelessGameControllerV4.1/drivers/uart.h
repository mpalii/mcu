/*
 * uart.h
 *
 * Created: 02/04/2023 15:51:40
 *  Author: Maksym_Palii
 */ 


#ifndef UART_H_
#define UART_H_

#include <stdbool.h>

void UART_init(uint32_t f_cpu, uint32_t baud_rate, bool double_speed_enabled);
void UART_transmit(char* data);

#endif /* UART_H_ */