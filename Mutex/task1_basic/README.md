# FreeRTOS Debug Notes — Mutex + Priority Inheritance

Breakpoints  
break TaskLow  
break TaskHigh  
continue  

Stops execution exactly where the mutex is taken and allows inspection of ownership and priority changes.

Inspect the currently running task  

p *pxCurrentTCB  

Observe:  
pcTaskName → which task is running  
uxPriority → current priority (may be inherited)  
uxBasePriority → original priority  
uxMutexesHeld → number of mutexes held  

Key fact:  
uxPriority may change  
uxBasePriority never changes  

Inspect mutex internals  

p *xMutex  

Observe:  
xSemaphore.xMutexHolder → task holding the mutex  
uxMessagesWaiting  
1 → mutex free  
0 → mutex taken  
xTasksWaitingToReceive → tasks blocked on mutex  

Key fact:  
A mutex is internally implemented as a queue  
Mutex ownership is explicitly tracked  

TaskLow takes the mutex  

step  
finish  

Inspect again:  

p *pxCurrentTCB  

Expected:  
uxMutexesHeld = 1  
uxPriority    = 1  
uxBasePriority = 1  

Meaning:  
TaskLow owns the mutex  
No priority inheritance yet  

TaskHigh attempts to take the mutex  

continue  

TaskHigh blocks on the mutex  

Inspect current task:  

p *pxCurrentTCB  

Expected when inheritance happens:  
uxPriority     = 3  
uxBasePriority = 1  
uxMutexesHeld  = 1  

Meaning:  
Priority inversion detected  
Kernel temporarily boosts TaskLow’s priority  

After mutex is released  

continue  
p *pxCurrentTCB  

Expected:  
uxPriority     = 1  
uxBasePriority = 1  
uxMutexesHeld  = 0  

Meaning:  
Inheritance removed  
System restored to normal scheduling
