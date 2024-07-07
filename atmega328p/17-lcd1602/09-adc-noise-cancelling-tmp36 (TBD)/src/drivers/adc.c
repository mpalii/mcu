#include "adc.h"
#include <avr/interrupt.h>

#define REFFERENCE_VOLTAGE_UV (1100000UL)
#define ADC_RESOLUTION (1024)
#define CONVERSION_RATIO (REFFERENCE_VOLTAGE_UV / ADC_RESOLUTION)

static uint16_t conversion_result = 0;

ISR(ADC_vect)
{
    conversion_result = ADC;
}

void init_adc(void)
{
    // ADC Input Channel Selection (Channel 3 - ADC3), Internal 1.1V Voltage Reference with external capacitor at AREF pin, ADLAR disable
    ADMUX = _BV(MUX1) | _BV(MUX0) | _BV(REFS1) | _BV(REFS0);
    // ADC in free running mode
    ADCSRB = 0x00;
    // ADC Enable, set Prescaler Select Bits (Division Factor - 64: 8MHz/64 = 125kHz), enable interrupts
    ADCSRA = _BV(ADEN) | _BV(ADIE) | _BV(ADPS2) | _BV(ADPS1);
    // ADC Noise Reduction Mode
    SMCR = _BV(SM0);
}


uint16_t adc_get_conversion_result(void)
{
    uint32_t millivolts = (conversion_result * CONVERSION_RATIO) / 1000;
    return millivolts;
}
