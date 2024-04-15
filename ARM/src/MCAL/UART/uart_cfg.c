/******************************************************************************
*
* Module: 
*
* File Name: uart_cfg.c
*

* Description: 
*
* Author: Safia Hany
* 
* Date:  13/4/2024
******************************************************************************/


/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/

#include "mcal/uart_cfg.h"


/********************************************************************************************************/
/*********************************************Implementation****************************************/
/********************************************************************************************************/

const uart_config_t usart_config[_UART_USED_NUM] = {
   [USART1] ={
        .uartid = USART1_IDX,
        .baudrate = USART_BAUDRATE,
        .data_size = UART_WORD_LENGTH_8,
        .stop_bits = UART_STOP_BITS_1,
        .parity = UART_PARITY_NONE,
        .mode = UART_MODE_TX_RX,
        .over_sampling = UART_OVERSAMPLING_16
    }
};