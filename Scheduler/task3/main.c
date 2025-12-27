#include "FreeRTOS.h"
#include "task.h"

void Task1(void *params); /*Declare Task1*/
void Task2(void *params); /*Declare Task2*/

int main(void){

xTaskCreate(Task1 , "Task1" , 128 , NULL , 2 ,NULL); /*Task1 with higher priority*/
xTaskCreate(Task2 , "Task2" , 128 , NULL , 1 ,NULL);
vTaskStartScheduler();

while(1);

}

void Task1(void *params){

while(1){

/* Busy loop */
        __asm volatile("nop");

}
}

void Task2(void *params){

while(1){
/* Busy loop */
        __asm volatile("nop"); /*no operation*/
}
}
