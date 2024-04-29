#ifndef UART_HAL_H
#define UART_HAL_H

#include "std_types.h"
#include "UART.h"


typedef void(*Cb )(void);
typedef struct{
    u8* buffer;
    u16 length;
    Cb callBack;
}user_req_t;
//void UART1_Init(void);
UART_Error_t UART_TxBufferAsync(/*u8* buffer, u16 length,Cb cb*/ user_req_t* user_req );
UART_Error_t UART_RxBufferAsync(/*u8* buffer, u16 length,Cb cb*/ user_req_t* user_req );


#endif