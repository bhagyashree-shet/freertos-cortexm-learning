# FreeRTOS Queue Debug Notes — Single Sender & Receiver

**Scenario**
- Queue with single sender and single receiver  
- Sender periodically sends an integer  
- Receiver blocks on the queue  

**Debug Setup**
- `break SenderTask`  
- `break ReceiverTask`  

**Execution Flow**
- `continue ->`  

**Receive API Breakpoint Hit**
- `xQueueReceive(xQueue, &received, portMAX_DELAY);`  

**TCB Inspection (Before Blocking)**
- `p *pxCurrentTCB`  
- **pcTaskName** = `"Receiver"`  
- **xStateListItem.pvContainer** → Ready list  
- Receiver task is **running and ready** before blocking  

**Continue Execution**
- `continue ->`  

**Receiver Blocking Observed**
- Receiver blocks on empty queue  

**Task Count Inspection**
- `p uxCurrentNumberOfTasks`  
- **Number of tasks** = `3`  
  - Sender  
  - Receiver  
  - Idle  

**Queue Inspection**
- `p *xQueue`  
- **xTasksWaitingToReceive** → Receiver  
- Receiver is:
  -  Not on Delay list  
  -  Not on Ready list  
  -  Blocked on Queue receive waiting list  
 

### Queue Blocking and Wake-Up
- Receiver blocks on empty queue
- Task moves to queue receive waiting list
- Sender sends data → kernel wakes receiver
- With timeout, receiver may wake due to tick expiry
- Queue-based blocking is event-driven and deterministic

