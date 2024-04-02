/******************************************************************************
 *
 * Module: 
 *
 * File Name: led.c
 *
 * Description: 
 *
 * Author: Safia Hany
 * 
 * Date:  Feb 26, 2024
 ******************************************************************************/


#include "hal/led.h"

#include <mcal/gpio.h>/*must be in this order otherwise the user will have to include this way too*/

extern const ledcfg_t leds[_led_num];
void led_init(void){
	GPIO_ConfigPin_t led;
	led.Mode= GPIO_MODE_OUT_PP;
	led.Speed=GPIO_HIGH_SPEED;
	for(uint32 idx=0; idx<_led_num; idx++){
		led.Port=leds[idx].port;
		led.Pin =leds[idx].pin;
		GPIO_init(&led);
		
		GPIO_setPinValue(leds[idx].port,leds[idx].pin,(leds[idx].connection)^(leds[idx].defaultstate));
	}
}
void led_setState (uint32 lednum,uint8 state){
	GPIO_setPinValue(leds[lednum].port,leds[lednum].pin,(leds[lednum].connection)^state);
}
void led_toggle(uint32 lednum)
{
	uint8 led_state = GPIO_getPinValue(leds[lednum].port,leds[lednum].pin);
	GPIO_setPinValue(leds[lednum].port,leds[lednum].pin,(!led_state));
}
