/******************************************************************************
 *
 * Module: 
 *
 * File Name: runnable.c
 *
 * Description: 
 *
 * Author: Safia Hany
 * 
 * Date:  Mar 24, 2024
 ******************************************************************************/
#include "services/sched.h"
#include "services/sched_cfg.h"


const runnable_t runnable_list[_num_runnable]=
{
/* 		[LED_StateMachine] = {.name = "traffic light state machine",
		.periodicity_ms_ms = 100,
		.cb = Runnable_LED_StateMachine,
		.delayms = 0
		},
		[LED_Toggle] = {
				.name = "toggle led",
				.periodicity_ms_ms = 1000,
				.cb = Runnable_LED_Toggle,
				.delayms = 100
		},
		[LED_SW] = {.name = "led on/off based on sw",
				.periodicity_ms_ms = 1100,
				.cb = Runnable_LED_SW,
				.delayms = 50
		} */
		[LCDRunnable] = {
			.name = "LCD",
			.periodicity_ms = 2,
			.cb =NULL_PTR,//LCD_Runnable,
			.delayms =0
		},
		[LCDTest] = {
			.name = "LCDTest",
			.periodicity_ms = 1000,
			.cb = NULL_PTR,//LCD_Test,
			.delayms =20
		},
		[Runnable_SwitchesTx]={.name="Runnable_Switches",
			.periodicity_ms=500,
			.cb=MCU1_SwitchesTx,
			.delayms =0
		},
		[Runnable_UARTSignalRx]={.name="Runnable_UARTSignal",
			.periodicity_ms=500,
			.cb=MCU1_UARTSignalRx,
			.delayms =0
		},
		[Runnable_Clock]={.name="Runnable_Clock",
			.periodicity_ms=1000,
			.cb=NULL_PTR,//MCU1_Clock,
			.delayms =0
		},
		[Runnable_StopWatch]={.name="Runnable_StopWatch",
			.periodicity_ms=500,
			.cb=NULL_PTR,//MCU1_StopWatch,
			.delayms =0
		}	
};
