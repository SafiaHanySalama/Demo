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
  //LED_StateMachine,
  //LED_Toggle,
  //LED_SW,
  LCDRunnable, //LCD Init
  //LCDTest, // LCD Display
  Runnable_SwitchesTx,
	Runnable_UARTSignalRx,
  SwitchRunnable,
	Runnable_Clock,
	Runnable_StopWatch,
  _num_runnable
}Run_t;

extern void Runnable_LED_Toggle(void);
extern void Runnable_LED_SW(void);
extern void Runnable_LED_StateMachine(void);
extern void LCD_Runnable(void);
extern void LCD_Test(void);
extern void MCU1_SwitchesTx(void);
extern void MCU1_UARTSignalRx(void);
extern void MCU1_Clock(void);
extern void MCU1_Day(void);
extern void MCU1_StopWatch(void);
extern void SWITCH_Runnable(void);

#endif /* INCLUDE_SERVICES_RUNNABLE_H_ */
