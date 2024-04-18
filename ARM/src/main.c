/*
#include "app/app.h"
int main()
{
  //app1();
  //app2();
  //app3();
  //app4();
  uart_test();
  return 0;
}
*/

#include "app/demo.h"
#include "mcal/rcc.h"
#include "mcal/gpio.h"
#include "mcal/nvic.h"

extern uint8 Switch_State[_sw_num];

int main(void){
  /*****testing*****/
  //Switch_State[Up_Start] = REALESED;
  /****************/
  RCC_enablePeri(RCC_APB2,USART1);
  RCC_enablePeri(RCC_AHB1,GPIOA);
  //set_preipheral_clk(GPIOA);
  NVIC_EnableIRQ(USART1_IRQn);

  GPIO_ConfigPin_t uart_pins_config[2] = {
        {
            .Mode = GPIO_MODE_AF_PP,
            .Pin = PIN9,
            .Port = GPIO_PORTA,
            .Speed = GPIO_HIGH_SPEED
        },
        {
            .Mode = GPIO_MODE_AF_PP,
            .Pin = PIN10,
            .Port = GPIO_PORTA,
            .Speed = GPIO_HIGH_SPEED
        }
  };

  GPIO_CFG_AlternativeFunction(uart_pins_config[0].Port,uart_pins_config[0].Pin,GPIO_AF_7);
  GPIO_CFG_AlternativeFunction(uart_pins_config[1].Port,uart_pins_config[1].Pin,GPIO_AF_7);
  GPIO_init(&uart_pins_config[0]);
  GPIO_init(&uart_pins_config[1]);
  SWITCH_init();
  UART_init();
  /********************
  //const SWITCH_Config_t switches[_sw_num];
  //uint8 sw_state_ [0]= {SWITCH_Getstatus(0)};
  
  uint8 x[] = {5};
  UART_UserReq_t uart_req = {
	.usartID = USART1_IDX,
	.ptr_buffer = &x,//sw_state_, //Only for Initialization
	.size = 1,
	.cbf =NULL_PTR//RecieverCallBack
  };
  //USART_RxBufferAsyncZeroCopy(&uart_req);
  //UART_sendByte(&uart_req);
  //UART_receiveByte(&uart_req);
  extern uint8 RecieverHasByte;
  //if(RecieverHasByte){
      //UART_sendByte(&uart_req);
   //}
  
  /************************
  while(1){
    UART_receiveByte(&uart_req);
    UART_sendByte(&uart_req);
  }
  */
  sched_init();
  sched_start();
  
}
