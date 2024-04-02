/******************************************************************************
*
* Module: 
*
* File Name: lcd_cfg.c
*

* Description: 
*
* Author: Safia Hany
* 
* Date:  1/4/2024
******************************************************************************/

#include "hal/lcd.h"


const LCD_Conn_t LCD_Config = {

    .Data_Pins[0].port = GPIO_PORTC,
    .Data_Pins[0].pin = PIN0,

    .Data_Pins[1].port = GPIO_PORTC,
    .Data_Pins[1].pin = PIN1,

    .Data_Pins[2].port = GPIO_PORTC,
    .Data_Pins[2].pin = PIN2,

    .Data_Pins[3].port = GPIO_PORTC,
    .Data_Pins[3].pin = PIN3,

    .Data_Pins[4].port = GPIO_PORTC,
    .Data_Pins[4].pin = PIN4,

    .Data_Pins[5].port = GPIO_PORTC,
    .Data_Pins[5].pin = PIN5, 

    .Data_Pins[6].port = GPIO_PORTC,
    .Data_Pins[6].pin = PIN6,  

    .Data_Pins[7].port = GPIO_PORTC,
    .Data_Pins[7].pin = PIN7,

    .RS_Pin.port = GPIO_PORTD,
    .RS_Pin.pin = PIN0,

    .RW_Pin.port = GPIO_PORTD,
    .RW_Pin.pin = PIN1,

    .E_Pin.port = GPIO_PORTD,
    .E_Pin.pin = PIN2
};