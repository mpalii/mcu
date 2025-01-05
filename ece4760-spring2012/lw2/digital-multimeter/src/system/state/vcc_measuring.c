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
        // enable ohmmeter 1k power line
        _gpio_set_output(OHMMETER_1K);
        _gpio_high(OHMMETER_1K);

        lcd_add_to_rendering("\b");
        return RES_MEASURING_1K;
    }

    uint16_t vcc_conversion_result = get_vcc_conversion_result();
    uint16_t alt_conversion_result = get_alt_conversion_result();

    uint16_t millivolts = map_to_millivolts(vcc_conversion_result) * VOLTAGE_DIVIDER_IMPEDANCE / VOLTAGE_DIVIDER_RESISTOR_2_HOHM;
    uint16_t centivolts = millivolts / 10;

    sprintf(text_buffer_lcd, "\r0.Supply voltage\n%04u:%04u  %1d.%02dV", vcc_conversion_result, alt_conversion_result, centivolts / 100, centivolts % 100);
    lcd_add_to_rendering(text_buffer_lcd);

    return VCC_MEASURING;
}