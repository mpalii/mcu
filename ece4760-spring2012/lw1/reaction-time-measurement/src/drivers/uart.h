#ifndef UART_H_
#define UART_H_

void init_uart(void);
void uart_transmit(char* message);
void uart_add_to_buffer(char* message);
void uart_write(void);

char uart_read(void);
void uart_enable_rx(void);
void uart_disable_rx(void);

#endif /* UART_H_ */