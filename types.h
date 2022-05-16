#ifndef TYPES_H
#define	TYPES_H

#include "user_conf.h"

#define TASK                          void
#define GLOBAL_INTERRUPTS_DISABLE()   INTCONbits.GIE = 0
#define GLOBAL_INTERRUPTS_ENABLE()    INTCONbits.GIE = 1


typedef unsigned char byte;
typedef unsigned int u_int;
typedef void(*f_task)(void);
typedef enum {READY = 0, RUNNING, WAITING, TERMINATED} state_t;

typedef struct TCB {
    u_int task_ID;
    u_int task_PRIOR;
    f_task task_PTR;
    __uint24 task_CONTEXT[STACK_SIZE];
    __uint24 task_BSR_reg;
    __uint24 task_WORK_reg;
    __uint24 task_STATUS_reg;
    u_int task_stack_real_size;
    state_t task_STATE;
} TCB_t;

typedef struct READY_queue {
    TCB_t tasks_list[MAX_TASKS_SCHEDULER];
    u_int tasks_installed;
    u_int task_running;    
} READY_queue_t;



#endif	/* TYPES_H */
