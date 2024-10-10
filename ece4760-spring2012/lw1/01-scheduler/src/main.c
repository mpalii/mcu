/**
 * @author Maksym Palii
 * @brief Scheduler
 * @version 1.0
 * @date 2024 October 10
 * @link https://people.ece.cornell.edu/land/courses/ece4760/labs/s2012/Sched1GCC644.c
 */

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>

//timeout values for each task
#define t1 250
#define t2 125
#define t3 60
 
//the three task subroutines
void task1(void);  	//blink at 2 or 8 Hz
void task2(void);	//blink at 1 Hz
void task3(void);	//detect button and modify task 1 rate 

void initialize(void); //all the usual mcu stuff 
          
volatile unsigned char time1, time2, time3;	//timeout counters 
unsigned char tsk2c;				//task 2 counter to get to 1/2 second
unsigned char tsk3m;				//task 3 message to task 1
unsigned char led;					//light states 
unsigned int time ;					//time since boot 
         
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
  
  //main task scheduler loop 
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
  }
}  
 
//*******************************   
//Task 3  
void task3(void) 
{
  // detect D.7 button push and
  // generate the message for task 1
  tsk3m = ~PIND & 0x80;  
} 
  
//********************************************************** 
//Set it all up
void initialize(void)
{
  //set up the ports
  DDRB=0x0f;    // PORT B is an output  
  PORTB=0;
  DDRD=0x00;	// PORT D is an input 
           
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
      
  //crank up the ISRs
  sei();
}  

   
