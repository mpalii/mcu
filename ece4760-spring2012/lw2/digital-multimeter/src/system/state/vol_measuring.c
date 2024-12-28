#include <stdint.h>
#include <stdio.h>
#include "drivers/adc.h"
#include "drivers/gpio.h"
#include "drivers/lcd.h"
#include "system/events.h"
#include "system/state_machine.h"

char text_buffer_lcd_4[33]            = { 0 };

e_state handle_vol_measuring(void)
{
    if (button_event)
    {
        button_event = false;
        set_alt_adc_channel(ADC_CHANNEL_1);

        lcd_add_to_rendering("\b");
        return VCC_MEASURING;
    }

    uint16_t vcc_conversion_result = get_vcc_conversion_result();
    uint16_t alt_conversion_result = get_alt_conversion_result();
   // uint16_t millivolts = (((uint32_t) conversion_result) * INTERNAL_VOLTAGE_REFERENCE_2_56_MV * VOLTAGE_DIVIDER_IMPEDANCE) / (((uint32_t) 1024) * VOLTAGE_DIVIDER_RESISTOR_2_HOHM);

    sprintf(text_buffer_lcd_4, "\r3.Voltage\n%04u:%04u", vcc_conversion_result, alt_conversion_result);
    lcd_add_to_rendering(text_buffer_lcd_4);

    return VOL_MEASURING;
}