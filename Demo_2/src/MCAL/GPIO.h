#ifndef __GPIO_H_
#define __GPIO_H_
//#include "GPIO_CFG.h"
//#include "mask.h"
#include "std_types.h"

typedef struct {
	u32 mode;
	u32 type;
	u32 pupd;
}gpiomode_t;

typedef struct{
	void* port;
	u32 pin;
	u32 speed;
	gpiomode_t* mode_t;
}gpiopin_t;

typedef enum{
	GPIO_enum_Nok,
	GPIO_enum_Ok,
	GPIO_enum_invalidValue,
	GPIO_enum_NullPointer
}GPIO_Error_t;

#define gpio_speed_veryhigh 3
#define gpio_speed_high  2
#define gpio_speed_medium 1
#define gpio_speed_low 0
/*output mode
#define gpio_mode_out_pp_no_pu_pd   0
#define gpio_mode_out_pp_pu   1
#define gpio_mode_out_pp_pd   2
#define gpio_mode_out_od_no_pu_pd   0
#define gpio_mode_out_od_pu  1
#define gpio_mode_out_od_pd   2

#define gpio_mode_in_floationg 0
#define gpio_mode_in_pu	1
#define gpio_mode_in_pd 2
analog
#define gpio_mode_analog_no_pu_pd  0
alternative function mode
#define gpio_mode_alterfunc_pp_no_pu_pd 0
#define gpio_mode_alterfunc_pp_pu  1
#define gpio_mode_alterfunc_pp_pd  2
#define gpio_mode_alterfunc_od_no_pu_pd  0
#define gpio_mode_alterfunc_od_pu  1
#define gpio_mode_alterfunc_od_pd  2
*/
#define gpio_mode_in 0
#define gpio_mode_out 1
#define gpio_mode_AF 2
#define gpio_mode_analog 3

#define gpio_type_pp 0
#define gpio_type_od 1

#define gpio_pupd_no_pu_pd 0
#define gpio_pupd_pu 1
#define gpio_pupd_pd 2

#define GPIO_AF0_System 0
#define GPIO_AF1_TIM1	1
#define GPIO_AF1_TIM2	1
#define GPIO_AF2_TIM3	2
#define GPIO_AF2_TIM4	2
#define GPIO_AF2_TIM5	2
#define GPIO_AF3_TIM9	3
#define GPIO_AF3_TIM10	3
#define GPIO_AF3_TIM11	3
#define GPIO_AF4_I2C1	4
#define GPIO_AF4_I2C2	4
#define GPIO_AF4_I2C3	4
#define GPIO_AF5_SPI1	5
#define GPIO_AF5_SPI2	5
#define GPIO_AF5_SPI4	5
#define GPIO_AF6_SPI3	6
#define GPIO_AF7_USART1 7
#define GPIO_AF7_USART2 7
#define GPIO_AF8_USART6 8
#define GPIO_AF9_I2C2 	9
#define GPIO_AF9_I2C3	9
#define GPIO_AF10_OTG_FS	 0xA
#define GPIO_AF12_SDIO		 0xC
#define GPIO_AF15_EVENTOUT	 0xF

#define GPIOA (void*)(0x40020000)
#define GPIOB (void*)(0x40020400)
#define GPIOC (void*)(0x40020800)
#define GPIOD (void*)(0x40020C00)
#define GPIOE (void*)(0x40021000)
#define GPIOH (void*)(0x40021C00)
/*
#define PIN0 BIT0_MASK
#define PIN1 BIT1_MASK
#define PIN2 BIT2_MASK
#define PIN3 BIT3_MASK
#define PIN4 BIT4_MASK
#define PIN5 BIT5_MASK
#define PIN6 BIT6_MASK
#define PIN7 BIT7_MASK
#define PIN8 BIT8_MASK
#define PIN9 BIT9_MASK
#define PIN10 BIT10_MASK
#define PIN11 BIT11_MASK
#define PIN12 BIT12_MASK
#define PIN13 BIT13_MASK
#define PIN14 BIT14_MASK
#define PIN15 BIT15_MASK
#define PIN16 BIT16_MASK
#define PIN17 BIT17_MASK
#define PIN18 BIT18_MASK
#define PIN19 BIT19_MASK
#define PIN20 BIT20_MASK
#define PIN21 BIT21_MASK
#define PIN22 BIT22_MASK
#define PIN23 BIT23_MASK
#define PIN24 BIT24_MASK
#define PIN25 BIT25_MASK
#define PIN26 BIT26_MASK
#define PIN27 BIT27_MASK
#define PIN28 BIT28_MASK
#define PIN29 BIT29_MASK
#define PIN30 BIT30_MASK
#define PIN31 BIT31_MASK
*/

#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7
#define PIN8 8
#define PIN9 9
#define PIN10 10
#define PIN11 11
#define PIN12 12
#define PIN13 13
#define PIN14 14
#define PIN15 15
#define PIN16 16
#define PIN17 17
#define PIN18 18
#define PIN19 19
#define PIN20 20
#define PIN21 21
#define PIN22 22
#define PIN23 23
#define PIN24 24
#define PIN25 25
#define PIN26 26
#define PIN27 27
#define PIN28 28
#define PIN29 29
#define PIN30 30
#define PIN31 31

typedef struct {
	u32 MODER;
	u32 OTYPER;
	u32 OSPEEDR;
	u32 PUPDR;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 LCKR;
	u32 AFRL;
	u32 AFRH;
}gpio_t;

GPIO_Error_t gpio_initPin(gpiopin_t * pin);
GPIO_Error_t gpio_setPinValue(void* port,u32 pin,u8 value);
u8 gpio_getPinValue(void* port,u32 pin);
GPIO_Error_t gpio_setAF(u32 value, void* port,u16 pin);

#endif
