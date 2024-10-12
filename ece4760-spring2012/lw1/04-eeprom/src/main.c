/**
 * @author Maksym Palii
 * @brief EEPROM
 * @version 1.0
 * @date 2024 October 12
 * @link https://people.ece.cornell.edu/land/courses/ece4760/labs/s2012/lab1code/eeprom_GCC644.c
 */

// Mega644 version
// with eeprom test

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <avr/eeprom.h> 

// serial communication library
#include "uart.h"

//timeout values for each task
#define t1 250  
#define t2 125
#define t3 60  
 
// eeprom define addressee
#define eeprom_true 0
#define eeprom_data 1

//the three task subroutines
void task1(void); //blink at 2 or 8 Hz
void task2(void);	//blink at 1 Hz
void task3(void);	//detect button and modify task 1 rate 

void initialize(void); //all the usual mcu stuff 
          
volatile unsigned char time1, time2, time3;	//timeout counters 
unsigned char tsk2c;				//task 2 counter to get to 1/2 second
unsigned char tsk3m;				//task 3 message to task 1
unsigned char led;					//light states 
unsigned char time ;					//time since boot 


// UART file descriptor
// putchar and getchar are in uart.c
FILE uart_str = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);
         
//**********************************************************
//timer 0 compare ISR
ISR (TIMER0_COMPA_vect)
{      
  //Decrement the three times if they are not already zero
  if (time1>0)	--time1;
  if (time2>0) 	--time2;
  if (time3>0)	--time3;
}  

//**********************************************************       
//Entry point and task scheduler loop
int main(void)
{  
  	initialize();
 	if (eeprom_read_byte((uint8_t*)eeprom_true) != 'T')
 	{ 
  		eeprom_write_byte((uint8_t*)eeprom_data,0x55);
		eeprom_write_byte((uint8_t*)eeprom_true,'T');
 	}

  //main task scheduler loop 
  fprintf(stdout,"%x \n\r", eeprom_read_byte((uint8_t*)eeprom_data)) ;

  while(1)
  { 
  	// reset time and call task    
    if (time1==0){ time1=t1; task1();}
    if (time2==0){ time2=t2; task2();}
    if (time3==0){ time3=t3; task3();}
  }
}  
  
//*******************************         
//Task subroutines
//Task 1
void task1(void) 
{  
  if (tsk3m != 0) time1 >>= 2;  //check for task 3 message
  
  //toggle the zeros bit
  led = led ^ 0x01;
  PORTB = led;
}  
 
//******************************* 
//Task 2  
void task2(void) 
{
  if (--tsk2c == 0)  //have we waited 1/2 second?
  {  
  	tsk2c = 4;		//reload the 1/2 sec counter
     //toggle the ones bit
  	led = led ^ 0x02;
  	PORTB = led;
	fprintf(stdout,"%d \n\r", time++) ;
	// will print message if argument is NOT true;
	//assert(time<10);
  }
}  
 
//*******************************   
//Task 3  
void task3(void) 
{
  // detect D.7 button push and
  // generate the message for task 1
  tsk3m = ~PIND & 0x80;  
  if (tsk3m) eeprom_write_byte((uint8_t*)eeprom_data,time);
  // test assertion -- 
  // will print message if argument is NOT true
  //assert(!(~PIND & 0x40) ) ;
} 
  
//********************************************************** 
//Set it all up
void initialize(void)
{
  //set up the ports
  DDRB=0x0f;    // PORT B is an output  
  PORTB=0;
  DDRD=0x02;	// PORT D is an input except for UART on D.1
  PORTD = 0x80; /*Pull up internal resistor PD7*/

           
  //set up timer 0 for 1 mSec ticks
  TIMSK0 = 2;		//turn on timer 0 cmp match ISR 
  OCR0A = 250;  	//set the compare reg to 250 time ticks
  TCCR0A = 0b00000010; // turn on clear-on-match
  TCCR0B = 0b00000011;	// clock prescalar to 64
    
  //init the LED status (all off)
  led=0xff; 
  
  //init the task timers
  time1=t1;
  time2=t2;
  time3=t3;    
  
  //init the task 2 state variable for four ticks
  tsk2c=4;
  
  //init the task 3 message for no message
  tsk3m=0;

  //init the UART -- uart_init() is in uart.c
  uart_init();
  stdout = stdin = stderr = &uart_str;
  fprintf(stdout,"Starting...\n\r");
  
  //crank up the ISRs
  sei();
}
