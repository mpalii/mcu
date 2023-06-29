/*
 * @author Maksym Palii
 * @brief Timer 2 220Hz buzzer
 * @version 1.0
 * @date 2023 June 25
 */

#define F_CPU (8000000UL)

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

void init_io_pins(void);
void buzz_220_hz(void);
void buzz_440_hz(void);
void buzz_880_hz(void);
void buzz_1760_hz(void);

int main(void)
{
    init_io_pins();
	
    while (true) 
    { 
        for (uint8_t i = 0; i < 50; i++)
        {
            buzz_220_hz();
            _delay_ms(10);
            buzz_440_hz();
            _delay_ms(10);
            buzz_880_hz();
            _delay_ms(10);
            buzz_1760_hz();
            _delay_ms(10);
        }


        for (uint8_t i = 0; i < 25; i++)
        {
            buzz_220_hz();
            _delay_ms(20);
            buzz_440_hz();
            _delay_ms(20);
            buzz_880_hz();
            _delay_ms(20);
            buzz_1760_hz();
            _delay_ms(20);
        }


        for (uint8_t i = 0; i < 8; i++)
        {
            buzz_220_hz();
            _delay_ms(250);
            buzz_440_hz();
            _delay_ms(250);
            buzz_880_hz();
            _delay_ms(250);
            buzz_1760_hz();
            _delay_ms(250);
        }  
    }
}

void init_io_pins(void)
{
    DDRB = _BV(PB3);
}

/****************************************************************************/
/* Set up timer 0 for 220Hz frequency                                       */
/* (256 (prescaler) * 142 (OCR2A + 1)) / 8_000_000 MHz = 0.004545Sec        */
/****************************************************************************/
void buzz_220_hz(void)
{	
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);   
	
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = _BV(CS22) | _BV(CS21);    // clkT2 S/256
	
    // OCR2A – Timer/Counter0 Output Compare Register channel A
    OCR2A = 141;			   //set the compare reg to 142 ticks (zero based)
}



/****************************************************************************/
/* Set up timer 0 for 440Hz frequency                                       */
/* (128 (prescaler) * 142 (OCR2A + 1)) / 8_000_000 MHz = 0.002272Sec        */
/****************************************************************************/
void buzz_440_hz(void)
{	
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);   
	
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = _BV(CS22) | _BV(CS20);    // clkT2 S/128
	
    // OCR2A – Timer/Counter0 Output Compare Register channel A
    OCR2A = 141;			   //set the compare reg to 142 ticks (zero based)
}



/****************************************************************************/
/* Set up timer 0 for 880Hz frequency                                       */
/* (64 (prescaler) * 142 (OCR2A + 1)) / 8_000_000 MHz = 0.001136Sec         */
/****************************************************************************/
void buzz_880_hz(void)
{	
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);   
	
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = _BV(CS22);    // clkT2 S/64
	
    // OCR2A – Timer/Counter0 Output Compare Register channel A
    OCR2A = 141;			   //set the compare reg to 142 ticks (zero based)
}



/****************************************************************************/
/* Set up timer 0 for 1760Hz frequency                                      */
/* (32 (prescaler) * 142 (OCR2A + 1)) / 8_000_000 MHz = 0.000568Sec         */
/****************************************************************************/
void buzz_1760_hz(void)
{	
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);   
	
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = _BV(CS21) | _BV(CS20);    // clkT2 S/32
	
    // OCR2A – Timer/Counter0 Output Compare Register channel A
    OCR2A = 141;			   //set the compare reg to 142 ticks (zero based)
}
