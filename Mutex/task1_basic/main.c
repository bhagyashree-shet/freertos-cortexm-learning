#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

SemaphoreHandle_t xMutex;

void TaskLow(void *params) {
    for(;;) {
        xSemaphoreTake(xMutex, portMAX_DELAY);
        // This loop must be long enough for TaskHigh to wake up while we are here
        for(volatile uint32_t i = 0; i < 2000000000; i++);
        xSemaphoreGive(xMutex);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void TaskHigh(void *params) {
    vTaskDelay(pdMS_TO_TICKS(50)); // Wake up while TaskLow is in the middle of its loop
    for(;;) {
        xSemaphoreTake(xMutex, portMAX_DELAY); // This will trigger Inheritance
        xSemaphoreGive(xMutex);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main(void) {
    xMutex = xSemaphoreCreateMutex();

    // Low priority = 1, High priority = 3
    xTaskCreate(TaskLow, "TaskLow", 128, NULL, 1, NULL);
    xTaskCreate(TaskHigh, "TaskHigh", 128, NULL, 3, NULL);

    vTaskStartScheduler();
    return 0;
}

