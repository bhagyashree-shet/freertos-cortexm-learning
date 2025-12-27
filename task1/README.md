SIMPLE TASK WITH NO DELAY
1. break main
   continue   : Stop execution at main. Run until main.
2. break vTaskStartScheduler
   continue   : Run until vTaskStartScheduler.
3. break Simple_Task : Stop execution at Simple_Task.
4. info registers : inspect CPU execution state.
   Here we inspect :: SP(Stack Pointer) register value is same as PSP(Process Stack Pointer)->CPU is running the task using PSP, but still in privileged mode.
                      xPSR = 0x01000000 -> Thumb State
5. p *pxCurrentTCB : Inspect Task internals. -> Shows currently running Task.
                                                Shows task stack range (stack grows downward)
                                                Displays task priority
                                                xStateListItem indicates the task is in the Ready list
                                                xEventListItem is empty (no blocking yet)

main() is not a task; it only creates tasks and starts the scheduler.
Tasks execute on PSP, not MSP.
Tasks run in privileged mode by default in FreeRTOS.
A task is represented by a TCB + stack, not just a function.
Scheduler control begins at vTaskStartScheduler().


