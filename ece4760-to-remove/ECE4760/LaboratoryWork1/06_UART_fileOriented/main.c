/*
 * 06_UART_arrayOriented.c
 *
 * Created: 12/02/2023 14:21:32
 * Author : Maksym_Palii
 */

#define F_CPU 8000000UL
#define BUFFER_SIZE 41

#include <stdio.h>
#include <stdbool.h>
#include "uart328p.h"

volatile char input_command[BUFFER_SIZE];

int main(void)
{
    stdin = stdout = stderr = UART_init(F_CPU, 9600, false);
    printf("Start up...\r\n");

    while (true)
    {
        //fgets(input_command, BUFFER_SIZE, stdin);
        scanf("%s", input_command);
		
        printf("INPUT:'%s'\r\n", input_command);
    }
}
