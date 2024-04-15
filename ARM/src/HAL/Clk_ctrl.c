/******************************************************************************
 *
 * Module: 
 *
 * File Name: Clk_ctrl.c
 *
 * Description: 
 *
 * Author: Safia Hany
 * 
 * Date:  Mar 26, 2024
 ******************************************************************************/
#include "hal/Clk_ctrl.h"

void set_preipheral_clk(uint32 prei)
{
  if (prei == GPIOA || prei == GPIOB)
  {  
    RCC_enablePeri(RCC_AHB1, prei);
  }
  else if (prei == USART1)
  {
     RCC_enablePeri(RCC_APB2, prei);

  }
}