#include "drivers/gpio.h"
#include "drivers/lcd1602.h"
#include <avr/interrupt.h>

void init_tasks(void);
void init_timer_0(void);

// Task 1
#define T1 250
void task_1(void);
volatile uint8_t time1;

ISR (TIMER0_COMPA_vect)
{
	if (time1 > 0) --time1;
}

int main(void)
{
    init_gpio();
	init_lcd1602();
	init_tasks();
	init_timer_0();
	sei();
	
	//char *message_one = "Simple text!";
	//char *message_two = "Message two#";
	//char *message = "Hello World!\n Simple text!)))\rThe end...      \n---------------*";
	char *message = "Hello World!#\n Simple text!)))#\rThe end...      \n---------------*";
	
	printMessage(message);
	
    while (1) 
    {
		if (time1 == 0) task_1();
    }
}



void init_tasks(void)
{
	time1 = T1;
}

/****************************************************************************/
/* Set up timer 0 for 1 mSec timebase                                       */
/* (64 (prescaler) * 125 (OCR0A + 1)) / 8_000_000 MHz = 0.001Sec = 1mSec    */
/****************************************************************************/
void init_timer_0(void)
{
	// TCCR0A – Timer/Counter0 Control Register channel A
	TCCR0A = _BV(WGM01);             // Clear Timer on Compare Match (CTC) mode (only works with channel)
	
	// TCCR0B – Timer/Counter0 Control Register channel B
	TCCR0B = _BV(CS01) | _BV(CS00);  // clk/64 (From prescaler)
	
	// OCR0A – Timer/Counter0 Output Compare Register channel A
	OCR0A =	124;                     //set the compare reg to 125 time ticks (zero based)
	
	// TIMSK0 – Timer/Counter0 Interrupt Mask Register
	TIMSK0 = _BV(OCIE0A);            // Timer/Counter0 Output Compare Match channel A Interrupt Enable
}

/****************************************************************************/
/* Tasks implementation section                                             */
/****************************************************************************/

void task_1(void)
{
	// re-initialize task 1 timer
	time1 = T1;
	
	// perform print
	handleMessageChar();
}





/*
int main(void)
{
    init_gpio();
	init_lcd1602();
	
	char *message_one = "Simple text!";
	char *message_two = "Message two#";
	
	
	//for (int i = 0; message[i] != '\0'; i++)
	//{
	//	lcd1602_print_char(message[i]);
	//}
	
	
    while (1) 
    {
		lcd1602_send_command(MOVE_CURSOR_TO_POSITION_0_LINE_1);
		for (int i = 0; message_one[i] != '\0'; i++)
		{
			
			GPIO_LOW(LCD_1602_E);
			GPIO_HIGH(LCD_1602_RS);
			PORTD = message_one[i];
			GPIO_HIGH(LCD_1602_E);
			
			_delay_us(1000);
		}
		
		
		lcd1602_send_command(MOVE_CURSOR_TO_POSITION_0_LINE_2);
		for (int i = 0; message_two[i] != '\0'; i++)
		{
			lcd1602_print_char(message_two[i]);
		}
		
		_delay_ms(500);
		lcd1602_send_command(CLEAR_DISPLAY);
		_delay_ms(500);		
    }
}
*/