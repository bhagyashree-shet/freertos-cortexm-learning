# FreeRTOS Debug Notes — Task Notifications (ulTaskNotifyTake / xTaskNotifyGive)

**Initial State**
- **ReceiverTask** priority = 2  
- **SenderTask** priority = 1  
- Receiver notification value = 0

---

**Receiver Starts and Blocks**
- `break ReceiverTask`
- `continue`
- Inspect current task:
  - `print *pxCurrentTCB`

Observed:
- **pcTaskName = "ReceiverTask"**
- **ulNotifiedValue = 0**
- **ucNotifyState = ""** (not yet marked waiting)

Result:
- Receiver enters `ulTaskNotifyTake`
- Receiver moves to the **Suspended List**
- Receiver is now blocked, waiting for a notification

---

**Sender Runs While Receiver Is Blocked**
- SenderTask executes (lower priority but only READY task)
- Inspect Receiver from Sender context:
  - `print *((TCB_t *)xReceiverTaskHandle)`

Observed:
- **pvContainer = <xSuspendedTaskList>**
- **ucNotifyState = taskWAITING_NOTIFICATION**

Result:
- Confirms Receiver is officially waiting and inactive

---

**Sender Sends Notification**
- Sender calls `xTaskNotifyGive()`
- Step into kernel:
  - `step`
  - `next` (until notification increment)

Inspect Receiver TCB again:
- `print *((TCB_t *)xReceiverTaskHandle)`

Observed:
- **ulNotifiedValue = 1**
- **ucNotifyState = taskNOTIFICATION_RECEIVED**

Result:
- Notification signal delivered
- Kernel marks event as pending for Receiver

---

**Unblock and Preemption**
- Kernel moves Receiver from **Suspended List** to **Ready List**
- Receiver priority (2) > Sender priority (1)
- Immediate **context switch** occurs

- `continue`
- Execution hits `nop` in **ReceiverTask**

Inspect running task:
- `print *pxCurrentTCB`

Observed:
- **ulNotifiedValue = 0**
- **ucNotifyState = ""**

Result:
- Notification was **consumed**
- Because `pdTRUE` was used, the value reset immediately on wake

---

**Conclusion**
- Task notifications block the task using the **Suspended List**
- `xTaskNotifyGive()` delivers a lightweight signal (no queue)
- Higher-priority waiting tasks preempt immediately
- Notification value is cleared automatically when `pdTRUE` is used
