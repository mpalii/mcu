/*
 * FreeRTOS.c
 *
 * Created: 03/07/2022 20:40:53
 * Author : mpalii
 */ 

#include <avr/io.h>
#include "FreeRTOS.h"
#include "task.h"

void vApplicationIdleHook(void)
{
    /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
    to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
    task.  It is essential that code added to this hook function never attempts
    to block in any way (for example, call xQueueReceive() with a block time
    specified, or call vTaskDelay()).  If the application makes use of the
    vTaskDelete() API function (as this demo application does) then it is also
    important that vApplicationIdleHook() is permitted to return to its calling
    function, because it is the responsibility of the idle task to clean up
    memory allocated by the kernel to any task that has since been deleted. */
}

void myTask1(void *p) {
	while(1) {
		PORTD ^= _BV(PORTD0);
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

void myTask2(void *p) {
	while(1) {
		PORTD ^= _BV(PORTD1);
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

void myTask3(void *p) {
	while(1) {
		PORTD ^= _BV(PORTD2);
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

void myTask4(void *p) {
	while(1) {
		PORTD ^= _BV(PORTD3);
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

void myTask5(void *p) {
	while(1) {
		PORTD ^= _BV(PORTD4);
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

void myTask6(void *p) {
	while(1) {
		PORTD ^= _BV(PORTD5);
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

void myTask7(void *p) {
	while(1) {
		PORTD ^= _BV(PORTD6);
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

void myTask8(void *p) {
	while(1) {
		PORTD ^= _BV(PORTD7);
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

int main(void)
{
	DDRD = 0xFF;
	
	xTaskCreate(myTask1, "task1", 100, NULL, tskIDLE_PRIORITY, NULL);
	xTaskCreate(myTask2, "task2", 100, NULL, tskIDLE_PRIORITY, NULL);
	xTaskCreate(myTask3, "task3", 100, NULL, tskIDLE_PRIORITY, NULL);
	xTaskCreate(myTask4, "task4", 100, NULL, tskIDLE_PRIORITY, NULL);
	xTaskCreate(myTask5, "task5", 100, NULL, tskIDLE_PRIORITY, NULL);
	xTaskCreate(myTask6, "task6", 100, NULL, tskIDLE_PRIORITY, NULL);
	xTaskCreate(myTask7, "task7", 100, NULL, tskIDLE_PRIORITY, NULL);
	xTaskCreate(myTask8, "task8", 100, NULL, tskIDLE_PRIORITY, NULL);
	vTaskStartScheduler();
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

