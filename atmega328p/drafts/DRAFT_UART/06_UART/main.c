/*
 * Created: 20/12/2022 15:44:10
 * Author : Maksym_Palii
 */ 

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "uart328p.h"

#define CMD_MAX_SIZE 10

char input_command[CMD_MAX_SIZE];

int main(void)
{
    stdin = stdout = stderr = UART_init(18432000, 9600, false);
	printf("Start up...\n\r");

    while (true) 
    {
		fgets(input_command, CMD_MAX_SIZE - 1, stdin);
		//scanf("%s", input_command);
		//input_command[strcspn(input_command, "\r\n")] = 0;
		printf("INPUT:'%s'\n", input_command);
    }
}

