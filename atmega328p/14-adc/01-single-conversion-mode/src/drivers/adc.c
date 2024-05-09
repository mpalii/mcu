#include "adc.h"
#include <avr/io.h>

void adc_init(void)
{
    // ADC Enable, Prescaler Select Bits (Division Factor - 64: 8MHz/64 = 125kHz)
    ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1);
    // Internal 1.1V Voltage Reference with external capacitor at AREF pin, Input Channel - ADC3
    ADMUX = _BV(REFS1) | _BV(REFS0) | _BV(MUX1) | _BV(MUX0);
}

void adc_start_conversion(void)
{
    // ADC Start Conversion
    ADCSRA |= _BV(ADSC);
}