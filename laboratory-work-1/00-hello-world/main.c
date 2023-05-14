/**
 * @author Maksym Palii
 * @brief Simple bare metal 'Hello World' example without standard AVR libraries
 * @version 1.0
 * @date 2023 May 14
 */

// No includes at all

int main (void)
{
    // Configure the data direction for pin 0 (port D) as OUTPUT 
    *(unsigned char *)(0x2a) = 0b00000001;

    // Set pin 0 (port D) driven HIGH
    *(unsigned char *)(0x2b) = 0b00000001;

    while (1)
    {
        // NOP 
    }
}
