#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"

#define BIT_TASK1 (1 << 0)
#define BIT_TASK2 (1 << 1)

EventGroupHandle_t xEventGroup;

void Task1(void *params) {
    vTaskDelay(pdMS_TO_TICKS(1000));
    xEventGroupSetBits(xEventGroup, BIT_TASK1);
    vTaskSuspend(NULL); // Stop here so TaskWait can run
volatile TickType_t t = xTaskGetTickCount();
}

void Task2(void *params) {
    vTaskDelay(pdMS_TO_TICKS(2000));
    xEventGroupSetBits(xEventGroup, BIT_TASK2);
    vTaskSuspend(NULL); // Stop here so TaskWait can run
volatile TickType_t t = xTaskGetTickCount();
}

void TaskWait(void *params) {
    // Priority 2: This will run as soon as bits are ready
    xEventGroupWaitBits(
       xEventGroup,
        BIT_TASK1 | BIT_TASK2,
        pdTRUE, // Clear bits on exit
        pdTRUE, // Wait for ALL bits (AND logic)
        pdMS_TO_TICKS(1500)
    );
volatile TickType_t t = xTaskGetTickCount();
    __asm volatile("nop"); // Breakpoint here
    vTaskSuspend(NULL);
}

int main(void) {
  xEventGroup = xEventGroupCreate();

    xTaskCreate(Task1, "Task1", 128, NULL, 1, NULL);
    xTaskCreate(Task2, "Task2", 128, NULL, 1, NULL);
    xTaskCreate(TaskWait, "TaskWait", 128, NULL, 3, NULL);

    vTaskStartScheduler();
    return 0;
}
