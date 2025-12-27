# FreeRTOS Debug Notes — Queue Receive with Timeout Unblock

**Debug Setup**
- `break ReceiverTask`

**Execution**
- `continue`

**Observation**
- Receiver wakes up **periodically**

**TCB Inspection**
- `p *pxCurrentTCB`
- Receiver task is **RUNNING** on wake-up

**Queue State**
- Queue is **still empty**

**Receive API Result**
- Return value of `xQueueReceive()` is **pdFALSE**

**Conclusion**
- Receiver task was **unblocked due to timeout**
- Confirms **timeout-based unblock** behavior for `xQueueReceive()`
