#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "timers.h" // Required for xEventGroupSetBitsFromISR

/* Bit definitions */
#define BIT_ISR (1 << 0)

/* Global Event Group Handle */
static EventGroupHandle_t xEventGroup;

/* Task Prototypes */
void EventTask(void *params);
void vApplicationTickHook(void);

int main(void) {

    xEventGroup = xEventGroupCreate();

    if (xEventGroup != NULL) {

        xTaskCreate(EventTask, "EventTask", 128, NULL, 3, NULL);

        vTaskStartScheduler();
    }
    for (;;);
    return 0;
}

void EventTask(void *params) {
    EventBits_t uxBits;
    while (1) {
        /* Wait indefinitely for the ISR bit */
        uxBits = xEventGroupWaitBits(
            xEventGroup,    // The event group
            BIT_ISR,        // Bits to wait for
            pdTRUE,         // Clear bit on exit
            pdFALSE,        // Wait for any bit (OR logic)
            portMAX_DELAY   // No timeout
        );

        if ((uxBits & BIT_ISR) != 0) {
            __asm volatile("nop");
        }
    }
}
void vApplicationTickHook(void) {
    static uint32_t TickCount = 0;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    TickCount++;

    /* Trigger every 1000 ticks (1 second at 1kHz) */
    if (TickCount >= 1000) {
        TickCount = 0;

        /* Defer bit setting to the Timer/Daemon task */
        xEventGroupSetBitsFromISR(
            xEventGroup,
            BIT_ISR,
            &xHigherPriorityTaskWoken
        );

        /* Perform a context switch if a higher priority task was woken */
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

