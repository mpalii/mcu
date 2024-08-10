#include "onewire.h"
#include "gpio.h"

#define PULL_DOWN(BUS)  (GPIO_SET_OUTPUT(BUS))
#define PULL_UP(BUS)    (GPIO_SET_INPUT(BUS))

// a.k.a. initialization procedure
bool onewire_reset(void)
{
    // reset pulse
    PULL_DOWN(ONE_WIRE_BUS);
    _delay_us(500);

    //  wait for presence pulse
    PULL_UP(ONE_WIRE_BUS);
    _delay_us(120);

    // at least one device should be on the bus
    bool is_ready = GPIO_GET_INPUT(ONE_WIRE_BUS) ? false : true;
    _delay_us(380);

    return is_ready;
}

void onewire_write(uint8_t byte)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        if (byte & _BV(i))
        {
            // MASTER WRITE "1" SLOT
            PULL_DOWN(ONE_WIRE_BUS);
            _delay_us(2);
            PULL_UP(ONE_WIRE_BUS);
            _delay_us(58);
        }
	    else
        {
            // MASTER WRITE "0" SLOT
            PULL_DOWN(ONE_WIRE_BUS);
            _delay_us(65);
            PULL_UP(ONE_WIRE_BUS);
        }
    }
}

uint8_t onewire_read(void)
{
    uint8_t result = 0b00000000;

    for (int i = 0; i < 8; i++)
    {
        PULL_DOWN(ONE_WIRE_BUS);
        _delay_us(2);
        PULL_UP(ONE_WIRE_BUS);
        _delay_us(13);
        		
        if (GPIO_GET_INPUT(ONE_WIRE_BUS))
		{
			result |= _BV(i);
		}

		_delay_us(45);

        // if (GPIO_GET_INPUT(ONE_WIRE_BUS))
        //     result |= _BV(i);
        // else
        //     // only need when bus was pulled down
        //     _delay_us(45);
    }
	
    return result;
}
