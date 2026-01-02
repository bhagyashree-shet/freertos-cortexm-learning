#include "FreeRTOS.h"
#include "task.h"

// Task handle MUST be initialized via xTaskCreate
static TaskHandle_t ReceiverTaskHandle = NULL;

void ReceiverTask(void *params);


int main(void) {
    // Corrected: Pass the address of the handle to store it
    xTaskCreate(ReceiverTask, "ReceiverTask", 128, NULL, 3, &ReceiverTaskHandle);

    vTaskStartScheduler();
    for(;;);
}

void vApplicationTickHook(void) {
    static int once = 0;

    if( once == 0 )
    {
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        vTaskNotifyGiveFromISR(ReceiverTaskHandle, &xHigherPriorityTaskWoken);
        once = 1;
    }
}

void ReceiverTask(void *params) {
    for(;;) {
        // Task blocks here and system enters prvIdleTask
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // Breakpoint here to see it wake up!
        __asm volatile("nop");
    }
}

