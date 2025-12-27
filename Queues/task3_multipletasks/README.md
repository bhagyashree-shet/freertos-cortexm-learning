# FreeRTOS Debug Notes — Multiple Senders, Single Receiver (Queue + Priority)

**Debug Setup**
- `break ReceiveQueue`
- `break Send1Queue`
- `break Send2Queue`

**Execution**
- `continue`

**Initial Scheduling**
- **Receiver runs first**
- Receiver immediately blocks on:
  - `xQueueReceive()`
- Receiver appears in:
  - `xQueue->xTasksWaitingToReceive`

**Sender Execution Order**
- **Sender2 runs before Sender1**
- Reason:
  - **Higher priority**

**Observed**
- Breakpoint hit at **Sender2**

**Queue Send and Unblock**
- When **Sender2 executes**:
  - Receiver is **unblocked**
  - Receiver has **higher priority**
  - **Immediate context switch** occurs

**Context Switch Result**
- Breakpoint hit at **Receiver**
- **Sender2 does not continue yet**

**Data Ordering Observed**
- Values received:
  - **200-series first**
  - **100-series next**
