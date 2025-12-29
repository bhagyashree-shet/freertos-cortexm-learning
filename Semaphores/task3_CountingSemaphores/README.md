# FreeRTOS Debug Notes — Counting Semaphore Given from Tick Hook

**Breakpoints**
- `break HandlerTask`
- `break vApplicationTickHook`

**Run**
- `continue`

**Initial Semaphore Inspection (Before Any Task Runs)**
- `p *xCountSem`
- Observed:
  - `uxLength = 10`
  - `uxMessagesWaiting = 0`

**Tick Hook Execution**
- `continue`
- `continue`
- `continue`
- Tick hook fires multiple times

**Semaphore Inspection After Tick Hook Runs**
- `p *xCountSem`
- Observed:
  - `uxMessagesWaiting = 3`

**Conclusion**
- Semaphore is being **given from `vApplicationTickHook`**
- No task has taken the semaphore yet
- Counting semaphore correctly accumulates tokens up to `uxLength`
