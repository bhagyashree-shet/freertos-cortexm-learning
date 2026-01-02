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
void vApplicationTickHook(void)
{
    static int tickCount = 0;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    tickCount++;

    if (tickCount <= 5)   // send 5 signals
    {
        vTaskNotifyGiveFromISR(
            ReceiverTaskHandle,
            &xHigherPriorityTaskWoken
        );
    }
}
void ReceiverTask(void *params)
{
    for (;;)
    {
        uint32_t count = ulTaskNotifyTake(
                            pdTRUE,          // Clear count on exit
                            portMAX_DELAY    // Wait forever
                         );

        // One wake-up per notification
        __asm volatile("nop"); // breakpoint here
    }
}

