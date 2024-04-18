/******************************************************************************
 *
 * Module: 
 *
 * File Name: switch.c
 *
 * Description: 
 *
 * Author: Safia Hany
 * 
 * Date:  Feb 26, 2024
 ******************************************************************************/
#include "hal/switch.h"
#include "mcal/gpio.h"


extern const SWITCH_Config_t switches[_sw_num];
static uint8 state[_sw_num];

void SWITCH_init(void){
	GPIO_ConfigPin_t button;
	button.Speed=GPIO_HIGH_SPEED;
	for (uint32 idx=0; idx < _sw_num ; idx++)
	{
		button.Port = switches[idx].port;

		button.Pin = switches[idx].pin;
		if (switches[idx].connection == SWITCH_PULLUP){
			button.Mode = GPIO_MODE_IN_PU;
		}

		else{
			button.Mode = GPIO_MODE_IN_PD;
		}
		GPIO_init(&button);
	}
}
SWITCH_State_t SWITCH_Getstatus(uint32 switch_num){
//#ifndef RUNNABLE_USED
	uint8 state_local;
	state_local = GPIO_getPinValue(switches[switch_num].port,switches[switch_num].pin);
	//if state_local = HIGH and switch pull up i want to return RELEASED
	return (state_local^switches[switch_num].connection) ;

/*
#else
	return (state[switch_num] ^switches[switch_num].connection) ;
#endif
*/
}
#ifdef RUNNABLE_USED
void SWITCH_Runnable(void)
{
	//Function to update state
	uint8 current_state[_sw_num];
	static uint8 previous_state[_sw_num];
	static uint32 count[_sw_num] = {0};
	for (uint32 idx=0; idx < _sw_num ; idx++)
	{
		current_state[idx] = GPIO_getPinValue(switches[idx].port,switches[idx].pin);;
		if (previous_state[idx] == current_state[idx])	(count[idx])++;
		else (count[idx]) = 0;
		if ((count[idx])==5) {
			state[idx]= current_state[idx];
			(count[idx]) = 0;
		}
		previous_state[idx] = current_state[idx];
	}
}
#endif
