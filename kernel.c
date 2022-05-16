#include "kernel.h"
#include "user_tasks.h"
#include "scheduler.h"

// Declara��o da fila de aptos
READY_queue_t ready_queue;


// Rotinas de configura��o
void __interrupt() isr_INTERRUPTS()
{
   // Verifica��o da flag de interrup��o
   if (INTCONbits.INT0IF) {      
      INTCONbits.INT0IF = 0;
      
      // Salva contexto da tarefa que est� em execu��o
      SAVE_CONTEXT(READY);
      // Chama o escalonador para selecionar outra tarefa para executar
      ready_queue.task_running = scheduler();
      // Restaura o contexto da tarefa que ir� executar
      RESTORE_CONTEXT();
   }     
}

void config_os()
{
   // Ajusta estrutura de dados do kernel
   ready_queue.task_running      = 0;
   ready_queue.tasks_installed   = 0;  
   
   // Configura��o das interrup��es
   TRISBbits.RB0                 = 1;
   INTCONbits.INT0IE             = 1;
   INTCONbits.INT0IF             = 0;
   
   // Configura��o das tarefas de usu�rio
   config_tasks();
}


// Chamadas de sistema
void create_task(u_int id, u_int prior, f_task task)
{
   TCB_t new_task;
   
   // Cria uma nova tarefa
   new_task.task_ID                 = id;
   new_task.task_PRIOR              = prior;
   new_task.task_PTR                = task;
   new_task.task_STATE              = READY;
   new_task.task_stack_real_size    = 0;
   
   ready_queue.tasks_list[ready_queue.tasks_installed] = new_task;
   ready_queue.tasks_installed                        += 1;
}

void change_task_state(state_t new_state)
{
   
}

void start_os()
{
   // Habilita as interrup��es
   GLOBAL_INTERRUPTS_ENABLE();
}
