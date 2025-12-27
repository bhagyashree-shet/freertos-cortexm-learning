# FreeRTOS Debug Notes — Preemption via vTaskDelay and PendSV

**Clean Debug State**
- `delete info breakpoints`

**Debug Setup**
- `break Task1`
- `break PendSV_Handler`

**Initial Execution**
- `continue`
- Breakpoint hits **Task1**
  - Confirms task execution
- Breakpoint at **PendSV_Handler**
  - Confirms all context switches happen here

**Current Task Inspection**
- `p *pxCurrentTCB`
  - Confirms current task is **"Task1"**

**Blocking via vTaskDelay()**
- `continue`
- Task1 calls **vTaskDelay()**
- **Task1 → BLOCKED**
- Scheduler must select another **READY** task
- **PendSV triggers a context switch**
  - Breakpoint hit at **PendSV_Handler**

**Post-Context Switch Inspection**
- `p *pxCurrentTCB`
  - **pcTaskName = "Task2"**
  - **uxPriority = 1**

**Delay Expiry and Preemption**
- `continue`
- When **Task1’s delay expires**:
  - **SysTick** moves Task1 to **READY**
  - Higher priority is detected
  - **PendSV triggers again**
- Breakpoint hit at **Task1**
  - This is **preemption**
  - Task1 preempted Task2 immediately upon becoming READY

**Key Observations**
- `vTaskDelay()` causes an **immediate blocking switch**
- Preemption does **not** occur in task code
- **SysTick** decides when a task becomes READY
- **PendSV** performs all context switches
- Multiple **PendSV** executions can occur for different reasons:
  - Blocking
  - Preemption
