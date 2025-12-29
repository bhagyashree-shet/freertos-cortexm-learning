# FreeRTOS Debug Notes — Binary Semaphore (Wait / Give)

**Breakpoints**
- `delete`
- `break WaitTask`
- `break GiveTask`

**Start**
- `continue`

**Inspection Before Blocking (WaitTask)**
- Stopped in **WaitTask** before blocking
- Inspect current task:
  - `p pxCurrentTCB->pcTaskName`
  - Confirms execution is inside **WaitTask**

**Blocking Observation**
- `WaitTask` calls semaphore take
- Semaphore is not available
- `WaitTask` blocks

**GiveTask Execution**
- Execution continues
- Breakpoint hit at **GiveTask**

**Semaphore Inspection**
- `p *pxBinarySemaphore`
- Observed:
  ```text
  xTasksWaitingToReceive = {
      uxNumberOfItems = 1
  }
-Therefore the `WaitTask` is blocked
