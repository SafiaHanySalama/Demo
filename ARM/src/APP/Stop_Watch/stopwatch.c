/******************************************************************************
*
* Module: 
*
* File Name: StopWatch.c
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

#include "app/demo.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/

extern uint8 running; // Start the StopWatch immediately

extern uint8 paused;

extern uint8 reset;

CustomTime StopWatch = {0, 0, 0};

/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/


 static void displayStopwatch(const CustomTime *StopWatch) ;

 static void updateStopwatch(CustomTime *StopWatch) ;

 static void resetStopwatch(CustomTime *StopWatch) ;

 static void pauseStopwatch(char *paused);


/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/

void MCU1_StopWatch(void)
 {

 /* Start , End , Puase , Reset */
      if (running)
     {
        if (!paused)
         {
             updateStopwatch(&StopWatch);
        }
        else if (reset)
        {
        	resetStopwatch(&StopWatch);
        }
        else
        {

        }
         displayStopwatch(&StopWatch);
     }
      else
      {

      }
 }


static void resetStopwatch(CustomTime *StopWatch) {
     StopWatch->hours = 0;
     StopWatch->minutes = 0;
     StopWatch->seconds = 0;
 }

static void updateStopwatch(CustomTime *StopWatch) {
     StopWatch->seconds++;
     if (StopWatch->seconds > 60) {
         StopWatch->seconds = 0;
         StopWatch->minutes++;
         if (StopWatch->minutes > 60) {
             StopWatch->minutes = 0;
             StopWatch->hours++;
         }
     }
 }

static void displayStopwatch(const CustomTime *StopWatch) {

    static uint8 count= 0;
    const uint8* Timebreak = ":";
    const uint8* Daybreak = "/";
    const uint32 zero = 0;
    static uint8 Firstflag = 0;
    if (Firstflag == 0)
    {
        LCD_clearScreenAsynch();
        Firstflag = 1;
    }
    else
    {
        count++;
        if (count == 1)
        {
            LCD_setCursorPosAsync(START_X_POSITION, START_Y_POSITION + 5);
        }
        else if (count == 2)
        {
            updateCustomTime(&StopWatch);
            if (StopWatch->hours<10)
            {
                LCD_writeNumberAsync(zero);
            }
            LCD_writeNumberAsync(StopWatch->hours);
            
        }
        else if (count == 3)
        {
            LCD_writeStringAsync(Timebreak,1);
        }
        else if (count == 4)
        {
            if (StopWatch->minutes<10)
            {
                LCD_writeNumberAsync(zero);
            }
            LCD_writeNumberAsync(StopWatch->minutes);
        }
        else if (count == 5)
        {
            LCD_writeStringAsync(Timebreak,1);
        }
        else if (count == 6)
        {
            if (StopWatch->seconds <10)
            {
                LCD_writeNumberAsync(zero);
            }
            LCD_writeNumberAsync(StopWatch->seconds);
        }
    }

 }


static void pauseStopwatch(char *paused) {
    *paused = !(*paused); // Toggle paused state
 }

