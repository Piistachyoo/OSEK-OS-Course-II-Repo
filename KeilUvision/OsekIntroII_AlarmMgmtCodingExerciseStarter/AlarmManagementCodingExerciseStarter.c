/**
 * @file AlarmManagementCodingExerciseStarter.c
 * @author Sarea Alhariri (Sarea.h95@outlook.com)
 * @brief  Alarm Managment coding exercise starter file
 * @version 0.1
 * @date 2020-10-23
 *
 * @copyright Sarea Alhariri - All rights reserved
 *
 */

#include "os.h"
#include "switch.h"


volatile static bool g_PwmSignal = 0u; 


/*******************************************************************************
 * TODO: 
 * Add your needed shared variables 
 ******************************************************************************/
volatile uint8_t g_PwmValue = 1u;

/*******************************************************************************
 * TODO: 
 * Add the tasks & callback prototypes (DeclareTask(XX))
 ******************************************************************************/
DeclareTask(AppTask_PulseWidthUpdate);
DeclareTask(AppTask_PwmOn);
ALARMCALLBACK(PwmOFF_CB);

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
TASK(AppTask_PulseWidthUpdate){
	static bool increment_flag = 1;
	GetResource(pwm_width);
	if(g_PwmValue == 1)
		increment_flag = 1;
	else if(g_PwmValue == 9)
		increment_flag = 0;
	if(increment_flag)
		g_PwmValue++;
	else
		g_PwmValue--;
	ReleaseResource(pwm_width);
	TerminateTask();
}

/*******************************************************************************
 * TODO: 
 * Add your implementation for AppTask_PwmOn task 
 ******************************************************************************/
TASK(AppTask_PwmOn){
  GetResource(pwm_width);
	g_PwmSignal = 1;
	SetRelAlarm(Alrm_PwmOff, g_PwmValue, 0);
  ReleaseResource(pwm_width);
	TerminateTask();
}

/*******************************************************************************
 * TODO: 
 * Add your implementation for PwmOff callback 
 ******************************************************************************/
ALARMCALLBACK(PwmOFF_CB){
	g_PwmSignal = 0;
}
