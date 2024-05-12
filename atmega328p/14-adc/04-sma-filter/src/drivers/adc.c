#include "adc.h"
#include <avr/interrupt.h>
#include <util/atomic.h>

#define WINDOW_SIZE (512)

uint16_t calculation_window_buffer[WINDOW_SIZE] = { 0, };
static volatile uint32_t buffer_summ = 0;
static volatile uint16_t index = 0;

ISR(ADC_vect)
{
    buffer_summ -= calculation_window_buffer[index];
    calculation_window_buffer[index] = ADC;
    buffer_summ += calculation_window_buffer[index];

    if (++index > (WINDOW_SIZE - 1))
    {
        index = 0;
    }
}

void init_adc(void)
{
    // ADC Input Channel Selection (Channel 3 - ADC3), AVCC with external capacitor at AREF pin, ADLAR disable
    ADMUX = _BV(MUX1) | _BV(MUX0) | _BV(REFS0);
    // ADC trigger conversion on Timer/Counter0 Compare Match A
    ADCSRB = _BV(ADTS1) | _BV(ADTS0);
    // ADC Enable, set Prescaler Select Bits (Division Factor - 64: 8MHz/64 = 125kHz), enable interrupts, single conversion
    ADCSRA = _BV(ADEN) | _BV(ADSC) | _BV(ADATE) | _BV(ADIE) | _BV(ADPS2) | _BV(ADPS1);
}


uint16_t adc_get_conversion_result(void)
{
    return (uint16_t) (buffer_summ / WINDOW_SIZE);
}
