# FreeRTOS Debug Notes — Cooperative Switching with taskYIELD()

**FreeRTOSConfig.h**
- `#define configUSE_TIME_SLICING     0`

**Debug Setup**
- `break TaskA`
- `break TaskB`

**Execution**
- `continue`

**Breakpoint Sequence Observed**
- Breakpoint hit at **TaskA**
- Breakpoint hit at **TaskB**
- Breakpoint hit at **TaskA**
- Breakpoint hit at **TaskB**

**Observation**
- Both tasks are running even though **time slicing is disabled**
- Tasks cooperate explicitly
- Scheduler rotates the **Ready list** on yield

**Behavior When `taskYIELD()` Is Called**
- Task remains in **READY** state
- Task is moved to the **end of the Ready list** at its priority
- Scheduler selects the **next READY task**
- **PendSV** performs the context switch


