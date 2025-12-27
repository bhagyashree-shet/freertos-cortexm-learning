# FreeRTOS Debug Notes — Simple Task (No Delay)

**Debug Start**
- `break main`
- `continue` → Stop execution at `main`
- Run until `main`

**Scheduler Entry**
- `break vTaskStartScheduler`
- `continue` → Run until `vTaskStartScheduler`

**Task Entry**
- `break Simple_Task`
- Stop execution at `Simple_Task`

**CPU Register Inspection**
- `info registers`
- Inspect CPU execution state
- **SP (Stack Pointer)** = **PSP (Process Stack Pointer)**
  - CPU is running the task using **PSP**
  - Task is still running in **privileged mode**
- **xPSR = 0x01000000**
  - Indicates **Thumb state**

**TCB Inspection**
- `p *pxCurrentTCB`
- Shows the **currently running task**
- Displays **task stack range** (stack grows downward)
- Shows **task priority**
- **xStateListItem** → Ready list
- **xEventListItem** → Empty (task not blocked)

**Key Observations**
- `main()` is **not a task**
  - It only creates tasks and starts the scheduler
- Scheduler control begins at `vTaskStartScheduler()`
- Tasks execute using **PSP**, not **MSP**
- Tasks run in **privileged mode by default** in FreeRTOS
- A task is represented by:
  - **TCB + Stack**
  - Not just a function



