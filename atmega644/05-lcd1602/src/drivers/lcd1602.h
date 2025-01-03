#ifndef LCD1602_H_
#define LCD1602_H_

/**
 * @author Maksym Palii
 * @brief LCD1602, HD44780 based driver
 * @version 1.0
*/

#define F_CPU (16000000UL)

static void data_bus_input(void)
{
    GPIO_SET_INPUT(DATA4);
    GPIO_SET_INPUT(DATA5);
    GPIO_SET_INPUT(DATA6);
    GPIO_SET_INPUT(DATA7);
}

static void data_bus_output(void)
{
    GPIO_SET_OUTPUT(DATA4);
    GPIO_SET_OUTPUT(DATA5);
    GPIO_SET_OUTPUT(DATA6);
    GPIO_SET_OUTPUT(DATA7);
}

static void data_bus_low(void)
{
    GPIO_LOW(DATA4);
    GPIO_LOW(DATA5);
    GPIO_LOW(DATA6);
    GPIO_LOW(DATA7);
}

static void send_byte(uint8_t data)
{
    data_bus_low();
    data_bus_output();
    
    GPIO_HIGH(EN);
    if (data & 0x10) GPIO_HIGH(DATA4);
    if (data & 0x20) GPIO_HIGH(DATA5);
    if (data & 0x40) GPIO_HIGH(DATA6);
    if (data & 0x80) GPIO_HIGH(DATA7);
	GPIO_LOW(EN);

    asm("nop"::);
    asm("nop"::);

    data_bus_low();

    GPIO_HIGH(EN);
    if (data & 0x01) GPIO_HIGH(DATA4);
    if (data & 0x02) GPIO_HIGH(DATA5);
    if (data & 0x04) GPIO_HIGH(DATA6);
    if (data & 0x08) GPIO_HIGH(DATA7);
	GPIO_LOW(EN);
}

static void initialize_by_instructions(void)
{
    _delay_ms(100);

    GPIO_LOW(RS);
    GPIO_LOW(RW);
    GPIO_LOW(EN);

    data_bus_output();
    GPIO_LOW(DATA7);
    GPIO_LOW(DATA6);
    GPIO_HIGH(DATA5);
    GPIO_HIGH(DATA4);

    // Special case of 'Function Set'
    GPIO_HIGH(EN);
    asm("nop"::);
    asm("nop"::);
    GPIO_LOW(EN);

    _delay_ms(5);

    // Special case of 'Function Set'
    GPIO_HIGH(EN);
    asm("nop"::);
    asm("nop"::);
    GPIO_LOW(EN);

    _delay_us(100);

    // Special case of 'Function Set'
    GPIO_HIGH(EN);
    asm("nop"::);
    asm("nop"::);
    GPIO_LOW(EN);

    // _delay_us(100);      // this delay required for Proteus simulation (not specified in the datasheet)

    // 4bit mode selection
    GPIO_LOW(DATA7);
    GPIO_LOW(DATA6);
    GPIO_HIGH(DATA5);
    GPIO_LOW(DATA4);

    GPIO_HIGH(EN);
    asm("nop"::);
    asm("nop"::);
    GPIO_LOW(EN);
}

static uint8_t read_bf_and_ac(void)
{
    data_bus_low();
    data_bus_input();

    GPIO_LOW(RS);
    GPIO_HIGH(RW);

    uint8_t result = 0;

    GPIO_HIGH(EN);
    asm("nop"::);
    asm("nop"::);
    if (GPIO_GET_INPUT(DATA4)) result |= 0b00010000;
    if (GPIO_GET_INPUT(DATA5)) result |= 0b00100000;
    if (GPIO_GET_INPUT(DATA6)) result |= 0b01000000;
    if (GPIO_GET_INPUT(DATA7)) result |= 0b10000000;
    GPIO_LOW(EN);

    asm("nop"::);
    asm("nop"::);

    GPIO_HIGH(EN);
    asm("nop"::);
    asm("nop"::);
    if (GPIO_GET_INPUT(DATA4)) result |= 0b00000001;
    if (GPIO_GET_INPUT(DATA5)) result |= 0b00000010;
    if (GPIO_GET_INPUT(DATA6)) result |= 0b00000100;
    if (GPIO_GET_INPUT(DATA7)) result |= 0b00001000;
    GPIO_LOW(EN);

    return result;
}

void init_lcd1602(void)
{
    initialize_by_instructions();
	send_command(0b00101100);	// 'Function Set' - 4bit mode, 2 lines, 5x8 font
	send_command(0b00001111);	// 'Display ON/OFF Control' display on, cursor off and not blink    0b00001100
	send_command(0b00000001);	// 'Clear Display'
	send_command(0b00000110);	// 'Entry Mode Set' cursor shift to right
}

void send_command(uint8_t command)
{
    while (read_bf_and_ac() & 0x80);    

	GPIO_LOW(RS);
    GPIO_LOW(RW);
	send_byte(command);
}

void send_data(uint8_t data)
{
    while (read_bf_and_ac() & 0x80);    

	GPIO_HIGH(RS);
    GPIO_LOW(RW);
	send_byte(data);
}


#endif /* LCD1602_H_ */