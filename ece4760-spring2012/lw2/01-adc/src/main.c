//  A to D test code
// NOTE -- You MUST MOUNT the Aref jumper  

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "uart.h"

// UART file descriptor
// putchar and getchar are in uart.c
FILE uart_str = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);

unsigned char Ain ; 		//raw A to D number

int main(void)
{ 
   //init the A to D converter 
   //channel zero/ left adj /EXTERNAL Aref
   //!!!CONNECT Aref jumper!!!!
   ADMUX = (1<<ADLAR) | (1<<REFS0) ;  
    
   //enable ADC and set prescaler to 1/128*16MHz=125,000
   //and clear interupt enable
   //and start a conversion
   ADCSRA = ((1<<ADEN) | (1<<ADSC)) + 7 ; 
    
   // init the UART -- uart_init() is in uart.c
  uart_init();
  stdout = stdin = stderr = &uart_str;
  fprintf(stdout,"Starting ADC demo...\n\r"); 
      
   // measure and display loop
   while (1)
   {   
		//get the sample  
 		Ain = ADCH;
 		//start another conversion
 		ADCSRA |= (1<<ADSC) ; 
 		//results to hyperterm
  	printf("%d\n\r",Ain);
  }
}
     