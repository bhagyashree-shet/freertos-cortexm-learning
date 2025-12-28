# FreeRTOS Debug Notes — Queue Full, Sender Blocking, and Back-Pressure

**Debug Setup**
- `break FastSender`
- `break SlowReceiver`

**Run**
- `continue`

**Sender Blocking Observation**
- After the first send, **FastSender** attempts to send again
- Queue becomes full

**Queue Inspection**
- `p *xQueue`
- Observed:
  - **uxMessagesWaiting = 1**
  - Queue is **full**

**Sender Blocking**
- Sender blocks due to full queue
- Execution no longer hits **FastSender**

**Inspect Queue Send Wait List**
- `p xQueue->xTasksWaitingToSend`
- Observed:
  - **uxNumberOfItems = 1**

**Proof**
- Sender is **blocked**
- Sender is waiting for **queue space**
- Queue enforces **back-pressure**

**Receiver Frees Space**
- When **SlowReceiver** executes:
  - `xQueueReceive(...)`
- Kernel actions:
  - Removes item from queue
  - Frees queue space
  - Wakes blocked sender
  - Sender becomes **READY**
  - Scheduler evaluates priorities

**Preemption**
- Sender priority **greater than** receiver priority
- Sender **immediately preempts** receiver
