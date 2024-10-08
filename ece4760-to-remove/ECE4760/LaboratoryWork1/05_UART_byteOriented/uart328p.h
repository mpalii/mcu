/*
 * uart328p.h
 *
 * Created: 12/02/2023 12:03:10
 *  Author: Maksym_Palii
 */ 


#ifndef UART328P_H_
#define UART328P_H_

void UART_init(uint32_t f_cpu, uint32_t baud_rate, bool double_speed_enabled);
void UART_transmit(int8_t data);
int8_t UART_receive(void);

#endif /* UART328P_H_ */