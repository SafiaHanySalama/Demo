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
		[SWITCH1]={
				.port = GPIO_PORTB,
				.pin= PIN2,
				.connection= SWITCH_PULLUP,
		},
		[SWITCH2]={
				.port = GPIO_PORTB,
				.pin= PIN3,
				.connection= SWITCH_PULLDOWN,
		}
};
