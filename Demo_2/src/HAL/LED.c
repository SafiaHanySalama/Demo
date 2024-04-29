#include "LED.h"
#include "GPIO.h"

extern const ledcfg_t leds[_led_num];

void led_init(void){
	gpiopin_t led;
	gpiomode_t  led_mode ={ gpio_mode_out,\
		gpio_type_pp};
		
	// cppcheck-suppress uninitvar
	//led.mode_t->mode = gpio_mode_out;
	//led.mode_t->type =gpio_type_pp;
	led.mode_t = &led_mode;
	led.speed= gpio_speed_high;
	for(u32 idx=0;idx<_led_num ;idx++){
		led.pin =leds[idx].pin;
		led.port=leds[idx].port;
		gpio_initPin(&led);
	}

}

void led_setStatus(u32 led,u8 state){
	gpio_setPinValue(leds[led].port,leds[led].pin,leds[led].connection^state);
}
