/**
 * @author Maksym Palii
 * @brief GPIO driver, rework for matrix keyboard
 * @version 1.0
 * @date 2024 March 29
 */

#define F_CPU (8000000UL)

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

int main(void)
{
    gpio_init();

    while (true)
    {
        /* Enable column 1 (buttons: B1, B4, B7) */
        GPIO_HIGH(COLUMN1);
        
        /* Button B1 */
        // check whether button was pressed
        if (GPIO_GET_INPUT(ROW1) && !button_1_was_pressed)
        {
            button_1_was_pressed = true;
            GPIO_TOGGLE(LED1);
        }

        // check whether button was released
        if (!GPIO_GET_INPUT(ROW1) && button_1_was_pressed)
        {
            button_1_was_pressed = false;
        }
        
        /* Button B4 */
        // check whether button was pressed
        if (GPIO_GET_INPUT(ROW2) && !button_4_was_pressed)
        {
            button_4_was_pressed = true;
            GPIO_TOGGLE(LED4);
        }

        // check whether button was released
        if (!GPIO_GET_INPUT(ROW2) && button_4_was_pressed)
        {
            button_4_was_pressed = false;
        }
        
        /* Button B7 */
        // check whether button was pressed
        if (GPIO_GET_INPUT(ROW3) && !button_7_was_pressed)
        {
            button_7_was_pressed = true;
            GPIO_TOGGLE(LED7);
        }

        // check whether button was released
        if (!GPIO_GET_INPUT(ROW3) && button_7_was_pressed)
        {
            button_7_was_pressed = false;
        }

        /* Disable column 1 (buttons: B1, B4, B7) */
        GPIO_LOW(COLUMN1);

        /* Enable column 2 (buttons: B2, B5, B8) */
        GPIO_HIGH(COLUMN2);
        
        /* Button B2 */
        // check whether button was pressed
        if (GPIO_GET_INPUT(ROW1) && !button_2_was_pressed)
        {
            button_2_was_pressed = true;
            GPIO_TOGGLE(LED2);
        }

        // check whether button was released
        if (!GPIO_GET_INPUT(ROW1) && button_2_was_pressed)
        {
            button_2_was_pressed = false;
        }
        
        /* Button B5 */
        // check whether button was pressed
        if (GPIO_GET_INPUT(ROW2) && !button_5_was_pressed)
        {
            button_5_was_pressed = true;
            GPIO_TOGGLE(LED5);
        }

        // check whether button was released
        if (!GPIO_GET_INPUT(ROW2) && button_5_was_pressed)
        {
            button_5_was_pressed = false;
        }
        
        /* Button B8 */
        // check whether button was pressed
        if (GPIO_GET_INPUT(ROW3) && !button_8_was_pressed)
        {
            button_8_was_pressed = true;
            GPIO_TOGGLE(LED8);
        }

        // check whether button was released
        if (!GPIO_GET_INPUT(ROW3) && button_8_was_pressed)
        {
            button_8_was_pressed = false;
        }

        /* Disable column 2 (buttons: B2, B5, B8) */
        GPIO_LOW(COLUMN2);

        /* Enable column 3 (buttons: B3, B6, B9) */
        GPIO_HIGH(COLUMN3);
        
        /* Button B3 */
        // check whether button was pressed
        if (GPIO_GET_INPUT(ROW1) && !button_3_was_pressed)
        {
            button_3_was_pressed = true;
            GPIO_TOGGLE(LED3);
        }

        // check whether button was released
        if (!GPIO_GET_INPUT(ROW1) && button_3_was_pressed)
        {
            button_3_was_pressed = false;
        }
        
        /* Button B6 */
        // check whether button was pressed
        if (GPIO_GET_INPUT(ROW2) && !button_6_was_pressed)
        {
            button_6_was_pressed = true;
            GPIO_TOGGLE(LED6);
        }

        // check whether button was released
        if (!GPIO_GET_INPUT(ROW2) && button_6_was_pressed)
        {
            button_6_was_pressed = false;
        }
        
        /* Button B9 */
        // check whether button was pressed
        if (GPIO_GET_INPUT(ROW3) && !button_9_was_pressed)
        {
            button_9_was_pressed = true;
            GPIO_TOGGLE(LED9);
        }

        // check whether button was released
        if (!GPIO_GET_INPUT(ROW3) && button_9_was_pressed)
        {
            button_9_was_pressed = false;
        }

        /* Disable column 3 (buttons: B3, B6, B9) */
        GPIO_LOW(COLUMN3);
    }
}
