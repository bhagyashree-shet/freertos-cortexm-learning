In  FreeRTOSConfig.h : 
#define configUSE_PREEMPTION        1
#define configUSE_TIME_SLICING     1

1. break TaskA
   break TaskB
  continue -> Breakpoint, TaskA
              Breakpoint, TaskB
              Breakpoint, TaskA
              Breakpoint, TaskB  --> Both tasks are running.CPU is being shared.Time slicing is active.

At each SysTick interrupt:
Kernel checks READY tasks at current priority
Since multiple tasks exist at same priority
Current task is moved to end of Ready list
Next task in Ready list is selected
PendSV performs the context switch

