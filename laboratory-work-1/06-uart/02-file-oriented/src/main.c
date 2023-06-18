/*
 * @author Maksym Palii
 * @brief UART blocking file-oriented approach
 * @version 1.0
 * @date 2023 June 11
 */

#define F_CPU 8000000UL

#include "uart328p.h"

int main(void)
{
	char first_name[20];
    char last_name[20];
    int age;

    stdin = stdout = stderr = uart_init(F_CPU, 9600, false);
    printf("Start up...\r\n");

    while (true)
    {
        printf("Enter first and last name: ");
        scanf("%19s %19s", first_name, last_name);

        printf("Enter your age: ");
        scanf("%d", &age);
		
        printf("First: '%s' Last: '%s', Age:'%d'\r\n", first_name, last_name, age);
    }
}