/******************************************************************************
 *
 * Module: 
 *
 * File Name: led.h
 *
 * Description: 
 *
 * Author: Safia Hany
 * 
 * Date:  Feb 26, 2024
 ******************************************************************************/
#ifndef HAL_LED_LED_H_
#define HAL_LED_LED_H_

#include <Std_Types.h>

#include "led_cfg.h"

/*these values cannot be changed by the user*/
#define Led_conn_forward 0
#define Led_conn_rev  1
#define led_state_on 1
#define led_state_off 0

typedef struct {
	void * port;
	uint32 pin;
	uint8 connection;
	uint8 defaultstate;
}ledcfg_t;

void led_init(void);

void led_setState(uint32 led, uint8 status);

void led_toggle(uint32 lednum);

#endif /* HAL_LED_LED_H_ */
