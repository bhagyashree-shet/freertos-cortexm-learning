#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
//Enable #define configUSE_COUNTING_SEMAPHORES 1

SemaphoreHandle_t xCountSem;

void HandlerTask(void *p)
{
    while (1)
    {
        xSemaphoreTake(xCountSem, portMAX_DELAY);
        __asm volatile("nop");   
    }
}

/* Tick Hook runs in ISR context */
void vApplicationTickHook(void)
{
    static BaseType_t xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;

    xSemaphoreGiveFromISR(xCountSem, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

int main(void)
{
    /* Max count = 10, initial count = 0 */
    xCountSem = xSemaphoreCreateCounting(10, 0);

    xTaskCreate(HandlerTask, "Handler", 128, NULL, 2, NULL);

    vTaskStartScheduler();
    for (;;);
}
