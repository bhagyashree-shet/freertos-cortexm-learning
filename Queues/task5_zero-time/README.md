# FreeRTOS Debug Notes — Zero Timeout Receive and Sender Blocking

**Initial State**
- Receiver priority = **2**
- Sender priority = **1**
- Queue initially **empty**

**First Iteration**
- Receiver runs first
- Receiver executes:
  - `ret = xQueueReceive(..., 0);`
- Queue is empty
- **Zero timeout** → returns immediately
- Receiver then calls:
  - `vTaskDelay(...)`
- Receiver moves to **Delayed list**

**Sender First Execution**
- Sender runs for the first time
- Breakpoint hit at **Sender**
  - `int value = 42;`
- Sender executes:
  - `xQueueSend(xQueue, &value, portMAX_DELAY);`
- Queue is empty → send succeeds
- Queue now contains **1 item**

**Immediately After the Send**
- Queue length = `5` (or `1`, depending on test)
- Receiver is still **delayed (sleeping)**
- Sender loop has **no delay**
- Sender reaches:
  - `xQueueSend(xQueue, &value, portMAX_DELAY);`
  - again

**Sender Blocking (Important)**
- Receiver has not yet consumed the item
- Queue becomes **full** (or no receiver is READY)
- Sender attempts to send again
- `portMAX_DELAY` → Sender **blocks**

**Kernel Action**
- Sender removed from **READY list**
- Sender added to:
  - `xQueue->xTasksWaitingToSend`

**Result**
- Sender is now **BLOCKED**
- Sender breakpoint is **never hit again**
- This behavior is **expected**

**Why Receiver Keeps Hitting but Sender Does Not**

Receiver behavior:
- Receiver wakes periodically due to `vTaskDelay`
- Receiver runs
- Calls **zero-timeout receive**
- Consumes data
- Loops again
- Receiver breakpoint continues to hit

Sender behavior:
- Sender sends once
- Then blocks on **full queue**
- Sender will only wake when:
  - Receiver frees queue space
