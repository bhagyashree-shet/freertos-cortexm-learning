#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

static SemaphoreHandle_t xBinarySemaphore;

static void HandlerTask(void *params);

int main(void)
{
    xBinarySemaphore = xSemaphoreCreateBinary();
    if (xBinarySemaphore == NULL)
    {
        for (;;);
    }

    xTaskCreate(HandlerTask, "HandlerTask", 128, NULL, 2, NULL);

    vTaskStartScheduler();
    for (;;);
}

/* Task that waits for ISR signal */
static void HandlerTask(void *params)
{
    
    for (;;)
    {
        xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
        __asm volatile("nop");   // breakpoint: ISR event handled
    }
}

void vApplicationTickHook(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    xSemaphoreGiveFromISR(xBinarySemaphore,
                          &xHigherPriorityTaskWoken);

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

