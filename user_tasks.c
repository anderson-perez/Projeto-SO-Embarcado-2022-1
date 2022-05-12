#include "user_tasks.h"

void config_tasks()
{
   TRISDbits.RD0  = 0;
   TRISDbits.RD1  = 0;
   TRISDbits.RD2  = 0;
   
   // Declara as tarefas como funções globais
   asm("GLOBAL _task_1, _task_2, _task_3");
}

TASK task_1()
{
   while (1) {
      LATDbits.LATD0 = ~PORTDbits.RD0;
   }
}

TASK task_2()
{
   while (1) {
      LATDbits.LATD1 = ~PORTDbits.RD1;      
   }
}

TASK task_3()
{
   while (1) {
      LATDbits.LATD2 = ~PORTDbits.RD2;      
   }
}

