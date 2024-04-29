#ifndef UART_H
#define UART_H

#include "std_types.h"

#define TxEIE_mask              0X00000080
#define RxNEIE_mask             0X00000020
#define TxE                     TxEIE_mask
#define RxNE                    RxNEIE_mask
#define stop_bits_2_mask        0x00002000     //default is 1 stop bit
#define word_length_9_mask      0x00001000   //default is word length =8
#define oversampling_8_mask     0x00008000  //defualt is oversampling 16 
#define parity_enable_mask      0x00000400    //default: parity disabled
#define parity_odd_selection    0x00000200  //default: even parity is selected
#define parity_none             0x0
#define stop_bits_1_mask        0
#define word_length_8_mask      0
#define oversampling_16_mask    0  
#define parity_disable_mask     0    
#define parity_even_selection   0
#define mode_Tx_only            0x00000100
#define mode_Rx_only            0x00000101
#define mode_Tx_Rx              0x00000102
#define oversampling_16     16
#define oversampling_8      8
#define TC_mask                         0x00000040
#define UART_Transmission_Enable_mask   0x00000008
#define UART_Reciever_Enable_Mask       0x00000004

#define Enable 1
#define Disable 0

typedef struct {
    u8 stopBits;
    u8 wordLength;
    u8 parity_selection;
    f32 baudrate;
    u8 oversampling;

}uart_cfg_t;

typedef enum{
    UART_enum_Nok,
    UART_enum_Ok,
    UART_enum_invalidValue,
    UART_enum_Timeout,
    UART_enum_NullPointer
}UART_Error_t;


typedef struct{
    u32 SR;
    u32 DR;
    u32 BRR;
    u32 CR1;
    u32 CR2;
    u32 CR3;
    u32 GTPR;
}UART_reg_t;


UART_Error_t UART1_Init(uart_cfg_t * uart_cfg);
UART_Error_t UART_sendByte(u8 byte);
u8 UART_TxDone(void);
UART_Error_t UART_getRx(u8* byte);
u8 UART_IsRxDone(void);
void UART_enableInterrupt(u8 interrupt);
void UART_disableInterrupt(u8 interrupt);
void UART_setBaudrate(u32 baudrate);
//UART_Error_t UART_configFrame(frame_t* frame);
//UART_Error_t UART_control(u8 status,u16 mode);

#endif