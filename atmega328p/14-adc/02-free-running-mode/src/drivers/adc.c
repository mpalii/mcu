#include "adc.h"
#include <avr/io.h>

void adc_init(void)
{
    // ADC Enable
    ADCSRA |= _BV(ADEN);

    // ADC Prescaler Select Bits (Division Factor - 64: 8MHz/64 = 125kHz)
    ADCSRA |= _BV(ADPS2) | _BV(ADPS1);

    // ADC Interrupt Enable
    ADCSRA |= _BV(ADIE);

    // ADC Auto trigger enable
    ADCSRA |= _BV(ADATE);

    // ADC Input Channel Selection (Channel 3 - ADC3), with external AREF
    ADMUX |= _BV(MUX1) | _BV(MUX0);

    // ADC Start Conversion
    ADCSRA |= _BV(ADSC);
}
