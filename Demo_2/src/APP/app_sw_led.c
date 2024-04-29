#include "app_sw_led.h"
#include "SCHED.h"
#include "LED.h"
#include "SWITCH.h"
#include "NVIC.h"
#include "GPIO.h"
#include "UART_HAL.h"

void USART1_IRQHandler(void) {
    if (UART_IsRxDone()) {
        u8 data;
        // = UART1_ReadData();
        UART_getRx(&data);
        /******For debugging*******/
        UART_sendByte(data);
        /**************************/
        if (data == '1') {
            led_setStatus(led_red, led_state_on);
        } else if (data == '0') {
            led_setStatus(led_red, led_state_off);
        }
    }
    UART_enableInterrupt(UART_Reciever_Enable_Mask);
}


void App(){
    u8 state ;
    SWITCH_getStatus(switch_1,&state);
    if(state == state_PRESSED){
        UART_sendByte('1');
        //led_setStatus(led_red,led_state_on);
    }else{
        UART_sendByte('0');
        //led_setStatus(led_red,led_state_off);
    }
}

void App_Init(void){
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
    //user_req_t req = {.buffer=x,.length=size,.callBack=NULL};
    //UART_TxBufferAsync(&req);
    UART_enableInterrupt(UART_Reciever_Enable_Mask);
    UART_enableInterrupt(RxNEIE_mask);
    
    SWITCH_Init();
    led_init();
    SCHED_init();
    SCHED_start();
}

