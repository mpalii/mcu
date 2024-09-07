// /**
//  * @author Maksym Palii
//  * @brief TWI (I2C) with SHT3x Single Shot Data Acquisition Mode, NO clock stretching 
//  * (https://sensirion.com/media/documents/213E6A3B/63A5A569/Datasheet_SHT3x_DIS.pdf)
//  * @version 1.0
//  * @date 2024 August 24
//  */

// #define F_CPU           (16000000UL)
// #define DEVICE_ADDRESS  (0x88)      // TWI scanner shows 00 and 88 as valid addresses
// #define CMD_RL_CSD      (0x2416)    // Repeatability Low (RL) with Clock Stretching DISABLED (CSD)
 
// #include "drivers/gpio.h"
// #include "drivers/i2c.h"
// #include "drivers/uart644.h"
// #include <util/delay.h>

// void initialize(void);
// void print_i2c_status(void);
// void init_sht3x(void);
// struct SHT3xResult read_sht3x(void);
// void print_sht3x_result(struct SHT3xResult result);

// struct SHT3xResult
// {
//     uint16_t raw_temperature;
//     uint8_t temperature_crc;
//     uint16_t raw_humidity;
//     uint8_t humidity_crc;
// };

// int main(void) 
// {
//     initialize();
//     printf("Temperature/humidity sensor SHT3X example\r\n\r\n");

//     print_i2c_status();

//     // printf("1. Configure SHT3X with Single Shot Data Acquisition Mode no clock stretching:\r\n\r\n");
//     init_sht3x();
//     // printf("2. Init measurement and read results:\r\n\r\n");
//     struct SHT3xResult measurement_result = read_sht3x();
//     printf("3. Measurement results:\r\n\r\n");
//     print_sht3x_result(measurement_result);

//     while (true)
//     {
//         // NOP
//     }
// }

// void initialize(void)
// {
//     init_gpio();
//     stdin = stdout = stderr = init_uart(F_CPU, 9600, false);
//     init_i2c();
// }

// void print_i2c_status(void)
// {
//     uint8_t i2c_status = i2c_get_status();
//     printf("======= TWSR:0x%02X\r\n\r\n", i2c_status);
// }


// void init_sht3x(void)
// {
//     /**
//      * Single Shot Data Acquisition Mode
//      */
//     // START
//     // printf("\tSTART\r\n");
//     i2c_start();
//     // print_i2c_status();

//     // DEVICE ADDRESS + WRITE
//     // printf("\tDEVICE ADDRESS + WRITE\r\n");
//     i2c_set_data(DEVICE_ADDRESS & WRITE_BIT_MASK);
//     i2c_continue_no_ack();
//     // print_i2c_status();

//     // COMMAND (MSB)
//     // printf("\tCOMMAND (MSB)\r\n");
//     i2c_set_data(CMD_RL_CSD >> 8);
//     i2c_continue_no_ack();
//     // print_i2c_status();

//     // COMMAND (LSB)
//     // printf("\tCOMMAND (LSB)\r\n");
//     i2c_set_data(CMD_RL_CSD & 0xFF);
//     i2c_continue_no_ack();
//     // print_i2c_status();

//     // STOP
//     // printf("\tSTOP\r\n");
//     i2c_stop();
//     // print_i2c_status();
// }

// struct SHT3xResult read_sht3x(void)
// {
//     struct SHT3xResult result;

//     /** 
//      * Measurement
//      */
//     // waiting for the conversion result
//     uint8_t poll_counter = 0;
//     while (true)
//     {
//         poll_counter++;

//         // START
//         // printf("\tSTART\r\n");
//         i2c_start();
//         // print_i2c_status();

//         // DEVICE ADDRESS + READ
//         // printf("\tDEVICE ADDRESS + READ\r\n");
//         i2c_set_data(DEVICE_ADDRESS | READ_BIT_MASK);
//         i2c_continue_no_ack();
//         // print_i2c_status();

//         if (i2c_get_status() == 0x40)   // if ACK has been returned then break the loop
//         {
//             printf("\tSENSOR POLLING COUNTER: %d\r\n", poll_counter);
//             break;
//         }

//         // STOP
//         // printf("\tSTOP\r\n");
//         i2c_stop();
//         // print_i2c_status();
//     }

//     // TEMPERATURE MSB
//     printf("\tTEMPERATURE MSB\r\n");
//     i2c_continue_ack();
//     print_i2c_status();
//     result.raw_temperature = i2c_get_data() << 8;

//     // TEMPERATURE LSB
//     printf("\tTEMPERATURE LSB\r\n");
//     i2c_continue_ack();
//     print_i2c_status();
//     result.raw_temperature |= i2c_get_data();

//     // TEMPERATURE CRC
//     printf("\tTEMPERATURE CRC\r\n");
//     i2c_continue_ack();
//     print_i2c_status();
//     result.temperature_crc = i2c_get_data();

//     // HUMIDITY MSB
//     printf("\tHUMIDITY MSB\r\n");
//     i2c_continue_ack();
//     print_i2c_status();
//     result.raw_humidity = i2c_get_data() << 8;

//     // HUMIDITY LSB
//     printf("\tHUMIDITY LSB\r\n");
//     i2c_continue_ack();
//     print_i2c_status();
//     result.raw_humidity |= i2c_get_data();

//     // HUMIDITY CRC
//     printf("\tHUMIDITY CRC\r\n");
//     i2c_continue_no_ack();
//     print_i2c_status();
//     result.humidity_crc = i2c_get_data();

//     // STOP
//     printf("\tSTOP\r\n");
//     i2c_stop();
//     print_i2c_status();

//     return result;
// }

// void print_sht3x_result(struct SHT3xResult result)
// {
//     // results
//     int8_t converted_temperature = (int8_t) ((int32_t) 175 * result.raw_temperature / 0xFFFF) - 45;
//     int8_t converted_humidity = (int8_t) ((int32_t) 100 * result.raw_humidity / 0xFFFF);

//     printf("Raw temperature: 0x%4X, crc: 0x%X\r\n", result.raw_temperature, result.temperature_crc);
//     printf("Converted temperature: %dºC\r\n", converted_temperature);
//     printf("Raw humidity: 0x%4X, crc: 0x%X\r\n", result.raw_humidity, result.humidity_crc);
//     printf("Converted humidity: %d%%\r\n", converted_humidity);
// }




/*
 * Lesson_37.c
 *
 * Created: 20.12.2021 19:46:15
 * Author : Дмитрий
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

unsigned int r1_1000, r2_100=0, r3_10=0,  r4_1=0;


unsigned char TWI_status = 0;

int temper = 4598;


// Standard ASCII 5x8 font
const uint8_t font_5x8[] PROGMEM = {

    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // <space>
    0x00,0x00,0x00,0x00,0x5f,0x00,0x00,0x00,  // !
    0x00,0x00,0x00,0x03,0x00,0x03,0x00,0x00,  // "
    0x00,0x24,0x7e,0x24,0x24,0x7e,0x24,0x00,  // #
    0x00,0x2e,0x2a,0x7f,0x2a,0x3a,0x00,0x00,  // $
    0x00,0x46,0x26,0x10,0x08,0x64,0x62,0x00,  // %
    0x00,0x20,0x54,0x4a,0x54,0x20,0x50,0x00,  // &
    0x00,0x00,0x00,0x04,0x02,0x00,0x00,0x00,  // '
    0x00,0x00,0x00,0x3c,0x42,0x00,0x00,0x00,  // (
    0x00,0x00,0x00,0x42,0x3c,0x00,0x00,0x00,  // )
    0x00,0x10,0x54,0x38,0x54,0x10,0x00,0x00,  // *
    0x00,0x10,0x10,0x7c,0x10,0x10,0x00,0x00,  // +
    0x00,0x00,0x00,0x80,0x60,0x00,0x00,0x00,  // ,
    0x00,0x10,0x10,0x10,0x10,0x10,0x00,0x00,  // -
    0x00,0x00,0x00,0x60,0x60,0x00,0x00,0x00,  // .
    0x00,0x40,0x20,0x10,0x08,0x04,0x00,0x00,  // /

    0x3c,0x62,0x52,0x4a,0x46,0x3c,0x00,0x00,  // 0
    0x44,0x42,0x7e,0x40,0x40,0x00,0x00,0x00,  // 1
    0x64,0x52,0x52,0x52,0x52,0x4c,0x00,0x00,  // 2
    0x24,0x42,0x42,0x4a,0x4a,0x34,0x00,0x00,  // 3
    0x30,0x28,0x24,0x7e,0x20,0x20,0x00,0x00,  // 4
    0x2e,0x4a,0x4a,0x4a,0x4a,0x32,0x00,0x00,  // 5
    0x3c,0x4a,0x4a,0x4a,0x4a,0x30,0x00,0x00,  // 6
    0x02,0x02,0x62,0x12,0x0a,0x06,0x00,0x00,  // 7
    0x34,0x4a,0x4a,0x4a,0x4a,0x34,0x00,0x00,  // 8
    0x0c,0x52,0x52,0x52,0x52,0x3c,0x00,0x00,  // 9
    0x00,0x00,0x00,0x48,0x00,0x00,0x00,0x00,  // :
    0x00,0x00,0x80,0x64,0x00,0x00,0x00,0x00,  // ;
    0x00,0x00,0x10,0x28,0x44,0x00,0x00,0x00,  // <
    0x00,0x28,0x28,0x28,0x28,0x28,0x00,0x00,  // =
    0x00,0x00,0x44,0x28,0x10,0x00,0x00,0x00,  // >
    0x00,0x04,0x02,0x02,0x52,0x0a,0x04,0x00,  // ?

    0x00,0x3c,0x42,0x5a,0x56,0x5a,0x1c,0x00,  // @
    0x7c,0x12,0x12,0x12,0x12,0x7c,0x00,0x00,  // A
    0x7e,0x4a,0x4a,0x4a,0x4a,0x34,0x00,0x00,  // B
    0x3c,0x42,0x42,0x42,0x42,0x24,0x00,0x00,  // C
    0x7e,0x42,0x42,0x42,0x24,0x18,0x00,0x00,  // D
    0x7e,0x4a,0x4a,0x4a,0x4a,0x42,0x00,0x00,  // E
    0x7e,0x0a,0x0a,0x0a,0x0a,0x02,0x00,0x00,  // F
    0x3c,0x42,0x42,0x52,0x52,0x34,0x00,0x00,  // G
    0x7e,0x08,0x08,0x08,0x08,0x7e,0x00,0x00,  // H
    0x00,0x42,0x42,0x7e,0x42,0x42,0x00,0x00,  // I
    0x30,0x40,0x40,0x40,0x40,0x3e,0x00,0x00,  // J
    0x7e,0x08,0x08,0x14,0x22,0x40,0x00,0x00,  // K
    0x7e,0x40,0x40,0x40,0x40,0x40,0x00,0x00,  // L
    0x7e,0x04,0x08,0x08,0x04,0x7e,0x00,0x00,  // M
    0x7e,0x04,0x08,0x10,0x20,0x7e,0x00,0x00,  // N
    0x3c,0x42,0x42,0x42,0x42,0x3c,0x00,0x00,  // O

    0x7e,0x12,0x12,0x12,0x12,0x0c,0x00,0x00,  // P
    0x3c,0x42,0x52,0x62,0x42,0x3c,0x00,0x00,  // Q
    0x7e,0x12,0x12,0x12,0x32,0x4c,0x00,0x00,  // R
    0x24,0x4a,0x4a,0x4a,0x4a,0x30,0x00,0x00,  // S
    0x02,0x02,0x02,0x7e,0x02,0x02,0x02,0x00,  // T
    0x3e,0x40,0x40,0x40,0x40,0x3e,0x00,0x00,  // U
    0x1e,0x20,0x40,0x40,0x20,0x1e,0x00,0x00,  // V
    0x3e,0x40,0x20,0x20,0x40,0x3e,0x00,0x00,  // W
    0x42,0x24,0x18,0x18,0x24,0x42,0x00,0x00,  // X
    0x02,0x04,0x08,0x70,0x08,0x04,0x02,0x00,  // Y
    0x42,0x62,0x52,0x4a,0x46,0x42,0x00,0x00,  // Z
    0x00,0x00,0x7e,0x42,0x42,0x00,0x00,0x00,  // [
    0x00,0x04,0x08,0x10,0x20,0x40,0x00,0x00,  // <backslash>
    0x00,0x00,0x42,0x42,0x7e,0x00,0x00,0x00,  // ]
    0x00,0x08,0x04,0x7e,0x04,0x08,0x00,0x00,  // ^
    0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,  // _

    0x3c,0x42,0x99,0xa5,0xa5,0x81,0x42,0x3c,  // `
    0x00,0x20,0x54,0x54,0x54,0x78,0x00,0x00,  // a
    0x00,0x7e,0x48,0x48,0x48,0x30,0x00,0x00,  // b
    0x00,0x00,0x38,0x44,0x44,0x44,0x00,0x00,  // c
    0x00,0x30,0x48,0x48,0x48,0x7e,0x00,0x00,  // d
    0x00,0x38,0x54,0x54,0x54,0x48,0x00,0x00,  // e
    0x00,0x00,0x00,0x7c,0x0a,0x02,0x00,0x00,  // f
    0x00,0x18,0xa4,0xa4,0xa4,0xa4,0x7c,0x00,  // g
    0x00,0x7e,0x08,0x08,0x08,0x70,0x00,0x00,  // h
    0x00,0x00,0x00,0x48,0x7a,0x40,0x00,0x00,  // i
    0x00,0x00,0x40,0x80,0x80,0x7a,0x00,0x00,  // j
    0x00,0x7e,0x18,0x24,0x40,0x00,0x00,0x00,  // k
    0x00,0x00,0x00,0x3e,0x40,0x40,0x00,0x00,  // l
    0x00,0x7c,0x04,0x78,0x04,0x78,0x00,0x00,  // m
    0x00,0x7c,0x04,0x04,0x04,0x78,0x00,0x00,  // n
    0x00,0x38,0x44,0x44,0x44,0x38,0x00,0x00,  // o

    0x00,0xfc,0x24,0x24,0x24,0x18,0x00,0x00,  // p
    0x00,0x18,0x24,0x24,0x24,0xfc,0x80,0x00,  // q
    0x00,0x00,0x78,0x04,0x04,0x04,0x00,0x00,  // r
    0x00,0x48,0x54,0x54,0x54,0x20,0x00,0x00,  // s
    0x00,0x00,0x04,0x3e,0x44,0x40,0x00,0x00,  // t
    0x00,0x3c,0x40,0x40,0x40,0x3c,0x00,0x00,  // u
    0x00,0x0c,0x30,0x40,0x30,0x0c,0x00,0x00,  // v
    0x00,0x3c,0x40,0x38,0x40,0x3c,0x00,0x00,  // w
    0x00,0x44,0x28,0x10,0x28,0x44,0x00,0x00,  // x
    0x00,0x1c,0xa0,0xa0,0xa0,0x7c,0x00,0x00,  // y
    0x00,0x44,0x64,0x54,0x4c,0x44,0x00,0x00,  // z
    0x00,0x08,0x08,0x76,0x42,0x42,0x00,0x00,  // {
    0x00,0x00,0x00,0x7e,0x00,0x00,0x00,0x00,  // |
    0x00,0x42,0x42,0x76,0x08,0x08,0x00,0x00,  // }
    0x00,0x00,0x04,0x02,0x04,0x02,0x00,0x00,   // ~

	0x7C, 0x12, 0x11, 0x12, 0x7C,   // А 0xC0 192
	0x7F, 0x49, 0x49, 0x49, 0x31,   // Б 0xC1 193
	0x7F, 0x49, 0x49, 0x49, 0x36,   // В 0xC2 194
	0x7F, 0x01, 0x01, 0x01, 0x01,   // Г 0xC3 195
	0x60, 0x3F, 0x21, 0x3F, 0x60,   // Д 0xC4 196
	0x7F, 0x49, 0x49, 0x49, 0x41,   // Е 0xC5 197
	0x77, 0x08, 0x7F, 0x08, 0x77,   // Ж 0xC6 198
	0x22, 0x41, 0x49, 0x49, 0x36,   // З 0xC7 199
	0x7F, 0x10, 0x08, 0x04, 0x7F,   // И 0xC8 200
	0x7E, 0x10, 0x09, 0x04, 0x7E,   // Й 0xC9 201
	0x7F, 0x08, 0x14, 0x22, 0x41,   // К 0xCA 202
	0x40, 0x3E, 0x01, 0x01, 0x7F,   // Л 0xCB 203
	0x7F, 0x02, 0x0C, 0x02, 0x7F,   // М 0xCC 204
	0x7F, 0x08, 0x08, 0x08, 0x7F,   // Н 0xCD 205
	0x3E, 0x41, 0x41, 0x41, 0x3E,   // О 0xCE 206
	0x7F, 0x01, 0x01, 0x01, 0x7F,   // П 0xCF 207
	0x7F, 0x09, 0x09, 0x09, 0x06,   // Р 0xD0 208
	0x3E, 0x41, 0x41, 0x41, 0x22,   // С 0xD1 209
	0x01, 0x01, 0x7F, 0x01, 0x01,   // Т 0xD2 210
	0x07, 0x48, 0x48, 0x48, 0x3F,   // У 0xD3 211
	0x0E, 0x11, 0x7F, 0x11, 0x0E,   // Ф 0xD4 212
	0x63, 0x14, 0x08, 0x14, 0x63,   // Х 0xD5 213
	0x3F, 0x20, 0x20, 0x3F, 0x60,   // Ц 0xD6 214
	0x07, 0x08, 0x08, 0x08, 0x7F,   // Ч 0xD7 215
	0x7F, 0x40, 0x7E, 0x40, 0x7F,   // Ш 0xD8 216
	0x3F, 0x20, 0x3F, 0x20, 0x7F,   // Щ 0xD9 217
	0x01, 0x7F, 0x48, 0x48, 0x30,   // Ъ 0xDA 218
	0x7F, 0x48, 0x30, 0x00, 0x7F,   // Ы 0xDB 219
	0x00, 0x7F, 0x48, 0x48, 0x30,   // Ь 0xDC 220
	0x22, 0x41, 0x49, 0x49, 0x3E,   // Э 0xDD 221
	0x7F, 0x08, 0x3E, 0x41, 0x3E,   // Ю 0xDE 222
	0x46, 0x29, 0x19, 0x09, 0x7F,   // Я 0xDF 223
	0x20, 0x54, 0x54, 0x54, 0x78,   // а 0xE0 224
	0x3C, 0x4A, 0x4A, 0x4A, 0x31,   // б 0xE1 225
	0x7C, 0x54, 0x54, 0x28, 0x00,   // в 0xE2 226
	0x7C, 0x04, 0x04, 0x0C, 0x00,   // г 0xE3 227
	0x60, 0x3C, 0x24, 0x3C, 0x60,   // д 0xE4 228
	0x38, 0x54, 0x54, 0x54, 0x18,   // е 0xE5 229
	0x6C, 0x10, 0x7C, 0x10, 0x6C,   // ж 0xE6 230
	0x00, 0x44, 0x54, 0x54, 0x28,   // з 0xE7 231
	0x7C, 0x20, 0x10, 0x08, 0x7C,   // и 0xE8 232
	0x7C, 0x21, 0x12, 0x09, 0x7C,   // й 0xE9 233
	0x7C, 0x10, 0x28, 0x44, 0x00,   // к 0xEA 234
	0x40, 0x38, 0x04, 0x04, 0x7C,   // л 0xEB 235
	0x7C, 0x08, 0x10, 0x08, 0x7C,   // м 0xEC 236
	0x7C, 0x10, 0x10, 0x10, 0x7C,   // н 0xED 237
	0x38, 0x44, 0x44, 0x44, 0x38,   // о 0xEE 238
	0x7C, 0x04, 0x04, 0x04, 0x7C,   // п 0xEF 239
	0x7C, 0x14, 0x14, 0x14, 0x08,   // р 0xF0 240
	0x38, 0x44, 0x44, 0x44, 0x00,   // с 0xF1 241
	0x04, 0x04, 0x7C, 0x04, 0x04,   // т 0xF2 242
	0x0C, 0x50, 0x50, 0x50, 0x3C,   // у 0xF3 243
	0x08, 0x14, 0x7C, 0x14, 0x08,   // ф 0xF4 244
	0x44, 0x28, 0x10, 0x28, 0x44,   // х 0xF5 245
	0x3C, 0x20, 0x20, 0x3C, 0x60,   // ц 0xF6 246
	0x0C, 0x10, 0x10, 0x10, 0x7C,   // ч 0xF7 247
	0x7C, 0x40, 0x7C, 0x40, 0x7C,   // ш 0xF8 248
	0x3C, 0x20, 0x3C, 0x20, 0x7C,   // щ 0xF9 249
	0x04, 0x7C, 0x50, 0x50, 0x20,   // ъ 0xFA 250
	0x7C, 0x50, 0x20, 0x00, 0x7C,   // ы 0xFB 251
	0x00, 0x7C, 0x50, 0x50, 0x20,   // ь 0xFC 252
	0x28, 0x44, 0x54, 0x54, 0x38,   // э 0xFD 253
	0x7C, 0x10, 0x38, 0x44, 0x38,   // ю 0xFE 254
	0x48, 0x54, 0x34, 0x14, 0x7C    // я 0xFF 255
};





// Разбивка числа на разряды
void chislo (unsigned int chislo_z)
{
	r1_1000 = chislo_z/1000;
	r2_100 = chislo_z%1000/100;
	r3_10 = chislo_z%100/10;
	r4_1 = chislo_z%10;
}



// Настройки TWI
void TWI_settings (void)
{
	TWBR = 2; // Частота 50 кГц линии тактирования при fмк = 1 МГц
	TWSR &= ~((1<<TWPS1) | (1<<TWPS0)); // Коэф. деления = 1
}


// Старт TWI
void TWI_start (void)
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while (!(TWCR&(1<<TWINT)))
	;
}


// Стоп TWI
void TWI_stop (void)
{
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
}


// Передача адреса
void TWI_addres (void)
{
	TWDR=0b01111000;// Адрес + W / или 0b01111010
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)))
	;
}


// Передача данных TWI
void TWI_data (uint8_t data)
{
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR&(1<<TWINT)))
	;
}


// Передача команд TWI
void TWI_command (uint8_t command)
{
	TWDR = 0b10000000; // Контрольный байт
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR&(1<<TWINT)))
	;
	
	TWDR = command; // Команда
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR&(1<<TWINT)))
	;

}


// Массив команд инициализации
const uint8_t init[] PROGMEM =
{
	0xA8, // Установить multiplex ratio

	0x3F, // 1/64 duty (значение по умолчанию), 0x1F - 128x32, 0x3F - 128x64
	0xD3, // Смещение дисплея (offset)
	0x00, // Нет смещения
	0x40, // Начала строки начала разверки 0x40 с начала RAM
	0x20, // Режим автоматической адресации
	0x00, // 0 - по горизонтали с переходом на новую строку
	0xA1, // Режим разверки по странице (по X)
	// A1 - нормальный режим (слева/направо) A0 - обратный (справа/налево)
	0xC8, // Режим сканирования озу дисплея
	// для изменения системы координат
	// С0 - снизу/верх (начало нижний левый угол)
	// С8 - сверху/вниз (начало верний левый угол)
	0xDA, // Аппаратная конфигурация COM
	0x12, // 0x02 - 128x32, 0x12 - 128x64
	0x81, // Установка яркости дисплея
	0x7F, // 0x8F..0xCF   ???
	0xA4, // Режим нормальный
	0xA6, // 0xA6 - нет инверсии, 0xA7 - инверсия дисплея
	0xD5, // Настройка частоты обновления дисплея
	0x80, //+----- делитель 0-F/ 0 - деление на 1
	//+------ частота генератора. по умочанию 0x80
	0x8D, // Управление внутреним преобразователем
	0x14, // 0x10 - отключить (VCC подается извне) 0x14 - запустить внутрений DC/DC
	0xAF // Дисплей включен
};

// Функция инициализации дисплея
void display_init (void)
{
	for (uint8_t i = 0; i < sizeof init; i++)
	{
		TWI_command(pgm_read_byte(&init[i]));
	}
}


// Функция вывода символа 5*8
void print_char(uint8_t char_1)
{
	if ((char_1 >= 32) && (char_1 <= 127))
	{
		char_1 = char_1 - 32; // Смещение в таблице ASCII [32...127]	
	} 
	 else if (char_1 >= 192)
	{
		char_1 = char_1 - 96; // Смещение в таблице CP1251 [192...255]	
	}
	else char_1 = 85; //  Для экономии памяти остальные игнорируются, так как они отстутствуют в таблице
	
	for (uint8_t i = 0; i < 8; i++)
	{
		TWI_data(pgm_read_byte(&font_5x8[8*char_1 + i]));
	}
}



// Функция вывода строки 5*8
void print_string(char *str)
{
	while( *str)
	{
		print_char(*str++);
	}
}



int main(void)
{
    sei();
    
    TWI_settings();
    TWI_start();
    TWI_addres();
	
	display_init();
	
	// Очистка дисплея
	TWI_command(0x21); // Установка столбца
	TWI_command(0); // Начальный столбец
	TWI_command(127); // Конечный столбец
	TWI_command(0x22); // Установка (строки)страницы PAGE
	TWI_command(0); // Начальая страница
	TWI_command(7); // Конечная страница
	
	TWDR = 0b01000000; // Указываем, что следующиим будут байтЫ данных
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR&(1<<TWINT)))
	;
	
	for(int i = 0; i < 1024; i++)
	{
		TWI_data(0);
	}
	
	
// 	1
// 		TWI_data(0b00000000);
// 		TWI_data(0b00000100);
// 		TWI_data(0b00000010);	
// 		TWI_data(0b11111111);
// 		TWI_data(0b00000000);
// 		
// 		// 2
// 		TWI_data(0);  // 0ая колонка
// 	TWI_data(0b00111010	);  // 1ая колонка
// 	TWI_data(0b00101010	);  // 2ая колонка
// 	TWI_data(0b00101110	);  // 3ая колонка


/*
// с 0xF1 241
TWI_data(0x38);
TWI_data(0x44);
TWI_data(0x44);
TWI_data(0x44);
TWI_data(0x00);

// Пробел
TWI_data(0b00000000);
TWI_data(0b00000000);
TWI_data(0b00000000);
TWI_data(0b00000000);
TWI_data(0b00000000);

// т 0xF2 242
TWI_data(0x04);
TWI_data(0x04);
TWI_data(0x7C);
TWI_data(0x04);
TWI_data(0x04);

// Пробел
TWI_data(0b00000000);
TWI_data(0b00000000);
TWI_data(0b00000000);
TWI_data(0b00000000);
TWI_data(0b00000000);

 // у 0xF3 243
 TWI_data(0x0C);
 TWI_data(0x50);
 TWI_data(0x50);
 TWI_data(0x50);
 TWI_data(0x3C);
  
 // Пробел
 TWI_data(0b00000000);
 TWI_data(0b00000000);
 TWI_data(0b00000000);
 TWI_data(0b00000000);
 TWI_data(0b00000000);
 
 
   
 // ф 0xF4 244
 TWI_data(0x08);
 TWI_data(0x14);
 TWI_data(0x7C);
 TWI_data(0x14);
 TWI_data(0x08);

// Пробел
TWI_data(0b00000000);
TWI_data(0b00000000);
TWI_data(0b00000000);
TWI_data(0b00000000);
TWI_data(0b00000000);

*/


// print_char('D');
// print_char(' ');
// print_char('b');
// print_char(' ');
// print_char('l');
// print_char(' ');


print_string("Note that the bit rates are quoted for the transfers between controller" 
            // "(master) and target (slave) without clock stretching..."
            // " the target device, as well as per-byte ACK/NACK bits. Thus the actual transfer r"
            // "ate of user data is lower than those peak bit rates alone would imply. For exampl"
            // "e, if each interaction with a target inefficiently allows only 1 byte of data to "
            // "be transferred, the data rate will be less than half the peak bit rate."
            );


// chislo(temper);

// print_char(r1_1000 + '0');
// print_char(r2_100 + '0');
// print_char(r3_10 + '0');
// print_char(r4_1 + '0');

TWI_stop();

	
    while (1) 
    {
    }
}
