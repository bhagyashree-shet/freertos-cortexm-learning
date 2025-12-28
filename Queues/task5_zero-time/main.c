#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

static void Sender(void *params);
static void Receiver(void *params);

static QueueHandle_t xQueue;

int main(void){

xQueue = xQueueCreate( 5 , sizeof(int));
if (xQueue == NULL){
for(;;);
}

xTaskCreate( Sender , "Sender" , 128 , NULL , 1 , NULL);
xTaskCreate( Receiver , "Receiver" , 128 , NULL , 2 , NULL);

vTaskStartScheduler();

for(;;);

}

void Sender(void *params){
  
int value = 42;

while(1){

vTaskDelay(pdMS_TO_TICKS(500));
xQueueSend( xQueue , &value , portMAX_DELAY);
value++;

}

}

void Receiver(void *params){

int received;
BaseType_t ret;
while(1){

 ret = xQueueReceive(xQueue, &received, 0); // ZERO TIMEOUT

        if (ret == pdTRUE)
        {
            __asm volatile("nop");   // data received breakpoint
        }
        else
            {
            __asm volatile("nop");   // empty queue breakpoint
        }

vTaskDelay(pdMS_TO_TICKS(200));
//  taskYIELD();   // allow lower-priority task to run
}
}
