#include "so.h"

int main()
{
   start_os();
   
   create_task(1, 1, task_1);
   create_task(2, 1, task_2);
   create_task(3, 1, task_3);
   
   while (1) {
      
   }
   
   return 0;
}
