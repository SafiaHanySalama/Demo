/*
#include "INIT_SYS.h"
#include "RCC.h"
#include "GPIO.h"
#include "UART_HAL.h"
#include "NVIC.h"
#include "string.h"
#include "sched.h"
*/


#include "app_sw_led.h"

int main(void){
    App_Init();
}

/*
int main (void)
{
    u8 x[]="shereen\n";
    u8 size=sizeof(x)/sizeof(u8);
	gpiomode_t mode={.mode=gpio_mode_AF,.type=gpio_type_pp};
    gpiopin_t GpioTX={.port=GPIOA,.pin=PIN9,.speed=gpio_speed_high,.mode_t=&mode}; 
	gpiopin_t GpioRX={.port=GPIOA,.pin=PIN10,.speed=gpio_speed_high,.mode_t=&mode}; 
    
    uart_cfg_t USART1_cfg={.oversampling=oversampling_16,.wordLength=word_length_8_mask,.parity_selection=parity_none,.stopBits=stop_bits_1_mask,.baudrate=115200};
    
    initSys();
    NVIC_enableIRQ(NVIC_USART1_INTERRUPT);

	gpio_setAF(GPIO_AF7_USART1, GpioTX.port,GpioTX.pin);
	gpio_setAF(GPIO_AF7_USART1, GpioRX.port,GpioRX.pin);
    
    gpio_initPin(&GpioTX);
    gpio_initPin(&GpioRX); 
	

    UART1_Init(&USART1_cfg);
    user_req_t req = {.buffer=x,.length=size,.callBack=NULL};
    //UART_TxBufferAsync(&req);
    UART_sendByte(x[0]);
    while(1){

    }
    
}
*/