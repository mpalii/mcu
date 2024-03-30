/**
 * @author Maksym Palii
 * @brief GPIO driver, rework for matrix keyboard
 * @version 1.0
 * @date 2024 March 29
 */

#define F_CPU (8000000UL)
#define COLUMN_SIZE (3U)
#define ROW_SIZE (3U)

#include <stdbool.h>
#include <util/delay.h>
#include "drivers/gpio.h"

bool button_1_was_pressed = false;
bool button_2_was_pressed = false;
bool button_3_was_pressed = false;
bool button_4_was_pressed = false;
bool button_5_was_pressed = false;
bool button_6_was_pressed = false;
bool button_7_was_pressed = false;
bool button_8_was_pressed = false;
bool button_9_was_pressed = false;

uint8_t columns[] = { COLUMN1, COLUMN2, COLUMN3 };
uint8_t rows[] = { ROW1, ROW2, ROW3 };

bool *button_flags[COLUMN_SIZE][ROW_SIZE] = 
{
    { &button_1_was_pressed, &button_4_was_pressed, &button_7_was_pressed },
    { &button_2_was_pressed, &button_5_was_pressed, &button_8_was_pressed },
    { &button_3_was_pressed, &button_6_was_pressed, &button_9_was_pressed }
};

uint8_t leds[COLUMN_SIZE][ROW_SIZE] = 
{
    { LED1, LED4, LED7 },
    { LED2, LED5, LED8 },
    { LED3, LED6, LED9 }
};

int main(void)
{
    gpio_init();

    while (true)
    {
        for (uint8_t i = 0; i < COLUMN_SIZE; i++)
        {
            GPIO_HIGH(columns[i]);

            for (uint8_t j = 0; j < ROW_SIZE; j++)
            {
                bool row_high = GPIO_GET_INPUT(rows[j]);
                bool *button_flag = button_flags[i][j];
                uint8_t led = leds[i][j];

                // check whether button was pressed
                if (row_high && !*button_flag)
                {
                    *button_flag= true;
                    GPIO_TOGGLE(led);
                }

                // check whether button was released
                if (!row_high && *button_flag)
                {
                    *button_flag = false;
                }
            }

            GPIO_LOW(columns[i]);
        }

        // simpliest software debounce
        _delay_ms(15);
    }
}
