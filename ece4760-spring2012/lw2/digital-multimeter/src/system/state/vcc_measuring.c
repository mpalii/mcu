#include <stdint.h>
#include <stdio.h>
#include "drivers/adc.h"
#include "drivers/gpio.h"
#include "drivers/lcd.h"
#include "system/events.h"
#include "system/state_machine.h"

char text_buffer_lcd[33]            = { 0 };

e_state handle_vcc_measuring(void)
{
    if (button_event)
    {
        button_event = false;
        set_alt_adc_channel(ADC_CHANNEL_2);
        // enable ohmmeter 1k power line
        _gpio_set_output(OHMMETER_1K);
        _gpio_high(OHMMETER_1K);

        lcd_add_to_rendering("\b");
        return RES_MEASURING_1K;
    }

    uint16_t conversion_result = get_vcc_conversion_result();
    uint16_t millivolts = (((uint32_t) conversion_result) * INTERNAL_VOLTAGE_REFERENCE_2_56_MV * VOLTAGE_DIVIDER_IMPEDANCE) / (((uint32_t) 1024) * VOLTAGE_DIVIDER_RESISTOR_2_HOHM);
    uint16_t centivolts = millivolts / 10;

    sprintf(text_buffer_lcd, "\r0.Supply voltage\n%04u:----  %1d.%02dV", conversion_result, centivolts / 100, centivolts % 100);
    lcd_add_to_rendering(text_buffer_lcd);

    return VCC_MEASURING;
}