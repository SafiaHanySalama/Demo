#include "app/app.h"
void App_Init ()
{
  // Initialize the GPIO
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
  set_preipheral_clk(USART1);
  set_preipheral_clk(GPIOA);
  set_preipheral_clk(GPIOB);
  NVIC_EnableIRQ(USART1_IRQn);

  GPIO_CFG_AlternativeFunction(uart_pins_config[0].Port,uart_pins_config[0].Pin,GPIO_AF_7);
  GPIO_CFG_AlternativeFunction(uart_pins_config[1].Port,uart_pins_config[1].Pin,GPIO_AF_7);
  GPIO_init(&uart_pins_config[0]);
  GPIO_init(&uart_pins_config[1]);
  UART_init();
  SWITCH_init();
  LCD_initAsync();
}
int main()
{
  App_Init();
  LCD_clearScreenAsynch();
  sched_init();
  sched_start();
  return 0;
}