- Queue with single sender and receiver  
- Sender periodically sends an integer  
- Receiver blocks on the queue  

- break SenderTask  
- break ReceiverTask  

- continue ->  

- Hit Receive breakpoint  
  - xQueueReceive(xQueue, &received, portMAX_DELAY);

- Inspect  
  - p *pxCurrentTCB  
  - pcTaskName = "Receiver"
  - xStateListItem.pvContainer -> Ready list  
  - This is Receiver before blocking  

- continue ->  

- Receiver blocks  

- Inspect task count  
  - p uxCurrentNumberOfTasks 
  - number of tasks = 3  
  - Sender, Receiver, Idle  

- Inspect queue  
  - p *xQueue
  - xTasksWaitingToReceive -> Receiver
  - Receiver is blocked on the queue  
  - Not on delay list  
  - Not on Ready list  

### Queue Blocking and Wake-Up
- Receiver blocks on empty queue
- Task moves to queue receive waiting list
- Sender sends data → kernel wakes receiver
- With timeout, receiver may wake due to tick expiry
- Queue-based blocking is event-driven and deterministic

