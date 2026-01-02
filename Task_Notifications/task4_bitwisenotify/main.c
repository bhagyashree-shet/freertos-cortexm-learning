#include "FreeRTOS.h"
#include "task.h"

/* ---------------- Event bits ---------------- */
#define EVT_UART_RX   (1 << 0)
#define EVT_TIMER     (1 << 1)
#define EVT_ERROR     (1 << 2)

/* --------------- Task handle ---------------- */
static TaskHandle_t ReceiverTaskHandle = NULL;

/* --------------- Receiver Task -------------- */
void ReceiverTask(void *params)
{
    uint32_t events;

    for (;;)
    {
        /* Wait for ANY notification bits */
        events = ulTaskNotifyTake(
                    pdTRUE,            /* Clear bits on exit */
                    portMAX_DELAY      /* Block forever */
                 );
        if (events & EVT_UART_RX)
        {
            __asm volatile ("nop");  /* UART RX event */
        }

        if (events & EVT_TIMER)
        {
            __asm volatile ("nop");  /* Timer event */
        }

        if (events & EVT_ERROR)
        {
            __asm volatile ("nop");  /* Error event */
        }
    }
}

/* --------- Tick Hook = ISR Simulation -------- */
void vApplicationTickHook(void)
{
    static uint32_t tickCount = 0;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    tickCount++;

    /* Simulate different interrupt events */
    if (tickCount % 5 == 0)
    {
        xTaskNotifyFromISR(
            ReceiverTaskHandle,
            EVT_UART_RX,
            eSetBits,
            &xHigherPriorityTaskWoken
        );
    }

    if (tickCount % 10 == 0)
    {
        xTaskNotifyFromISR(
            ReceiverTaskHandle,
            EVT_TIMER,
            eSetBits,
            &xHigherPriorityTaskWoken
        );
    }

    if (tickCount % 25 == 0)
    {
        xTaskNotifyFromISR(
            ReceiverTaskHandle,
            EVT_ERROR,
            eSetBits,
            &xHigherPriorityTaskWoken
        );
    }

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/* ------------------- main ------------------- */
int main(void)
{
    xTaskCreate(
        ReceiverTask,
        "ReceiverTask",
        256,
        NULL,
        3,
        &ReceiverTaskHandle
    );

    vTaskStartScheduler();

    for (;;); /* Should never reach here */
}






        /* ---- Process events ---- */
