#include "FreeRTOS.h"
#include "task.h"

static TaskHandle_t xReceiverTaskHandle = NULL;

void ReceiverTask(void *params);
void SenderTask(void *params);

int main(void){

xTaskCreate(ReceiverTask , "ReceiverTask" , 128 , NULL , 2 , &xReceiverTaskHandle);
xTaskCreate(SenderTask , "SenderTask" , 128 , NULL , 1 , NULL);


vTaskStartScheduler();

for(;;);

}

void SenderTask(void *params){

for(;;){

vTaskDelay(pdMS_TO_TICKS(1000));

xTaskNotifyGive(xReceiverTaskHandle);

}
}

void ReceiverTask(void *params){

for(;;){

ulTaskNotifyTake( pdTRUE,        // clear count on exit (binary behavior)
            portMAX_DELAY  // block indefinitely
);
__asm volatile("nop");

}
}
