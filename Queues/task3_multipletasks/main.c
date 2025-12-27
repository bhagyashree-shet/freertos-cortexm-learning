#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

static void Send1Queue(void *params);
static void Send2Queue(void *params);
static void ReceiveQueue(void *params);

static QueueHandle_t xQueue; /*Initialise  Queuehandle*/

int main(void){

xQueue = xQueueCreate( 5 , sizeof(int)); /*Create queue*/

if (xQueue == NULL){
        for(;;);  /*Check Queue Empty*/
}


xTaskCreate(Send1Queue , "Send1Queue" , 128 , NULL ,1 ,NULL);
xTaskCreate(Send2Queue , "Send2Queue" , 128 , NULL ,2 ,NULL);
xTaskCreate(ReceiveQueue , "ReceiveQueue" , 128 , NULL ,3 ,NULL);

vTaskStartScheduler();

}

static void Send1Queue(void *params){
int value = 100;
while(1){

    xQueueSend(xQueue , &value , portMAX_DELAY);
    value++;
    vTaskDelay(pdMS_TO_TICKS(1000));
}

  
static void Send2Queue(void *params){
int value = 200;
while(1){

    xQueueSend(xQueue , &value , portMAX_DELAY);
    value++;
    vTaskDelay(pdMS_TO_TICKS(1000));
}


}

static void ReceiveQueue(void *params){
int received
;
while(1){
    xQueueReceive(xQueue , &received , portMAX_DELAY); /* BLOCK here until data is available */
    __asm volatile("nop");

}

}
}
