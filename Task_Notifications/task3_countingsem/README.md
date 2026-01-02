# FreeRTOS Debug Notes — Counting Task Notifications from ISR

**Breakpoints**
- `break ReceiverTask`        (task blocks on notification)
- `break vApplicationTickHook` (ISR / SysTick context)

**Start**
- `continue`

---

**Receiver Blocks on Notification**
- Breakpoint hit at `ReceiverTask` (line 36)
- `ulTaskNotifyTake(pdTRUE, portMAX_DELAY);`

Inspect TCB:
- `p *pxCurrentTCB`

Observed:
- **pcTaskName = "ReceiverTask"**
- **ulNotifiedValue = 0**
- **ucNotifyState = ""**

Meaning:
- No pending notifications
- Task is about to block

---

**ISR Fires (SysTick)**
- Breakpoint hit at `vApplicationTickHook`
- ISR context confirmed

Step into notify:
- `step`
- `vTaskNotifyGiveFromISR(...)`

---

**Notification Delivered**
- `p *pxCurrentTCB`

Observed:
- **ulNotifiedValue = 1**
- **ucNotifyState = taskNOTIFICATION_RECEIVED**

Meaning:
- Notification count incremented
- Task marked as notified

---

**Multiple ISR Hits**
- After several ticks:
  - `p *pxCurrentTCB`

Observed:
- **ulNotifiedValue = 3**

Meaning:
- Notifications accumulated
- Counting semaphore behavior

---

**Task Wakes and Consumes All**
- Breakpoint hit again at `ReceiverTask`
- `p count`

Observed:
- **count = 3**

Meaning:
- `ulTaskNotifyTake()` returned total count
- All notifications consumed at once
- Value cleared due to `pdTRUE`

---

**Verify Reset**
- `p *pxCurrentTCB`

Observed:
- **ulNotifiedValue = 0**

Meaning:
- Notification value reset
- Ready for next cycle

---

**Idle Task Runs**
- `Ctrl+C`
- Execution in `prvIdleTask`

Meaning:
- ReceiverTask is blocked
- No READY tasks
- Idle task running (expected)
