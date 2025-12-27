# FreeRTOS Debug Notes — Simple Task with Delay

**Step 1: Task Entry**
- `break Task1`
- `continue`
- `p *pxCurrentTCB`
  - Inspects the currently running task
  - **pcTaskName = "Task1"**
  - Task is in the **Ready list** and **RUNNING**

**Step 2: vTaskDelay() Call**
- `continue`
- `p *pxCurrentTCB`
  - `Task1` calls **vTaskDelay()**
  - Kernel moves **Task1** from the **Ready list** to the **Delayed list**
  - A context switch is requested via **PendSV**

**Step 3: Idle Task Execution**
- `break prvIdleTask`
- `continue`
  - CPU is executing the **Idle task**
  - **pxCurrentTCB** now points to the **Idle task TCB**
  - Confirms that **Task1 is BLOCKED** due to `vTaskDelay()`

**Key Observations**
- `vTaskDelay()` blocks the calling task by moving it to the **Delayed list**
- Blocking happens **before** the context switch
- The context switch occurs via **PendSV**
- When no application task is **READY**, the **Idle task** is scheduled
- **pxCurrentTCB** always points to the **currently running task**, never a blocked task

