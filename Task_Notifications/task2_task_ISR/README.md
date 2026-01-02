# FreeRTOS Debug Notes — Task Notification from ISR (Short)

**Receiver Blocks**
- `break ReceiverTask`
- `continue`
- `p *pxCurrentTCB`

Observed:
- **pcTaskName = "ReceiverTask"**
- **ulNotifiedValue = 0**
- **ucNotifyState = ""**

Result:
- Receiver enters `ulTaskNotifyTake()` and blocks
- Task state → **WAITING_NOTIFICATION**

---

**ISR Sends Notification**
- `break vApplicationTickHook`
- `continue`
- `step` (into `vTaskNotifyGiveFromISR`)
- `p *pxHigherPriorityTaskWoken`

Observed:
- **xHigherPriorityTaskWoken = 0**
- Notification delivered before scheduler switch

---

**Notification Update**
- `step`
- `p *pxCurrentTCB`

Observed:
- **ulNotifiedValue = 1**
- **ucNotifyState = taskNOTIFICATION_RECEIVED**

Result:
- Notification delivered
- Binary-semaphore behavior confirmed

---

**Task Unblocks and Runs**
- `continue`
- Breakpoint hits **ReceiverTask**
- `p *pxCurrentTCB`

Observed:
- **ulNotifiedValue = 0**
- **ucNotifyState = ""**

Result:
- Notification consumed (`pdTRUE`)
- Receiver preempted and resumed immediately
