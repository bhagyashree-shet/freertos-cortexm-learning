1. delete
   info breakpoints -> Clean Debug State

2. break Task1
   break PendSV_Handler -> Task1 - confirms task execution
                           PendSV_Handler → all context switches happen here

3. p *pxCurrentTCB  -> Confirms Current Task - "Task1"
4. continue -> Task1 calls vTaskDelay()
               Task1 → BLOCKED
               Scheduler must select another READY task
               PendSV triggers a context switch            -> Breakpoint, PendSV_Handler
5. p *pxCurrentTCB  -> pcTaskName = "Task2"  uxPriority = 1
6. continue -> When Task1’s delay expires: SysTick moves Task1 to READY Higher priority is detected PendSV triggers again
               You will hit:Breakpoint, Task1  -> This is preemption. Task1 preempted Task2 immediately upon becoming READY


vTaskDelay() causes an immediate blocking switch
1.Preemption does not occur in task code
2.SysTick decides when a task becomes READY
3.PendSV performs all context switches
4.Multiple PendSV executions can occur for different reasons:
  Blocking
  Preemption
