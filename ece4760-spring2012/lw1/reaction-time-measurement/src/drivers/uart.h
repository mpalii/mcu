#ifndef UART_H_
#define UART_H_

void init_uart(void);
void uart_transmit(char* message);
void uart_add_to_buffer(char* message);
void uart_write(void);

#endif /* UART_H_ */