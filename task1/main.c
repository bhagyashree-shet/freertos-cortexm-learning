#include "FreeRTOS.h"
#include "task.h"

void Simple_Task(void *params){

while(1){

}

}


int main(void){

xTaskCreate(Simple_Task , "Simple_Task" , 128 , NULL , 1 ,NULL);

vTaskStartScheduler();

while(1);
}
