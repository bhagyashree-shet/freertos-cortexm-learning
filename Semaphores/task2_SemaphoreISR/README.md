# FreeRTOS Debug Notes — Semaphore Given Before Task Blocks

**Breakpoints**
- `delete`
- `break HandlerTask`
- `break SysTick_Handler`

**Run**
- `continue`

**Initial Inspection**
- Inspect semaphore:
  - `p *xBinarySemaphore`
- Observed:
  - `xTasksWaitingToReceive.uxNumberOfItems = 0`
- Tick hook fires repeatedly

**Semaphore State Change**
- Inspect again:
  - `p *xBinarySemaphore`
- Observed:
  - `uxMessagesWaiting = 1`

**Important Timing Observation**
- At this exact moment:
  - The task has **entered** `xSemaphoreTake()`
  - The task has **NOT yet blocked**
  - The kernel has **NOT moved the task** to the semaphore wait list
  - The semaphore wait list is still **empty**

- Therefore:
  - `xTasksWaitingToReceive = 0`

**Continue Execution**
- `continue`
- `uxMessagesWaiting = 1` remains set


**xSemaphoreTake() Completion**
- Task resumes execution inside `xSemaphoreTake()`
- Task sees semaphore count = 1
- Task **takes semaphore immediately**
- Task **never blocks**
- Task is **never added** to `xTasksWaitingToReceive`


- If a semaphore is given **before** a task finishes blocking:
  - The task will **not** enter the wait list
