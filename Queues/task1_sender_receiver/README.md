/*
Sender periodically sends an integer
Receiver blocks on the queue

break SenderTask
break ReceiverTask
continue ->         
Hit Receive breakpoint - xQueueReceive(xQueue, &received, portMAX_DELAY);
Inspect - p *pxCurrentTCB -> pcTaskName = "Receiver" , xStateListItem.pvContainer pointing to a Ready list -> This is Receiver before blocking.

continue -> Receiver blocks.
p uxCurrentNumberOfTasks -> number of tasks = 3 ( in our case:Sender , Receiver , Idle)
p *xQueue ->  xTasksWaitingToReceive -> Receiver is blocked on the queue.Not on a delay list.Not on Ready list.

*/
