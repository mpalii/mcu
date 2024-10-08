/*
 * 09_EEPROM_random.c
 *
 * Created: 19/02/2023 15:08:26
 * Author : Maksym_Palii
 */

#define F_CPU 18432000UL
#define BUFFER_SIZE 8
#define EEPROM_RND_DATA 0

#include <avr/eeprom.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "uart328p.h"

char input_command[BUFFER_SIZE];
uint8_t rnd;

/****************************************************************************/
/* Set up timer 0                                                           */
/****************************************************************************/
void init_timer_0(void)
{
	// TCCR0B – Timer/Counter0 Control Register channel B
	TCCR0B = _BV(CS00);  // no divider
}

int main(void)
{
	init_timer_0();
    stdin = stdout = stderr = UART_init(F_CPU, 9600, false);
	rnd = eeprom_read_byte(EEPROM_RND_DATA);
    printf("Last random: %d\r\n", rnd);

    while (true)
    {
	    scanf("%s", input_command);
		
		if (strcmp(input_command, "rnd") == 0)
		{
			rnd = TCNT0;
			eeprom_write_byte(EEPROM_RND_DATA, rnd);
			printf("%d\r\n", rnd);
		}
		else
		{
			printf("UNKNOWN\r\n");
		}
    }
}
