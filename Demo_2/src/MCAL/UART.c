#include "UART.h"
#include "stdint.h"
#include "math.h"

#define fclk                16000000L
#define mantissaDiv_mask    0xfff0
#define mantissa_leftshift_4  4
#define fractionDiv_mask    0xf

#define UART_Enable_Mask                0x2000
#define UART_Transmission_Enable_mask   0x8
#define UART_Reciever_Enable_Mask       0x4

#define stop_bit_mask                   0x3000

#define UART_PARITY_ON                     0x00000400
#define UART_PARITY_SELECT_MASK            0x00000200
#define UART_PARITY_CONTROL_MASK           0x00000400


volatile UART_reg_t* const UART1 = (UART_reg_t* const) 0x40011000; 



u8 UART_TxDone(void){
    return (u8)(UART1->SR & TxE);
}

u8 UART_IsRxDone(void){
    return (u8)(UART1->SR & RxNE);
}

UART_Error_t UART1_Init(uart_cfg_t * uart_cfg){
    UART_Error_t Ret_ErrorStatus = UART_enum_Nok;
    if(!uart_cfg){
        Ret_ErrorStatus = UART_enum_NullPointer;
    }else if((uart_cfg->oversampling != oversampling_16)&& \
      (uart_cfg->oversampling != oversampling_8)&& \
      (uart_cfg->parity_selection != parity_even_selection)&& \
      (uart_cfg->parity_selection != parity_odd_selection) && \
      (uart_cfg->parity_selection != parity_none)&& \
      (uart_cfg->stopBits != stop_bits_1_mask)&& \
      (uart_cfg->stopBits != stop_bits_2_mask) && \
      (uart_cfg->wordLength != word_length_8_mask )&& \
      (uart_cfg->wordLength != word_length_9_mask) ){
        Ret_ErrorStatus =UART_enum_invalidValue;
      }else{
        Ret_ErrorStatus = UART_enum_Ok;
        f32 OVER8= (uart_cfg->oversampling==oversampling_16)?0:1;
        u32 MaxBaudRate= fclk/(8*(2-OVER8));
        if(uart_cfg->baudrate>MaxBaudRate)
        {
            Ret_ErrorStatus=UART_enum_invalidValue; 
        }
        else
        {
            
            u32 Loc_Reg=UART1->CR1;
            Loc_Reg|=UART_Enable_Mask;
            
            Loc_Reg&=~(word_length_9_mask);
            Loc_Reg|=(uart_cfg->wordLength);
            UART1->CR1=Loc_Reg;

            Loc_Reg=UART1->CR2;
            Loc_Reg&=~stop_bit_mask;
            Loc_Reg|=(uart_cfg->stopBits);
            UART1->CR2=Loc_Reg;

            Loc_Reg=UART1->CR1;
            Loc_Reg&=~UART_PARITY_CONTROL_MASK;
            if(uart_cfg->parity_selection==parity_none)
            {
               Loc_Reg|=parity_none;
            }
            else
            {
                Loc_Reg|=UART_PARITY_ON;
                Loc_Reg&=~UART_PARITY_SELECT_MASK;
                Loc_Reg|=uart_cfg->parity_selection;
            }
            UART1->CR1=Loc_Reg;
            
            /*Select Baud Rate*/
            f32 USARTDIV=((f32)(fclk)/((uart_cfg->baudrate)*8*(2-OVER8)));
            f32 FracionBoundary=(uart_cfg->oversampling==oversampling_16)?16:8;
            u32 DIV_Fraction=(u32)(FracionBoundary*(f32)((f32)USARTDIV-(u32)USARTDIV))+1;
            u32 MAXVALUE=(uart_cfg->oversampling==oversampling_16)?15:7;
            u32 DIV_Mantissa=0;
            if(DIV_Fraction>MAXVALUE)
            {
                DIV_Fraction=0;
                DIV_Mantissa=(u32)USARTDIV+1;
            }
            else
            {
                DIV_Mantissa= (u32)USARTDIV;
            }

            Loc_Reg=UART1->BRR;
            Loc_Reg&=~mantissaDiv_mask;
            Loc_Reg|=DIV_Mantissa<<mantissa_leftshift_4;

            Loc_Reg&=~fractionDiv_mask;
            Loc_Reg|=DIV_Fraction;

            UART1->BRR=Loc_Reg;
            /*
            Loc_Reg=UART1->CR1;
            Loc_Reg|=UART_Transmission_Enable_mask;

            Loc_Reg|=UART_Reciever_Enable_Mask;
            UART1->CR1=Loc_Reg;
            */
           UART1->SR = 0;
        } 
      }
      return Ret_ErrorStatus;
}

UART_Error_t UART_getRx(u8* byte){
    UART_Error_t Ret_ErrorStatus = UART_enum_Nok;
    u16 timeout=3000;
    UART1->CR1 |= UART_Reciever_Enable_Mask;
    while(timeout--&&(!(UART1->SR&RxNE)));
    if(UART1->SR&RxNE)
    {
        *byte=(u8)UART1->DR;
        Ret_ErrorStatus=UART_enum_Ok;
    }
    else{
        Ret_ErrorStatus=UART_enum_Timeout;
    }
    UART1->CR1 &= ~UART_Reciever_Enable_Mask;
    return Ret_ErrorStatus;
}

UART_Error_t UART_sendByte(u8 byte){
    UART_Error_t Ret_ErrorStatus = UART_enum_Nok;
    u16 timeout = 3000;
    //UART1->SR &=~ TC_mask;
    
    UART1->CR1 |= UART_Transmission_Enable_mask;
    UART1->DR = byte;
    while (timeout-- && (!(UART1->SR & TxE)));
        
    if (timeout == 0 && (UART1->SR & TxE)==0) {
            Ret_ErrorStatus = UART_enum_Timeout;
    } else if (UART1->SR & TxE) {
            Ret_ErrorStatus = UART_enum_Ok;
            
    }
    
    return Ret_ErrorStatus;
}

void UART_enableInterrupt(u8 interrupt){
    UART1->CR1 |= interrupt;
}

void UART_disableInterrupt(u8 interrupt){
    UART1->CR1 &= ~interrupt;
}