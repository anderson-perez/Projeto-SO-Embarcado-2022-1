#ifndef KERNEL_H
#define	KERNEL_H

#include "types.h"

#pragma config PBADEN = OFF

#define SAVE_CONTEXT(STATE);
#define RESTORE_CONTEXT();


// Rotinas de configuração
void __interrupt() isr_INTERRUPTS();
void config_os();


// Chamadas de sistema
void create_task(u_int id, u_int prior, f_task task);
void change_task_state(state_t new_state);
void start_os();

#endif