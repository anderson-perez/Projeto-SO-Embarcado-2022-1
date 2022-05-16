#include "kernel.h"
#include "user_tasks.h"
#include "scheduler.h"

// Declaração da fila de aptos
READY_queue_t ready_queue;


// Rotinas de configuração
void __interrupt() isr_INTERRUPTS()
{
   // Verificação da flag de interrupção
   if (INTCONbits.INT0IF) {      
      INTCONbits.INT0IF = 0;      
      // Salva contexto da tarefa que está em execução
      SAVE_CONTEXT(READY);
      // Chama o escalonador para selecionar outra tarefa para executar
      ready_queue.task_running = FIFO_scheduler();
      // Restaura o contexto da tarefa que irá executar
      RESTORE_CONTEXT();
   }     
}

void config_os()
{
   // Ajusta estrutura de dados do kernel
   ready_queue.task_running      = 0;
   ready_queue.tasks_installed   = 0;  
   
   // Configuração das interrupções
   TRISBbits.RB0                 = 1;
   INTCONbits.INT0IE             = 1;
   INTCONbits.INT0IF             = 0;
   
   // Configuração das tarefas de usuário
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
   // Habilita as interrupções
   GLOBAL_INTERRUPTS_ENABLE();
}

// Rotinas para salvar e restaurar o contexto de uma tarefa
#define SAVE_CONTEXT(STATE) { \
u_int p_context = 0, task_pos = ready_queue.task_running;\
do { \
    GLOBAL_INTERRUPTS_DISABLE(); \
    \
    if (ready_queue.tasks_list[task_pos].task_STATE == RUNNING) { \
      ready_queue.tasks_list[task_pos].task_BSR_reg      = BSR; \
      ready_queue.tasks_list[task_pos].task_WORK_reg     = WREG; \
      ready_queue.tasks_list[task_pos].task_STATUS_reg   = STATUS; \
      do { \
        ready_queue.tasks_list[task_pos].task_CONTEXT[p_context] = TOS; \
        asm("POP");\
        p_context += 1;\
      } while (STKPTR);\
      ready_queue.tasks_list[task_pos].task_stack_real_size = p_context; \
      ready_queue.tasks_list[task_pos].task_STATE           = STATE;\
    } \
    GLOBAL_INTERRUPTS_ENABLE(); \
while(0); \
} \

#define RESTORE_CONTEXT() { \
u_in* task_pos    = ready_queue.task_running;\
u_int p_context   = ready_queue.tasks_list[task_pos].task_stack_real_size;\
do { \
    GLOBAL_INTERRUPTS_DISABLE(); \
    STKPTR = 0;\
    if (ready_queue.tasks_list[task_pos].task_stack_real_size > 0) { \
      BSR      = ready_queue.tasks_list[task_pos].task_BSR_reg; \
      WREG     = ready_queue.tasks_list[task_pos].task_WORK_reg; \
      STATUS   = ready_queue.tasks_list[task_pos].task_STATUS_reg; \
      while (p_context) { \
        p_context -= 1;\
        asm("PUSH");\
        TOS = ready_queue.tasks_list[task_pos].task_CONTEXT[p_context];\
      }\
    } \
    else { \
      asm("PUSH");\
      TOS = ready_queue.tasks_list[task_pos].task_PTR;\
    } \
    ready_queue.tasks_list[task_pos].task_STATE = RUNNING;\
    GLOBAL_INTERRUPTS_ENABLE(); \
while(0); \
} \/