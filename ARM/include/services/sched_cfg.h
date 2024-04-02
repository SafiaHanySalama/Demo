/******************************************************************************
 *
 * Module: 
 *
 * File Name: runnable.h
 *
 * Description: 
 *
 * Author: Safia Hany
 * 
 * Date:  Mar 24, 2024
 ******************************************************************************/
#ifndef INCLUDE_SERVICES_RUNNABLE_H_
#define INCLUDE_SERVICES_RUNNABLE_H_


typedef enum
{
  LED_StateMachine,
  LED_Toggle,
  LED_SW,
  _num_runnable
}Run_t;

extern void Runnable_LED_Toggle(void);
extern void Runnable_LED_SW(void);
extern void Runnable_LED_StateMachine(void);


#endif /* INCLUDE_SERVICES_RUNNABLE_H_ */
