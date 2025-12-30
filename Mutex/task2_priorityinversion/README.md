# FreeRTOS Debug Notes — Priority Inversion (Binary Semaphore)

**Set Up the Trap**
- Breakpoints:
  - `break main.c:34`  (TaskLow after taking semaphore)
  - `break main.c:47`  (TaskMed work — inversion point)
  - `break main.c:60`  (TaskHigh work)
- Start execution:
  - `continue`

**Catch TaskLow (Setup)**
- Breakpoint hit in **TaskLow**
- Verify:
  - `p pxCurrentTCB->pcTaskName`
  - `p pxCurrentTCB->uxPriority`
- Check time:
  - `p xTickCount`
- Confirms TaskLow holds semaphore and others have not woken yet

**Trigger the Inversion**
- `continue`
- Binary semaphore → **no priority inheritance**
- When delays expire, scheduler preempts TaskLow

**Observe the Inversion**
- Breakpoint hit in **TaskMed**
- Verify:
  - `p pxCurrentTCB->pcTaskName`
  - `p pxCurrentTCB->uxPriority`
- TaskHigh (priority 3) has not hit its breakpoint
- TaskHigh is **blocked on semaphore**
- TaskMed (priority 2) is running

**Proof**
- TaskMed is executing while TaskHigh is blocked
- TaskLow is preempted while holding the resource
- This is **unbounded priority inversion**

**Resolution**
- `continue`
- Only after TaskMed finishes and blocks:
  - TaskLow runs again
  - Releases semaphore
  - TaskHigh finally executes

**Summary**
- Low task took the resource
- High task blocked on the resource
- Medium task preempted the low task
- High task stayed blocked for entire medium task execution
- This demonstrates **unbounded priority inversion**
