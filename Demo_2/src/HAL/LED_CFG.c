#include "GPIO.h"
#include "LED.h"

const ledcfg_t leds[_led_num]={
		[led_red]={.port=GPIOA,
				.pin=PIN0,
				.connection=led_conn_forward,
				.defaultState=led_state_off},
		[led_green]={.port=GPIOA,
				.pin=PIN1,
				.connection=led_conn_forward,
				.defaultState=led_state_off}
};
