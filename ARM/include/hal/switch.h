/******************************************************************************
 *
 * Module: 
 *
 * File Name: switch.h
 *
 * Description: 
 *
 * Author: Safia Hany
 * 
 * Date:  Feb 26, 2024
 ******************************************************************************/
#ifndef HAL_SWITCH_SWITCH_H_
#define HAL_SWITCH_SWITCH_H_


#include <Std_Types.h>

#include "switch_cfg.h"


#define SWITCH_PULLUP		1
#define SWITCH_PULLDOWN		0

#define RUNNABLE_USED

typedef struct {
	void * port;
	uint32 pin;
	//Pressed Low or Pressed High
	uint8 connection;
}SWITCH_Config_t;

typedef enum {
	REALESED,
	BRESSED
}SWITCH_State_t;

void SWITCH_init(void);

SWITCH_State_t SWITCH_Getstatus(uint32 switch_num);

#endif /* HAL_SWITCH_SWITCH_H_ */
