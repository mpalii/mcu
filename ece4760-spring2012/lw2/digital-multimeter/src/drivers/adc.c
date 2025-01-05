#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "adc.h"

#define ADC_REF_256     (_BV(REFS1) | _BV(REFS0))
#define ADC_REF_110     (_BV(REFS1))
#define ADC_REF_VCC     (_BV(REFS0))

#define WINDOW_SIZE (256)

static const float offset_128 = ((float) 331 - 17) / 127;
static const float offset_256 = ((float) 648 - 331) / 128;
static const float offset_384 = ((float) 965 - 648) / 128;
static const float offset_512 = ((float) 1282 - 965) / 128;
static const float offset_640 = ((float) 1597 - 1282) / 128;
static const float offset_768 = ((float) 1911 - 1597) / 128;
static const float offset_896 = ((float) 2224 - 1911) / 128;
static const float offset_1022 = ((float) 2539 - 2224) / 126;

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

float map_to_millivolts(uint16_t adc)
{
    if (adc == 0)
    {
        return 0;
    }


    if (adc >= 1 && adc < 128)
    {
        return (17 + (offset_128 * (adc - 1)));
    }

    if (adc >= 128 && adc < 256)
    {
        return (331 + (offset_256 * (adc - 128)));
    }

    if (adc >= 256 && adc < 384)
    {
        return (648 + (offset_384 * (adc - 256)));
    }

    if (adc >= 384 && adc < 512)
    {
        return (965 + (offset_512 * (adc - 384)));
    }

    if (adc >= 512 && adc < 640)
    {
        return (1282 + (offset_640 * (adc - 512)));
    }

    if (adc >= 640 && adc < 768)
    {
        return (1597 + (offset_768 * (adc - 640)));
    }

    if (adc >= 768 && adc < 896)
    {
        return (1911 + (offset_896 * (adc - 768)));
    }

    if (adc >= 896 && adc < 1023)
    {
        return (2224 + (offset_1022 * (adc - 896)));
    }

    return 2551.0;    // 1023
}
