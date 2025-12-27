# FreeRTOS Debug Notes — Two Tasks, Different Priorities

**Debug Setup**
- `break Task1`
- `break Task2`

**Execution**
- `continue ->`

**Breakpoint Hit**
- Breakpoint hits **Task1**
- `p *pxCurrentTCB`
  - **pcTaskName = "Task1"**
  - **uxPriority = 2**

**Observation**
- Breakpoint **never hits Task2**

**Conclusion**
- Task1 has higher priority than Task2
- Scheduler always selects the **highest-priority READY task**
- As long as Task1 does not block or yield, **Task2 never gets CPU time**
- `pxCurrentTCB` correctly reflects the currently running task (Task1)
