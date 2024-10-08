/*
 * uart328p.h
 *
 * Created: 12/02/2023 17:46:52
 *  Author: Maksym_Palii
 */ 


#ifndef UART328P_H_
#define UART328P_H_

void UART_init(uint32_t f_cpu, uint32_t baud_rate, bool double_speed_enabled);
void UART_receive(void);
int8_t* UART_receive_data(void);
void UART_transmit(void);
void UART_transmit_data(int8_t* data);

#endif /* UART328P_H_ */