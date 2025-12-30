# FreeRTOS Debug Notes — Watching Priority Inheritance 

**Watch the Inheritance Trigger**
- `break xTaskPriorityInherit`
- `continue`

This breakpoint confirms when the kernel detects priority inversion and applies inheritance.

**Inspect the Task Control Block (TCB)**
- Inspect the TCB address obtained from `pxCurrentTCB`:
  - `p *((TCB_t *)0x210008b8)`

---

**Initial State (Normal)**
- TaskLow holds the mutex
- No higher-priority task is waiting

Observed:
- **uxPriority = 1**
- **uxBasePriority = 1**
- **uxMutexesHeld = 1**
- **pvContainer = pxReadyTasksLists[1]**

Meaning:
- TaskLow is running at its base priority
- No priority inheritance has occurred yet

---

**Inheritance Triggered (The Boost)**
- TaskHigh attempts to take the mutex and blocks
- Kernel executes **xTaskPriorityInherit**

Observed:
- **uxPriority = 3** (inherited from TaskHigh)
- **uxBasePriority = 1** (original priority preserved)
- **pvContainer = pxReadyTasksLists[3]**

Meaning:
- Priority inversion detected
- TaskLow is temporarily boosted
- TaskLow is moved to the high-priority Ready list

---

**Observe the Boosted Priority**
- `finish`
- `p ((TCB_t *)0x210008b8)->uxPriority`

Confirms:
- **TaskLow is executing at priority 3**

---

**Restoration (The Release)**
- TaskLow calls `xSemaphoreGive()`

Observed:
- **uxPriority = 1**
- **uxBasePriority = 1**
- **uxMutexesHeld = 0**

Meaning:
- Mutex released
- Priority inheritance removed
- TaskLow restored to its original priority

---

**Key Fact**
- Priority inheritance is applied **only while the mutex is held**
- The kernel restores priority immediately after mutex release

