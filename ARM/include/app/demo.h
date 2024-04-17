/******************************************************************************
*
* Module: 
*
* File Name: demo.h
*

* Description: 
*
* Author: Team7
* 
* Date:  16/4/2024
******************************************************************************/


/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include <stdio.h>

#include "STD_TYPES.h"
#include "app/runnables.h"
#include "hal/switch.h"
#include "services/sched.h"
#include "mcal/UART.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

#define TRUE 1

#define FALSE 0

#define MODE_TIMENDATE 0
#define MODE_SW  1

#define MAX_LCD_COL  15
#define MAX_LCD_ROW 2

#define START_X_POSITION 0
#define START_Y_POSITION 0

#define SIZE_BUFFER1 9

#define SIZE_BUFFER2 11

#define SIZE_BUFFER3 33

/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

typedef struct {
    uint32 hours;
    uint32 minutes;
    uint32 seconds;
    uint32 dayPassed;
}CustomTime;

typedef struct  {
    uint32 day;
    uint32 month;
    uint32 year;
}CustomDate;


/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/

void MCU1_SwitchesTx(void);
void MCU1_UARTSignalRx(void);
void MCU1_Clock(void);
void MCU1_StopWatch(void);