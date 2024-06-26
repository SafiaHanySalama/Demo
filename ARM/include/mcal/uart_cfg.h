/******************************************************************************
*
* Module: 
*
* File Name: uart_cfg.h
*

* Description: 
*
* Author: Safia Hany
* 
* Date:  13/4/2024
******************************************************************************/
#ifndef UART_CFG_H
#define UART_CFG_H



/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "mcal/uart.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

#define UART_MODE_RX                        ((uint32)UART_RX_ENABLE)
#define UART_MODE_TX                        ((uint32)UART_TX_ENABLE)
#define UART_MODE_TX_RX                     ((uint32)(UART_TX_ENABLE |UART_RX_ENABLE))

#define UART_OVERSAMPLING_16                ((uint32)0x00000000)
#define UART_OVERSAMPLING_8                 ((uint32)0X00008000)

#define USART2 1
#define USART6 2


/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

typedef enum
{
    USART1_enum,
    _UART_USED_NUM
} uart_used;
#endif // UART_CFG_H
