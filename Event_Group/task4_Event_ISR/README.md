# FreeRTOS Debug Notes — Event Group Set from ISR (Tick Hook → Daemon → Task)

**The Wait**
- `EventTask` called `xEventGroupWaitBits`
- Task entered the **Blocked** state
- Confirmed when the first `EventTask` breakpoint was hit and execution did not progress further

**The Accumulation**
- System clock ticked **1000 times**
- On each tick:
  - `vApplicationTickHook` executed
  - Internal `TickCount` was incremented

**The Trigger**
- On the **1000th tick**:
  - Condition `if (TickCount >= 1000)` became true
  - ISR initiated the event signaling sequence

**The Handshake (ISR → Daemon Task)**
- `xEventGroupSetBitsFromISR` was called
- A message was placed into the **Timer Queue**
- `portYIELD_FROM_ISR` was executed
- As soon as the ISR completed:
  - **Timer Service Task (Daemon Task)** was scheduled to run

**The Handshake (Daemon Task → Waiting Task)**
- Timer Service Task processed the queued message
- `BIT_ISR` was set in the event group
- Kernel detected that `EventTask` was waiting for this bit
- `EventTask` was moved from **Blocked** to **Ready**

**The Execution**
- `EventTask` has **high priority (3)**
- Scheduler immediately preempted lower-priority tasks
- Execution jumped directly to `EventTask`
- `EventTask` hit the `nop` breakpoint

  **Kernel Configuration**
- `#define configUSE_TICK_HOOK             1`
- `#define configUSE_TIMERS                1`
- `#define INCLUDE_xTimerPendFunctionCall  1`

  **Timer Service Task Configuration**
- `#define configTIMER_TASK_PRIORITY    (configMAX_PRIORITIES - 1)`
- `#define configTIMER_TASK_STACK_DEPTH 128`
- `#define configTIMER_QUEUE_LENGTH     10`

**Conclusion**
- Event signaling from ISR is **deferred** via the Timer Service Task
- ISR never directly modifies the event group
- Task unblocking occurs in **task context**, not ISR context
- High-priority waiting tasks preempt immediately upon unblocking

