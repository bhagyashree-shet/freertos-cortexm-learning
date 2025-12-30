# FreeRTOS Debug Notes — Mutex and Priority Inheritance

**Breakpoints**
- `break TaskLow`
- `break TaskHigh`
- `continue`

**Why**
- Stops execution exactly where the mutex is taken
- Allows inspection of mutex ownership and task priority changes

**Inspect the Currently Running Task**
- `p *pxCurrentTCB`

**What to Observe**
- **pcTaskName** → which task is currently running  
- **uxPriority** → current priority (may be inherited)  
- **uxBasePriority** → original task priority  
- **uxMutexesHeld** → number of mutexes currently held  

**Key Learning**
- **uxPriority may change**
- **uxBasePriority never changes**

**Inspect the Mutex Internals**
- `p *xMutex`

**What to Observe**
- **xSemaphore.xMutexHolder** → task holding the mutex  
- **uxMessagesWaiting**
  - `1` → mutex is free  
  - `0` → mutex is taken  
- **xTasksWaitingToReceive** → tasks blocked on the mutex  

- A mutex is implemented internally as a **queue**
- Mutex ownership is **explicitly tracked** by the kernel

**Observe TaskLow Taking the Mutex**
- Step through the code:
  - `step`
  - `finish`
- Inspect again:
  - `p *pxCurrentTCB`

**Expected**
- **uxMutexesHeld = 1**
- **uxPriority    = 1**

**Meaning**
- TaskLow owns the mutex
- No priority inheritance yet

**Observe TaskHigh Attempting to Take the Mutex**
- `continue`
- TaskHigh attempts to take the same mutex and blocks
- Inspect:
  - `p *pxCurrentTCB`

**Expected When Inheritance Happens**
- **uxPriority     = 3** (boosted)  
- **uxBasePriority = 1** (original)  

**Meaning**
- Priority inversion detected
- Kernel temporarily boosts TaskLow’s priority

**After the Mutex Is Released**
- `continue`
- `p *pxCurrentTCB`

**Expected**
- **uxPriority     = 1**
- **uxBasePriority = 1**
- **uxMutexesHeld  = 0**

**Meaning**
- Priority inheritance removed
- System restored to normal scheduling
