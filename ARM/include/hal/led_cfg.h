/******************************************************************************
 *
 * Module: 
 *
 * File Name: led_cfg.h
 *
 * Description: 
 *
 * Author: Safia Hany
 * 
 * Date:  Feb 26, 2024
 ******************************************************************************/
#ifndef HAL_LED_LED_CFG_H_
#define HAL_LED_LED_CFG_H_

typedef enum{
led_red,
led_green,
led_yellow,
_led_num // user will not use it ,this indicates the num of leds stated by user
}leds_t;

#endif /* HAL_LED_LED_CFG_H_ */
