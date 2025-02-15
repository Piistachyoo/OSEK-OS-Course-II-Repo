/**
 * @file hook.c
 * @author Sarea Alhariri (sarea.h95@outlook.com)
 * @brief Hook routine stubs
 * @version 0.1
 * @date 2020-05-03
 *
 * @copyright ALL RIGHT RESERVED - Sarea Alhariri
 *
 */
#include "OsTypes.h"
#include "gpio.h"
#include "sysctl.h"
#include "hw_memmap.h"
#include "tm4c123gh6pm.h"

/**
 * @brief Error hook that will be triggered in any error is detected
 *          upon system service call
 * @remark The hook implementation is user defined
 *
 * @param status
 */
void ErrorHook(StatusType status){}

/**
 * @brief This hook routine is called by the operating system at the end of
 * the operating system initialisation and before the scheduler is running.
 * The user may use it for App related Init/device driver init..etc.
 */
void StartupHook(void){
   
    /* IO port initialization */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF) ;
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3) ;
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0) ;
    GPIO_PORTF_LOCK_R = 0x4c4f434b ;
    GPIO_PORTF_CR_R = 0x01f ;
	GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU) ;
    
}

/**
 * @brief This hook routine is called by the operating system before
 * executing a new task, but after the transition of the task to the
 * running state
 *
 */
void PreTaskHook(void){
	
}

/**
 * @brief This hook routine is called by the operating system after
 * executing a new task, but before the transition of the task out of the
 * running state
 *
 */
void PostTaskHook(void){}

/**
 * @brief if configured, this hook will be triggerd if the OS detected
 * an stack overflow for any application thread
 *
 */
void StackOverFlowHook(void){}


	