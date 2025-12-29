#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"


static SemaphoreHandle_t xBinarySemaphore;
static void WaitTask(void *params);
static void GiveTask(void *params);

int main(void){

xBinarySemaphore = xSemaphoreCreateBinary();
if (xBinarySemaphore == NULL){


          for(;;);
}

xTaskCreate( WaitTask , "WaitTask" , 128 , NULL , 2 , NULL);
xTaskCreate( GiveTask , "GiveTask" , 128 , NULL , 1 , NULL);

vTaskStartScheduler();

for(;;);

}


void WaitTask(void *params){

while(1){

      xSemaphoreTake(xBinarySemaphore , portMAX_DELAY);
       __asm volatile("nop");  // breakpoint: semaphore acquired
}

}

void GiveTask(void *params){

while(1){
      vTaskDelay(pdMS_TO_TICKS(1000));
      xSemaphoreGive(xBinarySemaphore);

}

}
