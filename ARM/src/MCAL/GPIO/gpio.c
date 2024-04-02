/******************************************************************************
 *
 * Module: 
 *
 * File Name: gpio.c
 *
 * Description: 
 *
 * Author: Safia Hany
 * 
 * Date:  Feb 26, 2024
 ******************************************************************************/
#include <Std_Types.h>
#include "mcal/gpio.h"

#define GPIO_MODE_MASK     		 	0x03
#define GPIO_OUT_TYPE_MASK  		0x04
#define GPIO_PULL_TYPE_MASK 		0x018
#define GPIO_OUT_TYPE_SHIFT         2
#define GPIO_PULL_TYPE_SHIFT        3
#define GPIO_GROUP_OF_2_BITS        2
#define GPIO_GROUP_OF_3_BITS        3

typedef struct
{
	uint32 MODER;
	uint32 OTYPER;
	uint32 OSPEEDR;
	uint32 PUPDR;
	uint32 IDR;
	uint32 ODR;
	uint32 BSRR;
	uint32 LCKR;
	uint32 AFRL;
	uint32 AFRH;
}GPIO_PortReg;

GPIO_ERROR_t GPIO_init(GPIO_ConfigPin_t *Config_ptr){
	GPIO_ERROR_t Return_Status = GPIO_OK;
	uint32 temp=0;
	uint32 moder = ((GPIO_PortReg *)Config_ptr ->Port) -> MODER;
	uint32 otyper = ((GPIO_PortReg *)Config_ptr ->Port) -> OTYPER;
	uint32 ospeedr = ((GPIO_PortReg *)Config_ptr ->Port) -> OSPEEDR;
	uint32 pupdr = ((GPIO_PortReg *)Config_ptr ->Port) -> PUPDR;
	if(Config_ptr == NULL_PTR)
	{
		Return_Status = GPIO_ERROR;
	}
	else if ( (Config_ptr -> Pin) < PIN0 ||(Config_ptr -> Pin) > PIN15 )
	{
		Return_Status = INVALID_PIN_NUM;
	}
	else if ((Config_ptr -> Speed) < GPIO_LOW_SPEED || (Config_ptr -> Speed) > GPIO_VHIGH_SPEED)
	{
		Return_Status = GPIO_ERROR;
	}
	else {
		moder  &= ~(0x03 << ((Config_ptr -> Pin)*2)) ;
		otyper &= ~(0x01 << ((Config_ptr -> Pin)))    ;
		ospeedr &= ~(0x03 << ((Config_ptr -> Pin)*2)) ;
		pupdr  &= ~(0x03 << ((Config_ptr -> Pin)*2)) ;

		temp = (Config_ptr->Mode) & GPIO_MODE_MASK;
		moder|=temp << ((Config_ptr->Pin) * 2);

		temp = ((Config_ptr->Mode) & GPIO_OUT_TYPE_MASK) >> GPIO_OUT_TYPE_SHIFT; 
		otyper |=temp <<(Config_ptr->Pin);

        temp = ((Config_ptr->Mode) & GPIO_PULL_TYPE_MASK) >> GPIO_PULL_TYPE_SHIFT; 
        pupdr |= (temp << ((Config_ptr->Pin) * 2));

		ospeedr |= ((Config_ptr->Speed) << ((Config_ptr->Pin) * 2));


		((GPIO_PortReg *)Config_ptr ->Port) -> MODER = moder;
		((GPIO_PortReg *)Config_ptr ->Port) -> OTYPER = otyper;
		((GPIO_PortReg *)Config_ptr ->Port) -> OSPEEDR = ospeedr;
		((GPIO_PortReg *)Config_ptr ->Port) -> PUPDR = pupdr;
	}
	return Return_Status;
}

GPIO_ERROR_t GPIO_setPinValue(void* port,uint32 pin, uint32 value){
	GPIO_ERROR_t Return_Status = GPIO_OK;
	if (value == 0 ) value = GPIO_RESET_PIN;
	else value = GPIO_SET_PIN;
	if (port == NULL_PTR)
	{
		Return_Status = INVALID_PORT_NUM;
	}
	else if ( pin < PIN0 ||pin > PIN15 )
	{
		Return_Status = INVALID_PIN_NUM;
	}
	else
	{
		((GPIO_PortReg *)port )-> BSRR = value << pin ;
	}
	return Return_Status;
}

uint32 GPIO_getPinValue(void* port,uint32 pin){
	uint32 value = ((((GPIO_PortReg *)port )-> IDR) & (1 << pin)) >> pin ;

	return value;
}
