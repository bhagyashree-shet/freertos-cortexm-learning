# FreeRTOS Debug Notes — Event Groups (with Timeout)

This debug session verifies **timeout behavior** when `xEventGroupWaitBits()` is used with **OR logic** and a finite wait time.

**Breakpoints**
- `break main.c:12`   (Task1 sets its bit at ~1000 ms)
- `break main.c:26`   (TaskWait starts waiting)
- `break main.c:33`   (TaskWait resumes: event or timeout)

---

**Inspection Commands**
When a breakpoint is hit, use the following to inspect RTOS state.

Check the event group internals:
- `p *((EventGroup_t *)xEventGroup)`

Expected observations:
- **uxEventBits**
  - `0` initially
  - `1` (BIT_TASK1) after ~1000 ms
- **xTasksWaitingForBits.uxNumberOfItems**
  - `1` while `TaskWait` is blocked

Check system time and running task:
- `p xTickCount`
- `p pxCurrentTCB->pcTaskName`

---

**Running the Debug Session**

- `continue`
  - Runs until `TaskWait` calls `xEventGroupWaitBits`
  - Verify:
    - `xTickCount` ≈ `0`
    - `xTasksWaitingForBits.uxNumberOfItems = 1`

- `continue`
  - Breakpoint hit at **Task1** (~1000 ms)
  - Verify:
    - `p *((EventGroup_t *)xEventGroup)`
    - **uxEventBits = 1**

- `continue`
  - Breakpoint hit at **TaskWait resume** (`main.c:33`)
  - Verify timeout behavior:
    - `p xTickCount` ≈ **1500**
    - **uxEventBits = 1**
    - TaskWait resumed due to **timeout**, not Task2

---

**Conclusion**
- `xEventGroupWaitBits()` returned due to **timeout**
- OR condition was partially satisfied (`BIT_TASK1` only)
- Task2 did not run before timeout (2000 ms)
- Event bits remain set because the unblock was **timeout-based**
- This confirms correct **finite wait + OR-mode** behavior in FreeRTOS Event Groups
