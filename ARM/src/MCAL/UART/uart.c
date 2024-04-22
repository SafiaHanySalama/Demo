/******************************************************************************

* Module: 

* File Name: uart.c

* Description: 

* Author: Safia Hany

* Date:  13/4/2024

******************************************************************************/


/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/

#include "mcal/uart.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/
/**
 * @brief USART Registers
*/
#define USART1_BASE_ADDRESS 0x40011000
#define USART2_BASE_ADDRESS 0x40004400
#define USART3_BASE_ADDRESS 0x40004800
#define UART4_BASE_ADDRESS 0x40004C00
#define UART5_BASE_ADDRESS 0x40005000
#define USART6_BASE_ADDRESS 0x40011400

/**
 * @brief UART Enable flag
 * @note: UART_ENABLE is used to enable the UART
*/
#define UART_ENABLE 0x00002000
/**
 * @brief UART TX empty flag and RX not empty flag
 * @note: TXE flag is set when the buffer is empty and ready to accept new data
 * @note: RXNE flag is set when the buffer is not empty and ready to be read
*/
#define UART_TXE_FLAG 0x00000080
#define UART_RXNE_FLAG 0x00000020
/**
 * @brief UART TX Done flag
*/
#define UART_TC_FLAG 0x00000040
/**
 * @brief UART TX Clear mask
*/
#define UART_RX_CLEAR_MASK 0xFFFFFFFB



/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

/**
 * @brief Typedef for the transmit complete callback function.
 *
 * This typedef defines the function pointer type for the transmit complete callback function.
 */
typedef void (*TX_CBF_t)(void);

typedef void (*RX_CBF_t)(void);


typedef struct uart_t
{
    uint32 USART_SR;   /*!< Status register */
    uint32 USART_DR;   /*!< Data register */
    uint32 USART_BRR;  /*!< Baud rate register */
    uint32 USART_CR1;  /*!< Control register 1 */
    uint32 USART_CR2;  /*!< Control register 2 */
    uint32 USART_CR3;  /*!< Control register 3 */
    uint32 USART_GTPR; /*!< Guard time and prescaler register */
} uart_t;

typedef struct buffer_t
{
    uint8 *data;
    uint32 size;
    uint32 index;
} buffer_t;



typedef struct tx_req
{
    uint8 usartID;
    buffer_t buffer;
    uint32 status;
    TX_CBF_t tx_cbf;
} tx_req;

typedef struct rx_req
{
    uint8 usartID;
    buffer_t buffer;
    uint32 status;
    RX_CBF_t rx_cbf;
} rx_req;

typedef enum
{
    USART_READY,
    USART_BUSY
}USART_ReqStatus_t;
 
/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/

extern const uart_config_t usart_config[_UART_USED_NUM];
/*static*/ tx_req TxReq;
/*static*/ rx_req RxReq;
volatile void *const uart_base_address[UART_NUM_IN_TARGET] = {
    (void *)USART1_BASE_ADDRESS,
    (void *)USART2_BASE_ADDRESS,
    (void *)UART5_BASE_ADDRESS,
    (void *)USART6_BASE_ADDRESS};

/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/

/**
 * @brief Initialize UART
 *
 * This function initializes the UART module based on the configuration settings.
 */
void UART_init(void)
{
    for (uint32 i = 0; i < _UART_USED_NUM; i++)
    {
        volatile uart_t *uart = (uart_t *)uart_base_address[usart_config[i].uartid];
        uint32 oversample;
        uint32 BRR;
        uint32 USARTDIV;

        uart->USART_CR2 |= usart_config[i].stop_bits;

        uart->USART_CR1 |= UART_ENABLE;
        uart->USART_CR1 |= usart_config[i].over_sampling;
        uart->USART_CR1 |= usart_config[i].data_size;
        uart->USART_CR1 |= usart_config[i].parity;
        /**
         * @brief Calculate the Baud rate
        */
        oversample = (usart_config[i].over_sampling == UART_OVERSAMPLING_16) ? 0 : 1;
        /**
         * Divide the mantissa and fraction
         * The mantissa is the integer part of the division
         * fraction is the decimal part of the division
         * The mantissa is calculated by dividing the USARTDIV by 16
         * The fraction is calculated by multiplying the decimal part by 16
         * The fraction is then shifted to the right by 1
         * The BRR is then calculated by combining the mantissa and fraction
        */
        USARTDIV = FCPU * 100 / (usart_config[i].baudrate * (2 - oversample) * 8);
        uint32 mantissa = USARTDIV / 100;
        uint32 fraction = ((USARTDIV - (mantissa * 100)) * 16 + 50) / 100;

        if (oversample) {
            fraction &= 0x07; // If oversampling by 8, only the 3 least significant bits of the fraction are used
    }

        BRR = (mantissa << 4) | fraction;
        uart->USART_BRR = BRR;
        uart->USART_SR = 0;
        
    }
}

/**
 * @brief Transmit data buffer asynchronously with zero copy
 *
 * This function transmits data from the buffer asynchronously with zero copy.
 * It sets up the necessary parameters and flags to initiate the transmission.
 *
 * @param Ptr_UserReq Pointer to the user request structure
 */
void USART_TxBufferAsyncZeroCopy(UART_UserReq_t *Ptr_UserReq)
{
    volatile uart_t *uart = (uart_t *)uart_base_address[usart_config[Ptr_UserReq->usartID].uartid];
    
    if (TxReq.status == USART_READY)
    {
        TxReq.buffer.data = Ptr_UserReq->ptr_buffer;
        TxReq.buffer.size = Ptr_UserReq->size;
        TxReq.buffer.index = 0;
        TxReq.tx_cbf = Ptr_UserReq->cbf;
        TxReq.status = USART_BUSY;
    }
    
    ((uart_t *)uart)->USART_CR1 |= UART_TX_ENABLE;
    ((uart_t *)uart)->USART_DR = TxReq.buffer.data[0];
    TxReq.buffer.index++;
    ((uart_t *)uart)->USART_CR1 |= UART_TXE_FLAG;
}

/**
 * @brief Receive data buffer asynchronously with zero copy
 *
 * This function receives data into the buffer asynchronously with zero copy.
 * It sets up the necessary parameters and flags to initiate the reception.
 *
 * @param Ptr_UserReq Pointer to the user request structure
 */
void USART_RxBufferAsyncZeroCopy(UART_UserReq_t *Ptr_UserReq)
{
    volatile uart_t *uart = (uart_t *)uart_base_address[usart_config[Ptr_UserReq->usartID].uartid];
    if (RxReq.status == USART_READY)
    {
        RxReq.buffer.data = Ptr_UserReq->ptr_buffer;
        RxReq.buffer.size = Ptr_UserReq->size;
        RxReq.buffer.index = 0;
        RxReq.rx_cbf = Ptr_UserReq->cbf;
        RxReq.status = USART_BUSY;
    }
     ((uart_t *)uart)->USART_CR1 |= UART_RX_ENABLE;
     ((uart_t *)uart)->USART_CR1 |= UART_RXNE_FLAG;
}

/**
 * @brief Send a single byte over UART
 *
 * This function sends a single byte over UART asynchronously.
 *
 * @param Ptr_UserReq Pointer to the user request structure
 */
void UART_sendByte(UART_UserReq_t *Ptr_UserReq)
{
    volatile uart_t *uart = (uart_t *)uart_base_address[usart_config[Ptr_UserReq->usartID].uartid];
    if (TxReq.status == USART_READY)
    {
       volatile uint32 timeout = 1000;
        TxReq.status = USART_BUSY;
        /*
        ((uart_t *)uart)->USART_CR1 |= UART_TX_ENABLE;
        ((uart_t *)uart)->USART_DR = *(Ptr_UserReq->ptr_buffer);
        */
        
        ((uart_t *)uart)->USART_DR = *(Ptr_UserReq->ptr_buffer);
        ((uart_t *)uart)->USART_CR1 |= UART_TX_ENABLE;
        
        while ((((((uart_t *)uart)->USART_SR) & UART_TC_FLAG)==0) && timeout)
        {
            timeout--;
        }
        if (timeout == 0)
        {
            //debugging
        }
        TxReq.status = USART_READY;

    }

}

/**
 * @brief Receive a single byte over UART
 *
 * This function receives a single byte over UART asynchronously.
 *
 * @param Ptr_UserReq Pointer to the user request structure
 */
void UART_receiveByte(UART_UserReq_t *Ptr_UserReq)
{
    volatile uart_t *uart = (uart_t *)uart_base_address[usart_config[Ptr_UserReq->usartID].uartid];
    if (RxReq.status == USART_READY)
    {
        volatile uint32 timeout = 1000;
        RxReq.status = USART_BUSY;
        ((uart_t *)uart)->USART_CR1 |= UART_RX_ENABLE;
        while (((((uart_t *)uart)->USART_SR & UART_RXNE_FLAG) == 1 )&& timeout)
        {
            timeout--;
        }
        *Ptr_UserReq->ptr_buffer = ((uart_t *)uart)->USART_DR;
        ((uart_t *)uart)->USART_CR1 &= ~UART_RX_ENABLE;
        RxReq.status = USART_READY;
    }
}

void USART1_IRQHandler(void)
{
    volatile uart_t *uart = (uart_t *)uart_base_address[0];
    if (RxReq.buffer.index < RxReq.buffer.size)
        {
            RxReq.buffer.data[RxReq.buffer.index] = uart->USART_DR;
            RxReq.buffer.index++;
             uart->USART_CR1 &= ~UART_RXNE_FLAG;
            RxReq.status = USART_READY;
            if (RxReq.rx_cbf != NULL_PTR)
            {
                RxReq.rx_cbf();
            }
    }
    
}

// Check if UART transmission is done
uint8 USART_txDone(uint8 usartID)
{
    volatile uart_t *uart = (uart_t *)uart_base_address[usart_config[usartID].uartid];
    return (uart->USART_SR & UART_TC_FLAG);
}

// Check if UART reception is done
uint8 USART_rxDone(uint8 usartID)
{
    volatile uart_t *uart = (uart_t *)uart_base_address[usart_config[usartID].uartid];
    return (uart->USART_SR & UART_RXNE_FLAG);
}
#if (_UART_USED_NUM > 1)
void USART2_IRQHandler(void)
{
    volatile uart_t *uart = (uart_t *)uart_base_address[usart_config[USART2].uartid];
    if (UART_TXE_FLAG & uart->USART_SR)
    {
    if (TxReq.buffer.index < TxReq.buffer.size)
    {
        uart->USART_DR = TxReq.buffer.data[TxReq.buffer.index];
        TxReq.buffer.index++;
    }
    else
    {
        uart->USART_CR1 &= ~UART_TXE_FLAG;
        uart->USART_CR1 |= UART_TC_FLAG;
        TxReq.status = USART_READY;
        if (TxReq.tx_cbf != NULL_PTR)
        {
            TxReq.tx_cbf();
        }
    }
    }
    if (UART_RXNE_FLAG & uart->USART_SR)
    {
        if (RxReq.buffer.index < RxReq.buffer.size)
        {
            RxReq.buffer.data[RxReq.buffer.index] = uart->USART_DR;
            RxReq.buffer.index++;
        }
        else
        {
            uart->USART_CR1 &= ~UART_RXNE_FLAG;
            RxReq.status = USART_READY;
            if (RxReq.rx_cbf != NULL_PTR)
            {
                RxReq.rx_cbf();
            }
        }
    }
}

void USART6_IRQHandler(void)
{
    volatile uart_t *uart = (uart_t *)uart_base_address[usart_config[USART6].uartid];
    if (UART_TXE_FLAG & uart->USART_SR)
    {
    if (TxReq.buffer.index < TxReq.buffer.size)
    {
        uart->USART_DR = TxReq.buffer.data[TxReq.buffer.index];
        TxReq.buffer.index++;
    }
    else
    {
        uart->USART_CR1 &= ~UART_TXE_FLAG;
        uart->USART_CR1 |= UART_TC_FLAG;
        TxReq.status = USART_READY;
        if (TxReq.tx_cbf != NULL_PTR)
        {
            TxReq.tx_cbf();
        }
    }
    }
    if (UART_RXNE_FLAG & uart->USART_SR)
    {
        if (RxReq.buffer.index < RxReq.buffer.size)
        {
            RxReq.buffer.data[RxReq.buffer.index] = uart->USART_DR;
            RxReq.buffer.index++;
        }
        else
        {
            uart->USART_CR1 &= ~UART_RXNE_FLAG;
            RxReq.status = USART_READY;
            if (RxReq.rx_cbf != NULL_PTR)
            {
                RxReq.rx_cbf();
            }
        }
    }
}
#endif