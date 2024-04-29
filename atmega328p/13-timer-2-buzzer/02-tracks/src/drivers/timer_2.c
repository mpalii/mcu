/**
 * @author Maksym Palii
 * @brief Timer 2 driver
 * @version 1.0
*/  

#define F_CPU (8000000UL)

#include "timer_2.h"
#include <util/delay.h>

void buzz_C3(void);
void buzz_C3_sharp(void);
void buzz_D3(void);
void buzz_D3_sharp(void);
void buzz_E3(void);
void buzz_F3(void);
void buzz_F3_sharp(void);
void buzz_G3(void);
void buzz_G3_sharp(void);
void buzz_A3(void);
void buzz_A3_sharp(void);
void buzz_B3(void);

void buzz_C4(void);
void buzz_C4_sharp(void);
void buzz_D4(void);
void buzz_D4_sharp(void);
void buzz_E4(void);
void buzz_F4(void);
void buzz_F4_sharp(void);
void buzz_G4(void);
void buzz_G4_sharp(void);
void buzz_A4(void);
void buzz_A4_sharp(void);
void buzz_B4(void);

void buzz_C5(void);

void internal_delay_ms(uint16_t ms)
{
    while (ms > 0)
    {  
        _delay_ms(1);
        --ms;
    }
}

void (*buzz_ptr[])(void) = 
{
    buzz_C3,
    buzz_C3_sharp,
    buzz_D3,
    buzz_D3_sharp,
    buzz_E3,
    buzz_F3,
    buzz_F3_sharp,
    buzz_G3,
    buzz_G3_sharp,
    buzz_A3,
    buzz_A3_sharp,
    buzz_B3,

    buzz_C4,
    buzz_C4_sharp,
    buzz_D4,
    buzz_D4_sharp,
    buzz_E4,
    buzz_F4,
    buzz_F4_sharp,
    buzz_G4,
    buzz_G4_sharp,
    buzz_A4,
    buzz_A4_sharp,
    buzz_B4,

    buzz_C5
};

/****************************************************************************/
/* Set up timer 2 for 130.7531Hz frequency (130.8128Hz - C3)                */
/* (256 (prescaler) * 239 (OCR2A + 1)) / 8_000_000 MHz = 0.007648   Sec     */
/****************************************************************************/
void buzz_C3(void)
{	
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);   
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = _BV(CS22) | _BV(CS21);    // clkT2 S/256
    // OCR2A – Timer/Counter0 Output Compare Register channel A
    OCR2A = 238;                        //set the compare reg to 239 ticks (zero based)
}

/****************************************************************************/
/* Set up timer 2 for 138.8888Hz frequency (138.5913Hz - C3#)               */
/* (256 (prescaler) * 225 (OCR2A + 1)) / 8_000_000 MHz = 0.007200   Sec     */
/****************************************************************************/
void buzz_C3_sharp(void)
{	
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);   
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = _BV(CS22) | _BV(CS21);    // clkT2 S/256
    // OCR2A – Timer/Counter0 Output Compare Register channel A
    OCR2A = 224;                        //set the compare reg to 225 ticks (zero based)
}

/****************************************************************************/
/* Set up timer 2 for 146.7136Hz frequency (146.8324Hz - D3)                */
/* (256 (prescaler) * 213 (OCR2A + 1)) / 8_000_000 MHz = 0.006816   Sec     */
/****************************************************************************/
void buzz_D3(void)
{	
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);   
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = _BV(CS22) | _BV(CS21);    // clkT2 S/256
    // OCR2A – Timer/Counter0 Output Compare Register channel A
    OCR2A = 212;                        //set the compare reg to 213 ticks (zero based)
}

/****************************************************************************/
/* Set up timer 2 for 155.4726Hz frequency (155.5635Hz - D3#)               */
/* (256 (prescaler) * 201 (OCR2A + 1)) / 8_000_000 MHz = 0.006432   Sec     */
/****************************************************************************/
void buzz_D3_sharp(void)
{	
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);   
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = _BV(CS22) | _BV(CS21);    // clkT2 S/256
    // OCR2A – Timer/Counter0 Output Compare Register channel A
    OCR2A = 200;                        //set the compare reg to 201 ticks (zero based)
}

/****************************************************************************/
/* Set up timer 2 for 164.4736Hz frequency (164.8138Hz - E3)                */
/* (256 (prescaler) * 190 (OCR2A + 1)) / 8_000_000 MHz = 0.006080   Sec     */
/****************************************************************************/
void buzz_E3(void)
{	
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);   
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = _BV(CS22) | _BV(CS21);    // clkT2 S/256
    // OCR2A – Timer/Counter0 Output Compare Register channel A
    OCR2A = 189;                        //set the compare reg to 190 ticks (zero based)
}

/****************************************************************************/
/* Set up timer 2 for 174.5810Hz frequency (174.6141Hz - F3)                */
/* (256 (prescaler) * 179 (OCR2A + 1)) / 8_000_000 MHz = 0.005728   Sec     */
/****************************************************************************/
void buzz_F3(void)
{	
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);   
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = _BV(CS22) | _BV(CS21);    // clkT2 S/256
    // OCR2A – Timer/Counter0 Output Compare Register channel A
    OCR2A = 178;                        //set the compare reg to 179 ticks (zero based)
}

/****************************************************************************/
/* Set up timer 2 for 184.9112Hz frequency (184.9972Hz - F3#)               */
/* (256 (prescaler) * 169 (OCR2A + 1)) / 8_000_000 MHz = 0.005408   Sec     */
/****************************************************************************/
void buzz_F3_sharp(void)
{	
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);   
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = _BV(CS22) | _BV(CS21);    // clkT2 S/256
    // OCR2A – Timer/Counter0 Output Compare Register channel A
    OCR2A = 168;                        //set the compare reg to 169 ticks (zero based)
}

/****************************************************************************/
/* Set up timer 2 for 196.5408Hz frequency (195.9977Hz - G3)                */
/* (256 (prescaler) * 159 (OCR2A + 1)) / 8_000_000 MHz = 0.005088   Sec     */
/****************************************************************************/
void buzz_G3(void)
{	
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);   
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = _BV(CS22) | _BV(CS21);    // clkT2 S/256
    // OCR2A – Timer/Counter0 Output Compare Register channel A
    OCR2A = 158;                        //set the compare reg to 159 ticks (zero based)
}

/****************************************************************************/
/* Set up timer 2 for 208.3333Hz frequency (207.6523Hz - G3#)               */
/* (256 (prescaler) * 150 (OCR2A + 1)) / 8_000_000 MHz = 0.004800   Sec     */
/****************************************************************************/
void buzz_G3_sharp(void)
{	
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);   
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = _BV(CS22) | _BV(CS21);    // clkT2 S/256
    // OCR2A – Timer/Counter0 Output Compare Register channel A
    OCR2A = 149;                        //set the compare reg to 150 ticks (zero based)
}

/****************************************************************************/
/* Set up timer 2 for 220.0704Hz frequency (220.0000Hz - A3)                */
/* (256 (prescaler) * 142 (OCR2A + 1)) / 8_000_000 MHz = 0.004544Sec        */
/****************************************************************************/
void buzz_A3(void)
{	
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);   
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = _BV(CS22) | _BV(CS21);    // clkT2 S/256
    // OCR2A – Timer/Counter0 Output Compare Register channel A
    OCR2A = 141;			   //set the compare reg to 142 ticks (zero based)
}

/****************************************************************************/
/* Set up timer 2 for 233.2089Hz frequency (233.0819Hz - A3#)               */
/* (256 (prescaler) * 134 (OCR2A + 1)) / 8_000_000 MHz = 0.004288   Sec     */
/****************************************************************************/
void buzz_A3_sharp(void)
{	
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);   
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = _BV(CS22) | _BV(CS21);    // clkT2 S/256
    // OCR2A – Timer/Counter0 Output Compare Register channel A
    OCR2A = 133;                        //set the compare reg to 134 ticks (zero based)
}

/****************************************************************************/
/* Set up timer 2 for 246.0623Hz frequency (246.9417Hz - B3)                */
/* (256 (prescaler) * 127 (OCR2A + 1)) / 8_000_000 MHz = 0.004049539 Sec    */
/****************************************************************************/
void buzz_B3(void)
{	
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);   
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = _BV(CS22) | _BV(CS21);    // clkT2 S/256
    // OCR2A – Timer/Counter0 Output Compare Register channel A
    OCR2A = 126;			   //set the compare reg to 127 ticks (zero based)
}

/****************************************************************************/
/* Set up timer 2 for 262,6050Hz frequency (261.6256Hz - C4)                */
/* (256 (prescaler) * 119 (OCR2A + 1)) / 8_000_000 MHz = 0.003808   Sec     */
/****************************************************************************/
void buzz_C4(void)
{	
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);   
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = _BV(CS22) | _BV(CS21);    // clkT2 S/256
    // OCR2A – Timer/Counter0 Output Compare Register channel A
    OCR2A = 118;                        //set the compare reg to 119 ticks (zero based)
}

/****************************************************************************/
/* Set up timer 2 for 276.5486Hz frequency (277.1826Hz - C4#)               */
/* (256 (prescaler) * 113 (OCR2A + 1)) / 8_000_000 MHz = 0.003616   Sec     */
/****************************************************************************/
void buzz_C4_sharp(void)
{	
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);   
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = _BV(CS22) | _BV(CS21);    // clkT2 S/256
    // OCR2A – Timer/Counter0 Output Compare Register channel A
    OCR2A = 112;                        //set the compare reg to 113 ticks (zero based)
}

/****************************************************************************/
/* Set up timer 2 for 294,8113Hz frequency (293.6648Hz - D4)                */
/* (256 (prescaler) * 106 (OCR2A + 1)) / 8_000_000 MHz = 0.003392   Sec     */
/****************************************************************************/
void buzz_D4(void)
{	
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);   
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = _BV(CS22) | _BV(CS21);    // clkT2 S/256
    // OCR2A – Timer/Counter0 Output Compare Register channel A
    OCR2A = 105;                        //set the compare reg to 106 ticks (zero based)
}

/****************************************************************************/
/* Set up timer 2 for 312.5000Hz frequency (311.1270Hz - D4#)               */
/* (256 (prescaler) * 100 (OCR2A + 1)) / 8_000_000 MHz = 0.003200   Sec     */
/****************************************************************************/
void buzz_D4_sharp(void)
{	
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);   
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = _BV(CS22) | _BV(CS21);    // clkT2 S/256
    // OCR2A – Timer/Counter0 Output Compare Register channel A
    OCR2A = 99;                        //set the compare reg to 100 ticks (zero based)
}

/****************************************************************************/
/* Set up timer 2 for 328,9473Hz frequency (329.6276Hz - E4)                */
/* (256 (prescaler) * 95 (OCR2A + 1)) / 8_000_000 MHz = 0.003040   Sec      */
/****************************************************************************/
void buzz_E4(void)
{	
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);   
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = _BV(CS22) | _BV(CS21);    // clkT2 S/256
    // OCR2A – Timer/Counter0 Output Compare Register channel A
    OCR2A = 94;                        //set the compare reg to 95 ticks (zero based)
}

/****************************************************************************/
/* Set up timer 2 for 351,1235Hz frequency (349.2282Hz - F4)                */
/* (256 (prescaler) * 89 (OCR2A + 1)) / 8_000_000 MHz = 0.002848   Sec      */
/****************************************************************************/
void buzz_F4(void)
{	
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);   
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = _BV(CS22) | _BV(CS21);    // clkT2 S/256
    // OCR2A – Timer/Counter0 Output Compare Register channel A
    OCR2A = 88;                        //set the compare reg to 89 ticks (zero based)
}

/****************************************************************************/
/* Set up timer 2 for 372.0238Hz frequency (369.9944Hz - F4#)               */
/* (256 (prescaler) * 84 (OCR2A + 1)) / 8_000_000 MHz = 0.002688   Sec      */
/****************************************************************************/
void buzz_F4_sharp(void)
{	
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);   
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = _BV(CS22) | _BV(CS21);    // clkT2 S/256
    // OCR2A – Timer/Counter0 Output Compare Register channel A
    OCR2A = 83;                        //set the compare reg to 84 ticks (zero based)
}

/****************************************************************************/
/* Set up timer 2 for 390,6250Hz frequency (391.9954Hz - G4)                */
/* (256 (prescaler) * 80 (OCR2A + 1)) / 8_000_000 MHz = 0.002560   Sec      */
/****************************************************************************/
void buzz_G4(void)
{	
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);   
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = _BV(CS22) | _BV(CS21);    // clkT2 S/256
    // OCR2A – Timer/Counter0 Output Compare Register channel A
    OCR2A = 79;                        //set the compare reg to 80 ticks (zero based)
}

/****************************************************************************/
/* Set up timer 2 for 416.6666Hz frequency (415.3047Hz - G4#)               */
/* (256 (prescaler) * 75 (OCR2A + 1)) / 8_000_000 MHz = 0.002400   Sec      */
/****************************************************************************/
void buzz_G4_sharp(void)
{	
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);   
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = _BV(CS22) | _BV(CS21);    // clkT2 S/256
    // OCR2A – Timer/Counter0 Output Compare Register channel A
    OCR2A = 74;                        //set the compare reg to 75 ticks (zero based)
}

/****************************************************************************/
/* Set up timer 2 for 440,1408Hz frequency (440.0000Hz - A4)                */
/* (256 (prescaler) * 71 (OCR2A + 1)) / 8_000_000 MHz = 0.002272   Sec      */
/****************************************************************************/
void buzz_A4(void)
{	
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);   
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = _BV(CS22) | _BV(CS21);    // clkT2 S/256
    // OCR2A – Timer/Counter0 Output Compare Register channel A
    OCR2A = 70;                        //set the compare reg to 71 ticks (zero based)
}

/****************************************************************************/
/* Set up timer 2 for 466.4179Hz frequency (466.1638Hz - A4#)               */
/* (256 (prescaler) * 67 (OCR2A + 1)) / 8_000_000 MHz = 0.002144   Sec      */
/****************************************************************************/
void buzz_A4_sharp(void)
{	
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);   
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = _BV(CS22) | _BV(CS21);    // clkT2 S/256
    // OCR2A – Timer/Counter0 Output Compare Register channel A
    OCR2A = 66;                        //set the compare reg to 67 ticks (zero based)
}

/****************************************************************************/
/* Set up timer 2 for 496.0317Hz frequency (493.8833Hz - B4)                */
/* (256 (prescaler) * 63 (OCR2A + 1)) / 8_000_000 MHz = 0.002016   Sec      */
/****************************************************************************/
void buzz_B4(void)
{	
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);   
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = _BV(CS22) | _BV(CS21);    // clkT2 S/256
    // OCR2A – Timer/Counter0 Output Compare Register channel A
    OCR2A = 62;                        //set the compare reg to 63 ticks (zero based)
}

/****************************************************************************/
/* Set up timer 2 for 520.8333Hz frequency (523.2511Hz - C5)                */
/* (256 (prescaler) * 60 (OCR2A + 1)) / 8_000_000 MHz = 0.001920   Sec      */
/****************************************************************************/
void buzz_C5(void)
{	
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);   
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = _BV(CS22) | _BV(CS21);    // clkT2 S/256
    // OCR2A – Timer/Counter0 Output Compare Register channel A
    OCR2A = 59;                        //set the compare reg to 60 ticks (zero based)
}

void buzz_off(void)
{	
    // TCCR2B – Timer/Counter0 Control Register channel B
    TCCR2B = 0;

    GPIO_LOW(OC2A);
}

void play_tone(uint8_t note, uint16_t interval_duration, uint8_t note_part)
{
    uint16_t note_duration = interval_duration / note_part;
    uint16_t mute_duration = interval_duration - note_duration;

    buzz_ptr[note]();
    internal_delay_ms(note_duration);

    if (mute_duration != 0)
    {
        buzz_off();
        internal_delay_ms(mute_duration);
    }
}

void mute(uint16_t mute_duration)
{
    buzz_off();
    internal_delay_ms(mute_duration);   
}
