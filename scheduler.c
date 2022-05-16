#include "scheduler.h"

// Acesso a fila de aptos
extern READY_queue_t ready_queue;


u_int RR_scheduler()
{
   u_int task_to_run;
   
   return task_to_run;
}

u_int PRIOR_scheduler()
{
   u_int task_to_run;
   
   return task_to_run;
}

u_int FIFO_scheduler()
{
   u_int task_to_run;
   
   // Escolha da tarefa que será executada (ordem de chegada)
   task_to_run = (ready_queue.task_running + 1) % ready_queue.tasks_installed;
   
   return task_to_run;
}

u_int scheduler()
{
   u_int task_to_run;
   
#if DEFAULT_SCHEDULER == RR_SCHEDULER
   task_to_run = RR_scheduler();
#elif DEFAULT_SCHEDULER == PRIOR_SCHEDULER
   task_to_run = RR_scheduler();
#else
   task_to_run = FIFO_scheduler();
#endif
   
   
   return task_to_run;
}