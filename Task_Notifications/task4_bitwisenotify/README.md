# FreeRTOS Debug Notes — Accumulated Task Notifications (eSetBits)

**Observation**
- `(gdb) p events`
- Result: **7**

This confirms correct notification accumulation.

---

**Task Blocks**
- `ReceiverTask` enters `ulTaskNotifyTake()`
- Inspect TCB:
  - **ulNotifiedValue = 0**
  - **ucNotifyState = ""**
- No notifications pending → task **blocks**

---

**ISRs Send Notifications**
- While task is blocked, `vApplicationTickHook()` runs
- ISR calls:
  - `xTaskNotifyFromISR(..., eSetBits, ...)`
- Notifications are **OR-ed**, not overwritten

Observed internally:
- **ulNotifiedValue = 5** → `0b101`
- Means:
  - `EVT_UART_RX`
  - `EVT_ERROR`

---

**Task Wakes and Consumes**
Inside `ulTaskGenericNotifyTake()`:
- Kernel copies notification value
- Clears `ulNotifiedValue`
- Resets notify state

---

**Why `events = 7`**
- Another notification arrived before task ran:
  - `EVT_TIMER = 0b010`
- Final value:
  - `0b101 | 0b010 = 0b111`

So:
- **events = 7**
- Represents:
  - `EVT_UART_RX | EVT_TIMER | EVT_ERROR`

---

**Key Takeaway**
- Task notifications **accumulate while blocked**
- `ulTaskNotifyTake()` returns the **combined value once**
- Value is cleared immediately after return
