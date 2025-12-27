# Queue with Single Sender and Receiver

Sender periodically sends an integer.  
Receiver blocks on the queue.

---

## Debug Flow

### Break SenderTask  
### Break ReceiverTask  

continue ->
Hit Receive breakpoint:
xQueueReceive(xQueue, &received, portMAX_DELAY);
Inspect:
p *pxCurrentTCB
Observed:
pcTaskName = "Receiver"
xStateListItem.pvContainer -> Ready list
This is the Receiver task before blocking.

continue ->
Receiver blocks.
Inspect number of tasks:
p uxCurrentNumberOfTasks
number of tasks = 3
(Sender, Receiver, Idle)

Inspect queue:
p *xQueue
Observed:
xTasksWaitingToReceive -> Receiver
Receiver is:
Not on Delay list
Not on Ready list
Blocked on Queue Receive waiting list

### Queue Blocking and Wake-Up
- Receiver blocks on empty queue
- Task moves to queue receive waiting list
- Sender sends data → kernel wakes receiver
- With timeout, receiver may wake due to tick expiry
- Queue-based blocking is event-driven and deterministic

