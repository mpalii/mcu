/**
 * @author Maksym Palii
 * @brief Dynamic lighting, 4-digits seven-segment display with common cathode
 * @version 1.0
 * @date 2024 February 20
 * @see https://pixeljoint.com/forum/forum_posts.asp?TID=18755
 */

#define F_CPU 8000000UL
#define DELAY 1000

#include <stdbool.h>
#include <util/delay.h>
#include "drivers/sn74hc595.h"
#include "drivers/gpio.h"

uint16_t alphabet[] = 
{
    0x0000,     // space
    0x6606,	    // !
    0xAA00,	    // “
    0xFFFF,	    // #    NOT IMPLEMENTED
    0xFFFF,	    // $    NOT IMPLEMENTED
    0x9249,	    // %
    0x2FAE,	    // &
    0x6200,	    // '
    0x2442,	    // (
    0x4224,	    // )
    0x4A40,	    // *
    0x6F60,	    // +
    0x0026,     // ,
    0x0600,	    // -
    0x0006,	    // .
    0x1248,	    // /
    0xFDBF,	    // 0
    0xE66F,	    // 1
    0xF7EF,	    // 2
    0xF73F, 	// 3
    0xBFF3,	    // 4
    0xFE7F,	    // 5
    0x8FBF,	    // 6
    0xF333,	    // 7
    0x75FF,	    // 8
    0xFBF3,	    // 9
    0x4040,	    // :
    0x4044,	    // ;
    0x4840,	    // <
    0x0F0F,	    // =
    0x2120,	    // >
    0xEA06,	    // ?
    0xFB8F,	    // @
    0xFDFD,	    // A
    0xEFDF,	    // B
    0xFCCF,	    // C
    0xEDDE,	    // D
    0xFECF,	    // E
    0xFCEC,	    // F
    0xFCDF,	    // G
    0xDFFD,	    // H
    0xF66F,	    // I
    0x333F,	    // J
    0xDEFD,	    // K
    0xCCCF,	    // L
    0xFFB9,	    // M
    0xDFFB,	    // N
    0xFDDF,	    // O
    0xF9FC,	    // P
    0xF9BF,	    // Q
    0xFDED,	    // R
    0xFC3F,	    // S
    0xFF66,	    // T
    0x99FF,	    // U
    0x99F6,	    // V
    0x9DFF,	    // W
    0x9F69,	    // X
    0x9F66,	    // Y
    0xF3CF,	    // Z
    0x6446,	    // [
    0x8421,	    // backslash
    0x6226,	    // ]
    0x4A00,	    // ^
    0x000F,	    // _
    0xFFFF,	    // `    NOT IMPLEMENTED
    0x69BD,	    // a
    0x8E9E,	    // b
    0x7887,	    // c
    0x1797,	    // d
    0x6BE7,	    // e
    0xF8E8,	    // f
    0x797E,	    // g
    0x8E99,	    // h
    0x202F,	    // i
    0x101F,	    // j
    0x89E9,	    // k
    0xC444,	    // l
    0x7B99,	    // m
    0xE999,	    // n
    0x6996,	    // o
    0xE9E8,	    // p
    0xEAE3,	    // q
    0xE988,	    // r
    0x342C,	    // s
    0x4F44,	    // t
    0x999F,	    // u
    0x9996,	    // v
    0x99DF,	    // w
    0x9969,	    // x
    0x9964,	    // y
    0xF24F,	    // z
    0x6CC6,	    // {
    0x4444,	    // |
    0x6336,	    // }
    0x05A0	    // ~
};

int main(void)
{
    gpio_init();

    char *message  = "Simple message with ASCII standard";
    
    uint16_t i = 0;
    while (message[i] != '\0')
    {
        uint8_t ascii_character = message[i];
        if (ascii_character > 31 && ascii_character < 127)
        {
            shift_data(alphabet[ascii_character - 32]);
        }
        else
        {
            shift_data(0xFFFF);
        }

        i++;
        _delay_ms(DELAY);
    }

    shift_data(0);

    while (true)
    {
        // NOP
    }
}
