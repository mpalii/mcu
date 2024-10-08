/*
 * uart_328p.h
 *
 * Created: 24/03/2023 23:46:48
 *  Author: Maksym_Palii
 */ 


#ifndef UART_328P_H_
#define UART_328P_H_

void UART_init(uint32_t f_cpu, uint32_t baud_rate, bool double_speed_enabled);
void UART_transmit(char* data);

#endif /* UART_328P_H_ */