#include "UART_HAL.h"
#include "UART.h"
#include "GPIO.h"
#include "NVIC.h"

#define ready 0
#define busy 1

typedef struct{
    u8* data;
    u32 pos;
    u32 size;
}buffer_t;

typedef struct{
    buffer_t buffer;
    u8 state;
    Cb cbf;
}TxReq_t;

typedef struct{
    buffer_t buffer;
    u8 state;
    Cb cbf;
}RxReq_t;

TxReq_t TxReq;
RxReq_t RxReq;

extern volatile UART_reg_t* const UART1 ; 


UART_Error_t UART_TxBufferAsync(/*u8* buffer, u16 length,Cb cb*/ user_req_t* user_req ){
    UART_Error_t Ret_ErrorStatus =UART_enum_Nok;
    if(!user_req->buffer){
        Ret_ErrorStatus = UART_enum_NullPointer;
    }else{
        Ret_ErrorStatus =UART_enum_Ok;
        if(TxReq.state == ready){
            TxReq.buffer.data=user_req->buffer;
            TxReq.buffer.size=user_req->length;
            TxReq.buffer.pos=0;
            TxReq.state=busy;
            TxReq.cbf=user_req->callBack;
            
            
        }
        //UART1->SR &= ~TC_mask; //clear TC
            UART1->CR1 |= UART_Transmission_Enable_mask;
            UART1->DR=TxReq.buffer.data[TxReq.buffer.pos];
            //UART1->DR=*TxReq.buffer.data;

            TxReq.buffer.pos++;
            //UART_enableInterrupt(TC_mask);
            //UART1->CR1 |= UART_Transmission_Enable_mask;
            UART1->CR1 |= TxEIE_mask;
    }
    return Ret_ErrorStatus;
    
}

UART_Error_t UART_RxBufferAsync(/*u8* buffer, u16 length,Cb cb*/ user_req_t* user_req ){
    UART_Error_t Ret_ErrorStatus =UART_enum_Nok;
    if(!user_req->buffer){
        Ret_ErrorStatus = UART_enum_NullPointer;
    }else{
        Ret_ErrorStatus =UART_enum_Ok;
        if(RxReq.state == ready){
        //UART_disableInterrupt(RxNEIE_mask);
        UART1->CR1 &=~ UART_Reciever_Enable_Mask;
        RxReq.buffer.data=user_req->buffer;
        RxReq.buffer.size=user_req->length;
        RxReq.buffer.pos=0;
        RxReq.state=busy;
        RxReq.cbf=user_req->callBack;
        
        //UART_enableInterrupt(RxNEIE_mask);
        }
        UART1->CR1 |= UART_Reciever_Enable_Mask;
        UART1->CR1 |= RxNEIE_mask;
    }
    return Ret_ErrorStatus;
}

/*
void  USART1_IRQHandler(void){
    u32 loc_cr1 = UART1->CR1;
    if(UART_TxDone()){//check TxE flag
        //UART_disableInterrupt(TC_mask);
        
        if(TxReq.buffer.pos < TxReq.buffer.size){
            //UART1->SR &= ~TC_mask; //clear TC
            UART1->DR=TxReq.buffer.data[TxReq.buffer.pos];
            TxReq.buffer.pos++;
            
        }else{
            //UART_disableInterrupt(TC_mask);
            loc_cr1 &=~TxEIE_mask;
            UART1-> CR1 =loc_cr1;
            TxReq.buffer.pos=0;
            TxReq.state = ready;
            if(TxReq.cbf){
                TxReq.cbf();
            }
        }
        
          
    }
    if(UART_IsRxDone()){
        if(RxReq.buffer.pos < RxReq.buffer.size){
            RxReq.buffer.data[RxReq.buffer.pos]=UART1->DR;
            RxReq.buffer.pos++;
        }else if(RxReq.buffer.pos == RxReq.buffer.size){
            RxReq.state = ready;
            //UART_disableInterrupt(RxNEIE_mask);
           
            UART1->CR1 &= ~RxNEIE_mask;
            RxReq.buffer.pos=0;
            if(RxReq.cbf){
                RxReq.cbf();
            }
        }
    }
}
*/