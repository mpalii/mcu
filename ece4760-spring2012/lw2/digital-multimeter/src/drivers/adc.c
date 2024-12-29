#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "adc.h"

#define ADC_REF_256     (_BV(REFS1) | _BV(REFS0))
#define ADC_REF_110     (_BV(REFS1))
#define ADC_REF_VCC     (_BV(REFS0))

#define WINDOW_SIZE (256)

static volatile bool is_vcc_measuring = true;
static volatile uint8_t alt_channel = ADC_CHANNEL_2;
static volatile uint8_t alt_refference = ADC_REF_256;

static uint16_t vcc_measuring_window_buffer[WINDOW_SIZE] = { 0, };
static volatile uint32_t vcc_buffer_summ = 0;
static volatile uint16_t vcc_index = 0;

static uint16_t alt_measuring_window_buffer[WINDOW_SIZE] = { 0, };
static volatile uint32_t alt_buffer_summ = 0;
static volatile uint16_t alt_index = 0;

ISR(ADC_vect)
{
    if (is_vcc_measuring)
    {
        vcc_buffer_summ -= vcc_measuring_window_buffer[vcc_index];
        vcc_measuring_window_buffer[vcc_index] = ADC;
        vcc_buffer_summ += vcc_measuring_window_buffer[vcc_index];

        if (++vcc_index > (WINDOW_SIZE - 1))
        {
            vcc_index = 0;
        }

        is_vcc_measuring = false;
        ADMUX &= _BV(ADLAR);
        ADMUX |= alt_refference | alt_channel;
    }
    else
    {
        alt_buffer_summ -= alt_measuring_window_buffer[alt_index];
        alt_measuring_window_buffer[alt_index] = ADC;
        alt_buffer_summ += alt_measuring_window_buffer[alt_index];

        if (++alt_index > (WINDOW_SIZE - 1))
        {
            alt_index = 0;
        }

        is_vcc_measuring = true;
        ADMUX &= _BV(ADLAR);
        ADMUX |= ADC_REF_256 | ADC_CHANNEL_1;
    }
}

void init_adc(void)
{
    // ADC trigger conversion on Timer/Counter0 Compare Match A
    ADCSRB = _BV(ADTS1) | _BV(ADTS0);

    // ADMUX - ADC Multiplexer Selection Register
    // ADMUX = _BV(REFS1) | _BV(MUX0);                 // Internal 1.10V Voltage Reference with external capacitor at AREF pin, Input Channel - ADC1
    ADMUX = _BV(REFS1) | _BV(REFS0) | _BV(MUX0);    // Internal 2.56V Voltage Reference with external capacitor at AREF pin, Input Channel - ADC1
    // ADMUX = _BV(REFS0) | _BV(MUX0);                 // AVCC with external capacitor at AREF pin, Input Channel - ADC1

    // ADCSRA - ADC Control and Status Register
    ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);  // ADC Enable, Prescaler Select Bits (Division Factor - 64: 18432000Hz/128 = 144kHz)

    // ADC Interrupt Enable
    ADCSRA |= _BV(ADIE);

    // ADC Auto trigger enable
    ADCSRA |= _BV(ADATE);

    // ADC Start Conversion
    ADCSRA |= _BV(ADSC);
}

uint16_t get_vcc_conversion_result(void)
{
    return (uint16_t) (vcc_buffer_summ / WINDOW_SIZE);
}


uint16_t get_alt_conversion_result(void)
{
    return (uint16_t) (alt_buffer_summ / WINDOW_SIZE);
}


void set_alt_adc_channel(uint8_t new_alt_channel)
{
    alt_channel = new_alt_channel;
}