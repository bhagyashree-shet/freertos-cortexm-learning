#include "FreeRTOS.h"
#include "task.h"

void Task1(void *params);

int main(void){

xTaskCreate(Task1 , "Task1" , 128 , NULL , 1 ,NULL);

vTaskStartScheduler();

while(1);

}

void Task1(void *params){

while(1){



vTaskDelay(pdMS_TO_TICKS(1000));


}
}
