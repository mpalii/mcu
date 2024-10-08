/*
 * timer0.h
 *
 * Created: 02/04/2023 16:14:17
 *  Author: Maksym_Palii
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

/*
//timer 0 compare ISR
ISR(TIMER0_COMPA_vect)
{
	//Decrement buttons handler task timer if it is not already zero
	if (time1 > 0) --time1;
}
*/

void init_timer0(void);

#endif /* TIMER0_H_ */