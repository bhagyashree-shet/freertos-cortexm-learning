#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

TaskHandle_t WorkerTaskHandle = NULL;
TimerHandle_t PeriodicTimerHandle = NULL;

void TimerCallback( TimerHandle_t xTimer ){


xTaskNotifyGive(WorkerTaskHandle);

}

void WorkerTask(void *params){
  while(1){
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        /* Do actual work */

}
}

int main(void){

xTaskCreate( WorkerTask,
        "Worker",
        128,
        NULL,
        2,
        &WorkerTaskHandle
);

 PeriodicTimerHandle = xTimerCreate(
        "PeriodicTimer",
        pdMS_TO_TICKS(1000),
        pdTRUE,                /* Auto-reload */
        NULL,
        TimerCallback
    );
xTimerStart(PeriodicTimerHandle, 0);

    vTaskStartScheduler();

    while (1);
}
