#ifndef RCC_H
#define RCC_H

#include "std_types.h"

/********************************Defines*****************************/
#define 	RCC_PLLCFGR_PLLP_DIV2   0x0
#define 	RCC_PLLCFGR_PLLP_DIV4   0x1
#define 	RCC_PLLCFGR_PLLP_DIV6   0x2
#define 	RCC_PLLCFGR_PLLP_DIV8   0x3
#define 	_RCC_PLLCFGR_PLLSRC    ((u32)0x00400000)
#define 	RCC_PLL_SRC_HSI 	~_RCC_PLLCFGR_PLLSRC
#define 	RCC_PLL_SRC_HSE		_RCC_PLLCFGR_PLLSRC

// Macros for RCC_CR register clock enable bits
#define RCC_CR_HSION    ((u32)0x00000001)
#define RCC_CR_HSEON    ((u32)0x00010000)
#define RCC_CR_HSEBYP   ((u32)0x00040000)
#define RCC_CR_PLLON    ((u32)0x01000000)
#define RCC_CR_PLLI2SON ((u32)0x04000000)

#define RCC_EN_HSI 			RCC_CR_HSION
#define RCC_EN_HSE			RCC_CR_HSEON
#define RCC_EN_PLL 			RCC_CR_PLLON
#define RCC_EN_HSEBYP		RCC_CR_HSEBYP
#define RCC_EN_PLLI2SON 	RCC_CR_PLLI2SON

// RCC AHB1 peripheral clock enable register (RCC_AHB1ENR)
#define RCC_AHB1_GPIOAEN    (0x0000000100000001)
#define RCC_AHB1_GPIOBEN    (0x0000000100000002)
#define RCC_AHB1_GPIOCEN    (0x0000000100000004)
#define RCC_AHB1_GPIODEN    (0x0000000100000008)
#define RCC_AHB1_GPIOEEN    (0x0000000100000010)
#define RCC_AHB1_GPIOHEN    (0x0000000100000080)
#define RCC_AHB1_CRCEN      (0x0000000100001000)
#define RCC_AHB1_DMA1EN     (0x0000000100200000)
#define RCC_AHB1_DMA2EN     (0x0000000100400000)
// RCC APB1 peripheral clock enable register (RCC_APB1ENR)
#define RCC_APB1_TIM2EN     (0x0000000200000001)
#define RCC_APB1_TIM3EN     (0x0000000200000002)
#define RCC_APB1_TIM4EN     (0x0000000200000004)
#define RCC_APB1_TIM5EN     (0x0000000200000008)
#define RCC_APB1_WWDGEN     (0x0000000200000800)
#define RCC_APB1_SPI2EN     (0x0000000200004000)
#define RCC_APB1_SPI3EN     (0x0000000200008000)
#define RCC_APB1_USART2EN   (0x0000000200020000)
#define RCC_APB1_I2C1EN     (0x0000000200200000)
#define RCC_APB1_I2C2EN     (0x0000000200400000)
#define RCC_APB1_I2C3EN     (0x0000000200800000)
#define RCC_APB1_PWREN      (0x0000000210000000)
// RCC APB2 peripheral clock enable register (RCC_APB2ENR)
#define RCC_APB2_TIM1EN     (0x0000000400000001)
#define RCC_APB2_USART1EN   (0x0000000400000010)
#define RCC_APB2_USART6EN   (0x0000000400000020)
#define RCC_APB2_ADC1EN     (0x0000000400000100)
#define RCC_APB2_SDIOEN     (0x0000000400000800)
#define RCC_APB2_SPI1EN     (0x0000000400001000)
#define RCC_APB2_SPI4EN     (0x0000000400002000)
#define RCC_APB2_SYSCFGEN   (0x0000000400004000)
#define RCC_APB2_TIM9EN     (0x0000000400010000)
#define RCC_APB2_TIM10EN    (0x0000000400020000)
#define RCC_APB2_TIM11EN    (0x0000000400040000)

#define RCC_PRE_AHB_SYSCLK_NOT_DIVIDED   0x0000000800000000  // 0xxx: system clock not divided
#define RCC_PRE_AHB_SYSCLK_DIV_BY_2      0x0000000800000080  // 1000: system clock divided by 2
#define RCC_PRE_AHB_SYSCLK_DIV_BY_4      0x0000000800000090  // 1001: system clock divided by 4
#define RCC_PRE_AHB_SYSCLK_DIV_BY_8      0x00000008000000A0  // 1010: system clock divided by 8
#define RCC_PRE_AHB_SYSCLK_DIV_BY_16     0x00000008000000B0  // 1011: system clock divided by 16
#define RCC_PRE_AHB_SYSCLK_DIV_BY_64     0x00000008000000C0  // 1100: system clock divided by 64
#define RCC_PRE_AHB_SYSCLK_DIV_BY_128    0x00000008000000D0  // 1101: system clock divided by 128
#define RCC_PRE_AHB_SYSCLK_DIV_BY_256    0x00000008000000E0  // 1110: system clock divided by 256
#define RCC_PRE_AHB_SYSCLK_DIV_BY_512    0x00000008000000F0  // 1111: system clock divided by 512
#define RCC_PRE_APB1_NO_DIV 			 0x0000000900000000
#define RCC_PRE_APB1_DIV_BY_2 			 0x0000000900001000
#define RCC_PRE_APB1_DIV_BY_4 			 0x0000000900001400
#define RCC_PRE_APB1_DIV_BY_8			 0x0000000900001800
#define RCC_PRE_APB1_DIV_BY_16			 0x0000000900001C00
#define RCC_PRE_APB2_NO_DIV 			 0x0000000A00000000
#define RCC_PRE_APB2_DIV_BY_2 			 0x0000000A00008000
#define RCC_PRE_APB2_DIV_BY_4 			 0x0000000A0000A000
#define RCC_PRE_APB2_DIV_BY_8			 0x0000000A0000C000
#define RCC_PRE_APB2_DIV_BY_16			 0x0000000A0000E000

#define RCC_Peripheral_Enable 0
#define RCC_Peripheral_Disable 1

/********************************Type Definitions********************/

// cppcheck-suppress syntaxError
typedef enum{
	RCC_enumNok,
	RCC_enumOk,
	RCC_enumWrongPLLConfiguration,
	RCC_enumPLLSourceNotEnabled,
	RCC_enumSysClockNotEnabled
}RCC_ErrorStatus_t;

typedef enum{
	RCC_CLK_HSI,
	RCC_CLK_HSE,
	RCC_CLK_PLL
}RCC_enuClock_t;

/********************************Function Prototypes*****************/
/*Options:
 *	 	RCC_EN_xx
 */
RCC_ErrorStatus_t enableClock(u32 clk_enable);
RCC_ErrorStatus_t disableClock(u32 clk);

/*Options for source:
 * 		RCC_PLL_SRC_xx
 * */
RCC_ErrorStatus_t configurePLL(u16 PLLM, u16 PLLN,u8 PLLP,u32 source);
/*Options:
 * 		RCC_CLK_xx
 */
RCC_ErrorStatus_t selectSysClock(RCC_enuClock_t syscCk);
//RCC_ErrorStatus_t enablePeripheral();
//RCC_ErrorStatus_t disablePeripheral();
/*
 * Options of control:
 * 		RCC_Peripheral_xx
 * */
RCC_ErrorStatus_t controlPeripheral(u64 peripheral ,u8 control);
/*Options:
 * RCC_PRE_xx
 * */
RCC_ErrorStatus_t configure_prescalers(u64 prescale);
#endif /*__RCC_H*/
