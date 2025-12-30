#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

static SemaphoreHandle_t xMutex;
void TaskLow(void *params);
void TaskHigh(void *params);

int main(void){

xMutex = xSemaphoreCreateMutex();


xTaskCreate(TaskLow , "TaskLow" , 128 , NULL , 1 , NULL);
xTaskCreate(TaskHigh , "TaskHigh" , 128 , NULL , 3 , NULL);
vTaskStartScheduler();

for(;;);

}


void TaskLow(void *params)
{
    while (1)
    {   xSemaphoreTake(xMutex, portMAX_DELAY);

        /* Hold mutex long enough */
        vTaskDelay(pdMS_TO_TICKS(1000));

        xSemaphoreGive(xMutex);
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

void TaskHigh(void *params)
{
    /* Let TaskLow run first */
    vTaskDelay(pdMS_TO_TICKS(10));

    while (1)
     {   // Let TaskLow take mutex first
    //vTaskDelay(pdMS_TO_TICKS(50));
        xSemaphoreTake(xMutex, portMAX_DELAY);
        xSemaphoreGive(xMutex);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}


