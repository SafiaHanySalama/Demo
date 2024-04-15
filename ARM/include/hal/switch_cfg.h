/******************************************************************************
 *
 * Module: 
 *
 * File Name: switch_cfg.h
 *
 * Description: 
 *
 * Author: Safia Hany
 * 
 * Date:  Feb 26, 2024
 ******************************************************************************/
#ifndef HAL_SWITCH_SWITCH_CFG_H_
#define HAL_SWITCH_SWITCH_CFG_H_


typedef enum{
	Up_Start,
	Down_End,
	Right_Pause,
	Left_Reset,
	Edit,
	Mode,
	Okay,
    _sw_num // user will not use it ,this indicates the num of leds stated by user
}SWITCHES_t;

#endif /* HAL_SWITCH_SWITCH_CFG_H_ */
