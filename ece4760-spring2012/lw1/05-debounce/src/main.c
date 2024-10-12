/**
 * @author Maksym Palii
 * @brief Debounce
 * @version 1.0
 * @date 2024 October 12
 * @link https://people.ece.cornell.edu/land/courses/ece4760/labs/s2012/lab2code/debounceGCC644.c
 */

// Debounce demo 
// Mega644 version
// used as an example of a state machine.      
             
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>

//timeout values for each task
#define t1 200  
#define t2 50
#define t3 50  

//State machine state names
#define Released 1 
#define MaybePush 2
#define Pushed 3
#define MaybeReleased 4
 
//the three task subroutines
void task1(void); //inc LEDs
void task2(void);	//non-debounced button 0
void task3(void);	//debounced button 1

void initialize(void); //all the usual mcu stuff 
          
volatile unsigned char time1, time2, time3;	//timeout counters 
unsigned char PushFlag;		//message indicating a button push 
unsigned char led;			//LED count
unsigned char PushState;	//state machine  
         
//**********************************************************
//timer 0 comare match ISR
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
    if (time1==0)	task1();
    if (time2==0) task2();
    if (time3==0)	task3();
  }

}  
  
//**********************************************************          
//Task subroutines
//Task 1
void task1(void) 
{  
  time1=t1;  //reset the task timer

  if (PushFlag)  //check for a button press
  {
  	//reset flag
  	PushFlag = 0;
  	//increment the LEDs	
  	++led;	
  	PORTC = ~led;
  }
}  
 
//******************************* 
//Task 2  
void task2(void) 
{
  time2=t2;  //reset the task timer

  if (~PIND & 0x01)  //button push
  {  
     PushFlag = 1;
  }
}  
 
//*******************************   
//Task 3  
void task3(void) 
{
  time3=t3;     //reset the task timer
  switch (PushState)
  {

     case Released: 
        if (~PIND & 0x02) PushState=MaybePush;
        else PushState=Released;
        break;

     case MaybePush:
        if (~PIND & 0x02) 
        {
           PushState=Pushed;   
           PushFlag=1;
        }
        else PushState=Released;
        break;

     case Pushed:  
        if (~PIND & 0x02) PushState=Pushed; 
        else PushState=MaybeReleased;    
        break;

     case MaybeReleased:
        if (~PIND & 0x02) PushState=Pushed; 
        else 
        {
           PushState=Released;
           PushFlag=0;
        }    
        break;

  }
}
  
//********************************************************** 
//Set it all up
void initialize(void)
{
  /**
   * @def disable JTAG interface in order to make pins 2, 3, 4, 5 (Port C) as general purpose
   * @see https://ww1.microchip.com/downloads/en/DeviceDoc/doc2593.pdf#G1.1375224
   */
  MCUCR |= _BV(JTD);
  MCUCR |= _BV(JTD);

  //set up the ports
  DDRD = 0x00;	// PORT D is an input
  PORTD = 0b00000011; // PORT D pull-up PD0 and PD1

  DDRC = 0xff;    // PORT C is an ouput 
  PORTC = 0xff ;  // turn off leds
           
  //set up timer 0 for 1 mSec timebase 
  OCR0A = 249;  		//set the compare re to 250 time ticks
  TIMSK0= (1<<OCIE0A);	//turn on timer 0 cmp match ISR 
  //set prescalar to divide by 64 
  TCCR0B= 3; //0b00000011;	
  // turn on clear-on-match
  TCCR0A= (1<<WGM01) ;
    
  //init the LED status (all off)
  led=0x00; 
  PORTC = ~led; 

  //init the task timers
  time1=t1;
  time2=t2;
  time3=t3;    
  
  //init the  message
  //for no button push
  PushFlag = 0;
  //init the state machine
  PushState = Released;
      
  //crank up the ISRs
  sei() ;
} 
