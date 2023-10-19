/**
 * @file AlarmManagementCodingExerciseStarter.c
 * @author Sarea Alhariri (Sarea.h95@outlook.com)
 * @brief  Event control coding exercise starter file
 * @version 0.1
 * @date 2020-10-23
 *
 * @copyright Sarea Alhariri - All rights reserved
 *
 */

#include "os.h"
#include "switch.h"

/*******************************************************************************
 * TODO: 
 * Add your needed shared variables 
 ******************************************************************************/
volatile bool g_PwmSignal = 0;
volatile uint8_t g_PwmWidth = 1;

/*******************************************************************************
 * TODO: 
 * Add the tasks prototypes (DeclareTask(XX))
 ******************************************************************************/
DeclareTask(AppTask_PwmHandler);
DeclareTask(AppTask_PulseWidthUpdate);

void SystemInit(void) {}
int main(void) {
  StartOS();
  while (1)
    ; /* Should not be executed */
  return 0;
}

/*******************************************************************************
 * TODO: 
 * Add your implementation for AppTask_PulseWidthUpdate task 
 ******************************************************************************/
TASK(AppTask_PwmHandler){
	EventMaskType event_return;
	
	while(1){
		WaitEvent(EventPwmOn | EventPwmOff);
		GetEvent(AppTask_PwmHandler, &event_return);
		ClearEvent(event_return);
		
		GetResource(PWM_WIDTH);
		
		if( (event_return & EventPwmOn) == EventPwmOn ){
			g_PwmSignal = 1;
			SetRelAlarm(Alrm_PwmOff, g_PwmWidth, 0);
		}
		if( (event_return & EventPwmOff) == EventPwmOff ){
			g_PwmSignal = 0;
		}
			
		ReleaseResource(PWM_WIDTH);
	}
}

/*******************************************************************************
 * TODO: 
 * Add your implementation for AppTask_PWMHandler task 
 ******************************************************************************/
TASK(AppTask_PulseWidthUpdate){
	uint8_t increment_flag = 0;
	while(1){
		WaitEvent(EventPwmUpdate);
		ClearEvent(EventPwmUpdate);
		
		GetResource(PWM_WIDTH);
		
		if(g_PwmWidth == 1)
			increment_flag = 1;
		else if(g_PwmWidth == 9)
			increment_flag = 0;
		
		if(increment_flag)
			g_PwmWidth++;
		else
			g_PwmWidth--;
		
		ReleaseResource(PWM_WIDTH);
	}
}
