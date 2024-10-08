/*
 * uart328p.h
 *
 * Created: 12/02/2023 14:31:15
 *  Author: Maksym_Palii
 */ 


#ifndef UART328P_H_
#define UART328P_H_

FILE* UART_init(uint32_t f_cpu, uint32_t baud_rate, bool double_speed_enabled);

#endif /* UART328P_H_ */