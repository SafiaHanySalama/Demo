/******************************************************************************
 *
 * Module: 
 *
 * File Name: switch_cfg.c
 *
 * Description: 
 *
 * Author: Safia Hany
 * 
 * Date:  Feb 26, 2024
 ******************************************************************************/


#include "mcal/gpio.h"
#include "hal/switch.h"

const SWITCH_Config_t switches[_sw_num]={
		[Up_Start]={
			.port = GPIO_PORTA,
			.pin= PIN0,
			.connection= SWITCH_PULLUP,
		},
		[Down_End]={
			.port = GPIO_PORTA,
			.pin= PIN1,
			.connection= SWITCH_PULLDOWN,
		},
		[Right_Pause]={
			.port = GPIO_PORTA,
			.pin= PIN2,
			.connection= SWITCH_PULLUP,
		},
		[Left_Reset]={

			.port = GPIO_PORTA,
			.pin= PIN3,
			.connection= SWITCH_PULLDOWN,
		},
		[Edit]={
			.port = GPIO_PORTA,
			.pin= PIN4,
			.connection= SWITCH_PULLUP,
		},
		[Mode]={
			.port = GPIO_PORTA,
			.pin= PIN5,
			.connection= SWITCH_PULLDOWN,
		},
		[Okay]={
			.port = GPIO_PORTA,
			.pin= PIN6,
			.connection= SWITCH_PULLUP,
		}
};
