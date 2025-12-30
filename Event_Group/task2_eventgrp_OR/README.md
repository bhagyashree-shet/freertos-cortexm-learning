# FreeRTOS Debug Notes — Event Groups (Logical OR Synchronization)

**Task Setup**
- **Task1 (Priority 1)**: Sets `BIT_1` at `1000 ms`
- **Task2 (Priority 1)**: Sets `BIT_2` at `2000 ms`
- **TaskWait (Priority 2)**: Calls `xEventGroupWaitBits()` with `xWaitForAllBits = pdFALSE`

This configuration tests **OR-mode synchronization**, where *any one bit* is sufficient to unblock the waiting task.

---

**GDB Debug Commands**
- `break main.c:12`   (Task1 — SetBits)
- `break main.c:32`   (TaskWait — NOP / Goal)
- `continue`

---

**Execution Observation**
- Execution stops at **Task1 (Line 12)**
- Step forward:
  - `next`
- GDB immediately jumps to **Breakpoint at TaskWait (NOP)**

This jump happens **before Task2 ever runs**.

---

**Result (Proof via Inspection)**

- `p xTickCount`
  - Value ≈ **1000**
  - Confirms TaskWait unblocked as soon as Task1 set its bit
  - TaskWait did **not** wait for Task2 (2000 ms)

- `p uxEventBits`
  - Value = **0**
  - Confirms **auto-clear** behavior after unblock

- `p uxNumberOfItems`
  - Value = **0**
  - Confirms TaskWait has left the event waiting list and is now running

---

**Conclusion**
- `xWaitForAllBits = pdFALSE` enables **OR-mode**
- TaskWait unblocks when **any one bit** is set
- Event bits are cleared automatically on exit
- Higher-priority TaskWait preempts immediately upon unblocking

This trace conclusively proves **OR-based event synchronization**, **priority preemption**, and **atomic clearing** behavior in FreeRTOS Event Groups.
