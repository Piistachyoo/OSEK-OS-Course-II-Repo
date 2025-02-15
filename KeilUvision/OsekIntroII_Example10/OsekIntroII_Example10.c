/**
 * @file OsekIntro_Example2.c
 * @author Sarea Alhariri (Sarea.h95@outlook.com)
 * @brief  Alarm and events integration: Periodic events
 * @version 0.1
 * @date 2020-08-19
 *
 * @copyright Sarea Alhariri - All rights reserved
 *
 */

#include "os.h"


DeclareTask(AppTask_MultiEventTask);


void SystemInit(void) {}
int main(void) {
  StartOS();
  while (1)
    ; /* Should not be executed */
  return 0;
}

TASK(AppTask_MultiEventTask) {
   EventMaskType l_ev; 

   static uint8_t Event5TicksCounter = 0u; 
   static uint8_t Event10TicksCounter = 0u; 
   static uint8_t Event35TicksCounter = 0u; 

   while(true)
   {
      WaitEvent(Event5Ticks|Event10Ticks|Event35Ticks);
      GetEvent(AppTask_MultiEventTask, &l_ev);
      ClearEvent(l_ev); 

      if((l_ev & Event5Ticks) == Event5Ticks)
      {
         Event5TicksCounter ^= 1; ; 
      } 
      if((l_ev & Event10Ticks) == Event10Ticks)
      {
         Event10TicksCounter ^= 1; ; 
      } 
      if((l_ev & Event35Ticks) == Event35Ticks)
      {
         Event35TicksCounter ^= 1; ; 
      } 

   }
}

