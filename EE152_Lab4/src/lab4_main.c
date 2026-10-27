// Include FreeRTOS headers.
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "portmacro.h"
#include "task.h"
#include "timers.h"
#include "stm32l4xx.h"
#include "stm32l432xx.h"
#include <stdbool.h>
#include "lib_ee152.h"
#include <math.h>

// Write a sawtooth out on DAC 1, which drives Nano A3.
// The spec: frequency=100Hz, amplitude of roughly 3.3V.
// Remember that 100Hz is ?? FreeRTOS ticks, and 3.3V is an argument of ??
// to analogWrite().
void task_sawtooth (void * pvParameters) {
    int val = 0;                       
    while (1) {
        analogWrite (A3, val * 28);    
        val = (val + 1) % 10;          
        vTaskDelay (1);                
    }
}

#define BLINK_GREEN_DELAY ( 500 / portTICK_PERIOD_MS )
void task_blink_green (void *pvParameters) { //A4
    // ... write me...
    volatile unsigned int green = 0;
    while (1) {
        green = !green;
        digitalWrite(D13, green);
        vTaskDelay(BLINK_GREEN_DELAY);
    }
    
}

int main() {
    //clock_setup_16MHz();		// 16 MHz, AHB and APH1/2 prescale=1x
    clock_setup_80MHz();		// 80 MHz, AHB and APH1/2 prescale=1x
    pinMode(D13, "OUTPUT");

    // Create tasks.
    // ... write me...
    TaskHandle_t task_handle_blinkgreen = NULL;
    BaseType_t task_create_OK = xTaskCreate (
            task_blink_green, "Blink Green",
            100, // stack size in words
            NULL, // parameter passed into task, e.g. "(void *) 1"
            1+tskIDLE_PRIORITY, // priority
            &task_handle_blinkgreen);
    if (task_create_OK != pdPASS) for ( ;; );
    vTaskSetApplicationTaskTag (task_handle_blinkgreen, (void *)3);

    TaskHandle_t task_handle_sawtooth = NULL;
    task_create_OK = xTaskCreate (
            task_sawtooth, "Sawtooth",
            100, // stack size in words
            NULL, // parameter passed into task, e.g. "(void *) 1"
            2+tskIDLE_PRIORITY, // priority
            &task_handle_sawtooth);
    if (task_create_OK != pdPASS) for ( ;; );
    vTaskSetApplicationTaskTag (task_handle_sawtooth, (void *)3);

    vTaskStartScheduler();
}