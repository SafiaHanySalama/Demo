/******************************************************************************
 *
 * Module: 
 *
 * File Name: gpio.h
 *
 * Description: 
 *
 * Author: Safia Hany
 * 
 * Date:  Feb 26, 2024
 ******************************************************************************/
#include "Std_Types.h"

#ifndef MCAL_GPIO_GPIO_H_
#define MCAL_GPIO_GPIO_H_

#define GPIO_PORTA  				(void *)(0x40020000)
#define GPIO_PORTB					(void *)(0x40020400)
#define GPIO_PORTC  				(void *)(0x40020800)
#define GPIO_PORTD 					(void *)(0x40020C00)
#define GPIO_PORTE 					(void *)(0x40021000)
#define GPIO_PORTH					(void *)(0x40021C00)

#define GPIO_MODE_IN_FL						0x00
#define GPIO_MODE_IN_PU						0x08
#define GPIO_MODE_IN_PD						0x10

#define GPIO_MODE_OUT_PP 					0x01
#define GPIO_MODE_OUT_PP_PU					0x09
#define GPIO_MODE_OUT_PP_PD					0x11
#define GPIO_MODE_OUT_OD					0x05
#define GPIO_MODE_OUT_OD_PL					0x0D
#define GPIO_MODE_OUT_OD_PD					0x15

#define GPIO_MODE_ANALOG 					0x03

#define GPIO_MODE_AF_PP 					0x02
#define GPIO_MODE_AF_PP_PU					0x0A
#define GPIO_MODE_AF_PP_PD					0x12
#define GPIO_MODE_AF_OD						0x06
#define GPIO_MODE_AF_OD_PL					0x0E
#define GPIO_MODE_AF_OD_PD					0x16

#define GPIO_SET_PIN 					0x00000001
#define GPIO_RESET_PIN 					0x00010000

typedef enum
{
	GPIO_LOW_SPEED,
	GPIO_MEDUIM_SPEED,
	GPIO_HIGH_SPEED,
	GPIO_VHIGH_SPEED,
}GPIO_SPEED;

typedef enum
{
	PIN0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15,
	PIN16
}GPIO_PinType;


typedef struct
{
	void* 	  Port;
	GPIO_PinType  Pin;
	GPIO_SPEED  Speed;
	uint32  Mode;

}GPIO_ConfigPin_t;

typedef enum
{
	GPIO_ERROR,
	GPIO_OK,
	INVALID_PORT_NUM,
	INVALID_PIN_NUM
}GPIO_ERROR_t;



GPIO_ERROR_t GPIO_init(GPIO_ConfigPin_t *Config_ptr);

GPIO_ERROR_t GPIO_setPinValue(void* port,uint32 pin, uint32 value);

uint32 GPIO_getPinValue(void* port,uint32 pin);

#endif /* MCAL_GPIO_GPIO_H_ */
