/******************************************************************************
*
* Module: 
*
* File Name: filename
*

* Description: 
*
* Author: Safia Hany
* 
* Date:  time
******************************************************************************/
#ifndef UART_H
#define UART_H



/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "Std_Types.h"
#include "mcal/uart_cfg.h"
/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

/**
 * @brief UART NUMBERS
*/


#define USART1_IDX 0
#define USART2_IDX 1
#define USART6_IDX 2
#define UART5_IDX 3



#define UART_NUM_IN_TARGET 4


#define USART_BAUDRATE 9600

#define FCPU 16000000UL
/**
 * @brief UART FLAGS
 * @note: TX_ENABLE and RX_ENABLE are used to enable the TX and RX
*/
#define UART_TX_ENABLE 0x00000008
#define UART_RX_ENABLE 0x00000004

#define UART_WORD_LENGTH_8 0x00000000
#define UART_WORD_LENGTH_9 0x00001000

#define UART_STOP_BITS_1 0x00000000
#define UART_STOP_BITS_0_5 0x00002000
#define UART_STOP_BITS_2 0x00003000
#define UART_STOP_BITS_1_5 0x00003000

#define UART_PARITY_ENABLE 0x00000100
#define UART_PARITY_NONE 0x00000000
#define UART_PARITY_EVEN 0x00000400
#define UART_PARITY_ODD 0x00000600

/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

typedef void (*uart_req_callback)(void);
/**
 * @brief Typedef for the UART configuration structure.
 *
 * This typedef defines the UART configuration structure.
 * The UART configuration structure contains the following members:
 * - baudrate: The baud rate of the UART.
 * - data_size: The data size of the UART.
 * - stop_bits: The stop bits of the UART.
 * - parity: The parity of the UART.
 * - mode: The mode of the UART.
 * - flow_control: The flow control of the UART.
 */

typedef struct uart_config_t
{
    uint32 uartid;
    uint32 baudrate;
    uint32 data_size;
    uint32 stop_bits;
    uint32 parity;
    uint32 mode;
    uint32 flow_control;
    uint32 over_sampling;
} uart_config_t;

typedef struct 
{
    uint8 usartID;
    uint8 *ptr_buffer;
    uint32 size;
    uart_req_callback cbf;
}UART_UserReq_t;


/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/

void UART_init(void);
void USART_TxBufferAsyncZeroCopy(UART_UserReq_t *Ptr_UserReq);
void USART_RxBufferAsyncZeroCopy(UART_UserReq_t *Ptr_UserReq);
void UART_sendByte(UART_UserReq_t *Ptr_UserReq);
void UART_receiveByte(UART_UserReq_t *Ptr_UserReq);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART6_IRQHandler(void);

#endif // UART_H
