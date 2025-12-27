#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#define INCLUDE_vTaskDelay    1
#define configUSE_PREEMPTION                    1
#define configCPU_CLOCK_HZ                      ((unsigned long)25000000)
#define configTICK_RATE_HZ                      ((TickType_t)1000)
#define configMAX_PRIORITIES                    (5)
#define configMINIMAL_STACK_SIZE                ((unsigned short)128)
#define configTOTAL_HEAP_SIZE                   ((size_t)(10240))
#define configUSE_16_BIT_TICKS                  0
#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     0
#define configSUPPORT_DYNAMIC_ALLOCATION        1
#define INCLUDE_xTaskDelayUntil    1

/* Cortex-M3 Specifics */
#define configKERNEL_INTERRUPT_PRIORITY         255
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    191

/* Map Handlers */
#define vPortSVCHandler                         SVC_Handler
#define xPortPendSVHandler                      PendSV_Handler
#define xPortSysTickHandler                     SysTick_Handler

#endif

