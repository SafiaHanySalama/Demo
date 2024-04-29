#ifndef  __LED_H_
#define  __LED_H_

#include "std_types.h"

#include "LED_CFG.h"


#define led_conn_forward 0
#define led_conn_reversed 1
#define led_state_on 1
#define led_state_off 0

typedef struct{
	void *port;
	u32 pin;
	u8 connection;
	u8 defaultState;
}ledcfg_t;



void led_setStatus(u32 led,u8 status);
void led_init(void);

#endif