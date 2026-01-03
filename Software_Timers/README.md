# FreeRTOS Debug Notes — Software Timer Driving Task Notification

**WorkerTask Blocks**
- `break WorkerTask`
- Breakpoint hit at:
  - `ulTaskNotifyTake(pdTRUE, portMAX_DELAY);`

Meaning:
- **WorkerTask is blocked**
- Waiting for a **task notification**
- Expected behavior before timer expiry

---

**Inspect PeriodicTimerHandle (Initial)**
- `p *PeriodicTimerHandle`

Observed:
- **xTimerListItem.xItemValue = 1000**
- **xTimerPeriodInTicks = 1000**
- **ucStatus = 5**

Meaning:
- Timer is active
- First expiry scheduled at **tick 1000**
- Periodic timer configuration confirmed

---

**Inspect PeriodicTimerHandle (Later)**
- `p *PeriodicTimerHandle`

Observed:
- **xTimerListItem.xItemValue = 2000**
- **xTimerPeriodInTicks = 1000**

Meaning:
- Timer expired once at **1000**
- Automatically reloaded
- Next expiry scheduled at **2000**

---

**Conclusion**
- Software timer is firing **periodically**
- Each expiry can notify **WorkerTask**
- WorkerTask remains blocked until notification arrives
