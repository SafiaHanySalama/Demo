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
		.periodicity_ms = 100,
		.cb = Runnable_LED_StateMachine,
		.delayms = 0
		},
		[LED_Toggle] = {
				.name = "toggle led",
				.periodicity_ms = 1000,
				.cb = Runnable_LED_Toggle,
				.delayms = 100
		},
		[LED_SW] = {.name = "led on/off based on sw",
				.periodicity_ms = 1100,
				.cb = Runnable_LED_SW,
				.delayms = 50
		} */
		[LCD] = {
			.name = "LCD",
			.periodicity_ms = 2,
			.cb = LCD_Runnable,
			.delayms =0
		},
		[LCDTest] = {
			.name = "LCDTest",
			.periodicity_ms = 1000,
			.cb = LCD_Test,
			.delayms =20
		}
		
};
