#include "scheduler.h"

// Acesso a fila de aptos
extern READY_queue_t ready_queue;


u_int RR_scheduler()
{
   u_int task_to_run;
   
   do {
      // Escolha da tarefa que será executada (ordem de chegada)
      task_to_run = (ready_queue.task_running + 1) % ready_queue.tasks_installed;
   } while (ready_queue.tasks_list[task_to_run].task_STATE != READY);
   
   return task_to_run;
}

u_int PRIOR_scheduler()
{
   u_int task_to_run, menor_prioridade;
   
   // A escolha pela tarefa de maior prioridade se dará de maneira
   // inversamente proporcional ao número atribuído a prioridade.
   u_int x, y;
   task_to_run      = 0;
   menor_prioridade = ready_queue.tasks_list[task_to_run].task_PRIOR;
   for (y = 1; y < ready_queue.tasks_installed; y++) {
       if ((ready_queue.tasks_list[y].task_PRIOR < menor_prioridade) &&
          (ready_queue.tasks_list[y].task_STATE == READY)) {
            menor_prioridade = ready_queue.tasks_list[y].task_PRIOR;
            task_to_run      = y;
         }
   }
   
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
   task_to_run = PRIOR_scheduler();
   #else
   task_to_run = FIFO_scheduler();
   #endif   
   
   return task_to_run;
}
