/******************************************************************************
*
* Module: 
*
* File Name: lcd.h
*

* Description: 
*
* Author: Safia Hany
* 
* Date:  1/4/2024
******************************************************************************/
#ifndef HAL_LCD_H_
#define HAL_LCD_H_


/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "Std_Types.h"
#include "mcal/gpio.h"
#include "hal/lcd_cfg.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/
typedef struct
{
    /* data */
    void* port;
    GPIO_PinType pin;
}LCD_Pin_t;

typedef struct
{
    /* data */
    LCD_Pin_t Data_Pins[8];
    LCD_Pin_t RS_Pin;
    LCD_Pin_t RW_Pin;
    LCD_Pin_t E_Pin;
}LCD_Conn_t;



/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/


void LCD_writeStringAsync(const uint8* string,uint8 length);

void LCD_setCursorPosAsync(uint8 posX, uint8 posY);

void LCD_clearScreenAsynch(void);

uint8 LCD_getStatus(void);

void LCD_initAsync();


#endif // HAL_LCD_H_