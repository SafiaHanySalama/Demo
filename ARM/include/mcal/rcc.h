/******************************************************************************
 *
 * Module: RCC
 *
 * File Name: rcc.h
 *
 * Description: 
 *
 * Author: Safia Hany
 * 
 * Date:  Feb 25, 2024
 ******************************************************************************/
#ifndef MCAL_RCC_RCC_H_
#define MCAL_RCC_RCC_H_

#include "Std_Types.h"

#define SYS_CLR_MASK			0xFFFFFFFC
#define PLL_SRC_CLR_MASK 		0xFFBFFFFF
#define PLL_CFG_CLR_MASK		0XF0FC8000
#define APB2_PRE_CLR_MASK   0XFFFF1FFF
#define APB1_PRE_CLR_MASK   0XFFFFE3FF
#define AHB_PRE_CLR_MASK    0XFFFFFF0F

//PLL Config
#define MIN_PLLM				2
#define MAX_PLLM				63
#define MIN_PLLN				192
#define MAX_PLLN				432
#define MIN_PLLP				2
#define MAX_PLLP				8
#define INVALID1_PLLP			3
#define INVALID2_PLLP			5
#define MIN_PLLQ				2
#define MAX_PLLQ				15
#define PLL_N_SHIFT				6
#define PLL_P_SHIFT				16
#define PLL_Q_SHIFT				24
//Peripherals IDs

/************AHB1_BUS_Peripheral_Masks ************/
#define GPIOA	0x00000001
#define GPIOB	0x00000002
#define GPIOC	0x00000004
#define GPIOD	0x00000008
#define GPIOE	0x00000010
#define GPIOH	0x00000080
#define CRC 	0x00001000
#define DMA1	0x00200000
#define DMA2	0x00400000
/************AHB2_BUS_Peripheral_Masks ************/
#define OTGFS	BIT7_MASK
/************APB1_BUS_Peripheral_Masks ************/
#define TIM2	0x00000001
#define TIM3	0x00000002
#define TIM4	0x00000004
#define TIM5	0x00000008
#define WWDG	0x00000800
#define SPI2	0x00004000
#define SPI3	0x00008000
#define USART2	0x00020000
#define I2C1	0x00200000
#define I2C2	0x00400000
#define I2C3	0x00800000
#define PWR		0x10000000
/************APB2_BUS_Peripheral_Masks ************/
#define TIM1	0x00000001
#define USART1	0x00000010
#define USART6	0x00000020
#define ADC1	0x00000100
#define SDIO	0x00000800
#define SPI1	0x00001000
#define SPI4	0x00004000
#define SYSCFG	0x00008000
#define TIM9	0x00010000
#define TIM10	0x00040000
#define TIM11	0x00080000
//BUS Prescaler
/************APB_High_Speed_BUS_Prescaler_Masks ************/
#define APB2_1   	0x00000000
#define APB2_2  	0x00008000
#define APB2_4 		0x0000A000
#define APB2_8  	0x0000C000
#define APB2_16		0x0000E000
/************APB_LOW_Speed_BUS_Prescaler_Masks ************/
#define APB1_1   	0x00000000
#define APB1_2  	0x00001000
#define APB1_4 		0x00001400
#define APB1_8  	0x00001800
#define APB1_16		0x00001C00
/************AHB_BUS_Prescaler_Masks ************/
#define AHB_1   	0x00000000
#define AHB_2  		0x00000080
#define AHB_4 		0x00000090
#define AHB_8  		0x000000A0
#define AHB_16		0x000000B0
#define AHB_64 		0x000000C0
#define AHB_128 	0x000000D0
#define AHB_256  	0x000000E0
#define AHB_512		0x000000f0
//


typedef enum{
    RCC_NOK,

    RCC_OK
}RCC_ERROR_STATUS;

typedef enum
{
	HSI,
	HSE,
	PLL

}CLK_SRC;

typedef enum
{
	HSI_DIV2,
	HSE_DIV2,
	HSE_NO_DIV
}PLL_SRC;

typedef enum
{
	PLL_input_clock_x2,
	PLL_input_clock_x3,
	PLL_input_clock_x4,
	PLL_input_clock_x5,
	PLL_input_clock_x6,
	PLL_input_clock_x7,
	PLL_input_clock_x8,
	PLL_input_clock_x9,
	PLL_input_clock_x10,
	PLL_input_clock_x11,
	PLL_input_clock_x12,
	PLL_input_clock_x13,
	PLL_input_clock_x14,
	PLL_input_clock_x15,
	PLL_input_clock_x16
}PLL_MUL;

typedef enum{
    RCC_AHB1,
    RCC_AHB2,
    RCC_APB1,
    RCC_APB2
}RCC_BUS_ID_t;


RCC_ERROR_STATUS RCC_enableClk(CLK_SRC clk);

RCC_ERROR_STATUS RCC_disableClk(CLK_SRC clk);

RCC_ERROR_STATUS RCC_setSysClk(CLK_SRC clk);

RCC_ERROR_STATUS RCC_pllConfig(uint8 PLLM,uint8 PLLN,uint8 PLLP,uint8 PLLQ,PLL_SRC PLLclk);

RCC_ERROR_STATUS RCC_enablePeri(RCC_BUS_ID_t busID, uint32 P_id);

RCC_ERROR_STATUS RCC_disablePeri(RCC_BUS_ID_t busID, uint32 P_id);

RCC_ERROR_STATUS RCC_prescalerConfig(RCC_BUS_ID_t busID,uint32  prescalar);

#endif /* MCAL_RCC_RCC_H_ */
