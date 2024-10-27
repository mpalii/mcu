//  A to D test code
// NOTE -- You MUST mount the Aref jumper  

#define F_CPU 16000000UL

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
 #include <avr/sleep.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include "uart.h"

// UART file descriptor
// putchar and getchar are in uart.c
FILE uart_str = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);
              
//I like these definitions
#define begin {
#define end   }  
#define Vref 2.56 

volatile int Ain, AinLow ; 		//raw A to D number
float voltage ;		//scaled input voltage
char v_string[10]; // scaled input voltage string to print

ISR (ADC_vect)
begin 
	//program ONLY gets here when ADC done flag is set
   //when reading 10-bit values 
   //you MUST read the low byte first 
   AinLow = (int)ADCL;
   Ain = (int)ADCH*256; 
   Ain = Ain + AinLow;
end

int main(void)
begin 
   
   //init the A to D converter 
   //channel zero/ right adj /ext Aref
   //!!!CONNECT Aref jumper!!!!
  //  ADMUX = 0b00000000;   
  // ADMUX = (1<<REFS0);
  ADMUX = (1<<REFS1) | (1<<REFS0);
   //enable ADC and set prescaler to 1/127*16MHz=125,000
   //and set int enable
   ADCSRA = ((1<<ADEN) | (1<<ADIE)) + 7 ; 

   SMCR = (1<<SM0) ; // sleep -- choose ADC mode 
   
   // init the UART -- uart_init() is in uart.c
  uart_init();
  stdout = stdin = stderr = &uart_str;
  fprintf(stdout,"\n\rStarting ADC ISR demo...\n\r"); 

  // Need the next two statments so that the USART finishes
  // BEFORE the cpu goes to sleep.
   while (!(UCSR0A & (1<<UDRE0))) ; 
   _delay_ms(1);

   sleep_enable();                             
   sei();
      
   // measure and display loop
   while (1)
   begin   
	    //get the sample  
	    //The sleep statment lowers digital noise   
	    //and starts the A/D conversion
	    sleep_cpu();
     
        //program ONLY gets here after ADC ISR is done
      	voltage = (float)Ain ;
      	voltage = (voltage/1024.0)*Vref ; //(fraction of full scale)*Vref
		dtostrf(voltage, 6, 3, v_string);
		printf("%s", v_string);
      	printf(" %d\n\r ",Ain) ;

		// Need the next two statments so that the USART finishes
  		// BEFORE the cpu goes to sleep the next time thru the loop.
		while (!(UCSR0A & (1<<UDRE0))) ;
		_delay_ms(1);
   end
end
     
