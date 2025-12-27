#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

void SendQueue(void *params);
void ReceiveQueue(void *params);

static QueueHandle_t xQueue; /*Initialise  Queuehandle*/

int main(void){

xQueue = xQueueCreate( 5 , sizeof(int)); /*Create queue*/

if (xQueue == NULL){
        for(;;);  /*Check Queue Empty*/
}


xTaskCreate(SendQueue , "SendQueue" , 128 , NULL ,1 ,NULL);
xTaskCreate(ReceiveQueue , "ReceiveQueue" , 128 , NULL ,1 ,NULL);

vTaskStartScheduler();

}

void SendQueue(void *params){
int value = 0;
while(1){
    value++;
    xQueueSend(xQueue , &value , portMAX_DELAY);
    vTaskDelay(pdMS_TO_TICKS(1000));
}

}

void ReceiveQueue(void *params){
int received;
while(1){
    xQueueReceive(xQueue , &received , pdMS_TO_TICKS(500)); /* BLOCK here until data is available */
    __asm volatile("nop");

}

}
