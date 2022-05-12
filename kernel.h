#ifndef KERNEL_H
#define	KERNEL_H

#include "types.h"

// Chamadas de sistema
void create_task(u_int id, u_int prior, f_task task);
void isr_TIMER0();
void change_task_state(state_t new_state);
void start_os();

#define GLOBAL_INTERRUPTS_DISABLE()   INTCONbits.GIE = 0
#define GLOBAL_INTERRUPTS_ENABLE()    INTCONbits.GIE = 1

#endif