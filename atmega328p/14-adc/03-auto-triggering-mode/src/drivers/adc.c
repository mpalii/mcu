#include "adc.h"
#include <avr/interrupt.h>

static volatile uint8_t conversion_result = 0;

ISR(ADC_vect)
{
    conversion_result = ADCH;
}

void init_adc(void)
{
    ADCSRB = _BV(ADTS1) | _BV(ADTS0);
    // ADC Enable and set Prescaler Select Bits (Division Factor - 64: 8MHz/128 = 125kHz)
    ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0) | _BV(ADIE) | _BV(ADATE);
    // ADC Input Channel Selection (Channel 3 - ADC3), AVCC with external capacitor at AREF pin, ADLAR enable
    ADMUX = _BV(MUX1) | _BV(MUX0) | _BV(ADLAR);
    // ADC Start Conversion
    ADCSRA |= _BV(ADSC);
}

uint8_t adc_get_conversion_result(void)
{
    return conversion_result;
}
