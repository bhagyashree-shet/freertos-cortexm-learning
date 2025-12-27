Set task breakpoints : break TaskA
                       break TaskB
                       continue     -> Breakpoint, TaskA
                                       Breakpoint, TaskB
                                       Breakpoint, TaskA
                                       Breakpoint, TaskB
Even though:
configUSE_TIME_SLICING = 0
1.Tasks cooperate explicitly
2.Scheduler rotates Ready list on yield

When taskYIELD() is called:
Task remains READY
Task is moved to end of Ready list at its priority
Scheduler selects next READY task
PendSV performs context switch

