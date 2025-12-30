#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <stdio.h> // For logging visibility

// CHANGE: Use a Binary Semaphore to allow inversion
static SemaphoreHandle_t xInversionSem;

void TaskLow(void *params);
void TaskHigh(void *params);
void TaskMed(void *params);

int main(void){
    // CHANGE: Binary semaphores do NOT have priority inheritance
    xInversionSem = xSemaphoreCreateBinary();
    xSemaphoreGive(xInversionSem); // Initialize as available

    xTaskCreate(TaskLow,  "TaskLow",  128, NULL, 1, NULL); // Priority 1
    xTaskCreate(TaskMed,  "TaskMed",  128, NULL, 2, NULL); // Priority 2
    xTaskCreate(TaskHigh, "TaskHigh", 128, NULL, 3, NULL); // Priority 3

    vTaskStartScheduler();
    for(;;);
}

void TaskLow(void *params){ while(1){
        printf("Low: Attempting to take semaphore\n");
        xSemaphoreTake(xInversionSem, portMAX_DELAY);
        printf("Low: Got semaphore, starting long work...\n");

        // Simulate long work that doesn't block (using a loop, not vTaskDelay)
        // If you use vTaskDelay, TaskLow will block and yield to TaskMed normally.
        for(volatile uint32_t i = 0; i < 10000000; i++);

        printf("Low: Work finished, releasing semaphore\n");
        xSemaphoreGive(xInversionSem);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void TaskMed(void *params){
    vTaskDelay(pdMS_TO_TICKS(100)); // Start shortly after Low
    while(1){
        printf("Med: Running (this blocks High via Low)...\n");
        // Medium task does heavy work without needing the semaphore
        for(volatile uint32_t i = 0; i < 50000000; i++);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}


void TaskHigh(void *params){
    vTaskDelay(pdMS_TO_TICKS(150)); // Start after Low has the semaphore
    while(1){
        printf("High: Attempting to take semaphore\n");
        xSemaphoreTake(xInversionSem, portMAX_DELAY); // Will block here

        printf("High: FINALLY got semaphore!\n");
        xSemaphoreGive(xInversionSem);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

  
