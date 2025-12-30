# FreeRTOS Debug Notes — Event Groups (Logical AND Synchronization)

**Synchronization Point 1**
- **Action**: `Task1` sets `BIT_TASK1`
- **Result**:
  - `uxEventBits = 1`
  - `uxNumberOfItems = 1`

**Observation**
- `TaskWait` (Priority 2) did **not** wake up
- It remains **parked in the event list**
- Reason:
  - Logical AND condition (**BIT_TASK1 AND BIT_TASK2**) is **not satisfied**

This confirms that partial events do not unblock the waiting task.

---

**Synchronization Point 2**
- **Action**: `Task2` sets `BIT_TASK2`

**Debugger Behavior**
- After stepping (`next`) at line 18, GDB immediately jumps to **Breakpoint 3 (TaskWait)**

**Why This Happened**
- `BIT_TASK2` was set
- Event bits became:
  - `0x01 | 0x02 = 0x03`
- Logical AND condition is now satisfied
- Kernel unblocks **TaskWait**
- Since `TaskWait` (Priority 2) > `Task2` (Priority 1):
  - Immediate **context switch** occurs

---

**Post-Unblock State**
- **Result**:
  - `uxEventBits = 0`

**Meaning**
- `pdTRUE` (**ClearOnExit**) worked correctly
- Event bits were cleared **atomically** when `TaskWait` unblocked

**Verification**
- `uxNumberOfItems = 0`
- `TaskWait` has left the event wait list
- `TaskWait` is now the **running task**

---

## Key Takeaways (Verified in GDB)

| Concept | Evidence |
|------|--------|
| **Barrier Synchronization** | `TaskWait` stayed blocked (`uxNumberOfItems = 1`) after only the first bit was set |
| **Priority Preemption** | GDB jumped directly from `Task2` to `TaskWait` when the second bit was set |
| **Atomic Clearing** | `uxEventBits` returned to `0` automatically due to `pdTRUE (ClearOnExit)` |

This trace proves correct **event group AND-mode synchronization**, **priority-based preemption**, and **atomic event clearing** in FreeRTOS.
