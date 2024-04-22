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
uint8 entered_once = 0;

volatile uint8 running = FALSE; // Start the StopWatch immediately

extern uint8 paused;

extern uint8 reset;

CustomTime StopWatch = {0, 0, 0};

extern CustomTime currentTime;

/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/


 /*static*/ void displayStopwatch(const CustomTime *StopWatch) ;

 void updateStopwatch(CustomTime *StopWatch) ;

 void resetStopwatch(CustomTime *StopWatch) ;

 void pauseStopwatch(char *paused);


/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/

void MCU1_StopWatch(void)
 {
    static uint8 count= 0;
    const uint8* Timebreak = ":";
    const uint8* Daybreak = "/";
    const uint32 zero = 0;
    static uint8 Firstflag = 0;
 /* Start , End , Puase , Reset */
      if (running)
     {
        static uint8 count =0;
        if (!paused)
         {
/*             count++;
            if(count <= 10){
                updateStopwatch(&StopWatch);
                count =0;
            }
            displayStopwatch(&StopWatch); */
        if (Firstflag == 0)
        {
            LCD_clearScreenAsynch();
            Firstflag = 1;
            entered_once =1;
        }
        else
        {
            count++;
            if (count == 1)
            {
                LCD_setCursorPosAsync(START_X_POSITION, START_Y_POSITION );
            }
            else if (count == 2)
            {
                updateStopwatch(&StopWatch);
                updateCustomTime(&currentTime);
                if (StopWatch.hours<10)
                {
                    LCD_writeNumberAsync(zero);
                }
            } 
            else if (count == 3) {
                LCD_writeNumberAsync(StopWatch.hours);
            }  
            
            else if (count == 4)
            {
                LCD_writeStringAsync(Timebreak,1);
            }
            else if (count == 5)
            {
                if (StopWatch.minutes<10)
                {
                    LCD_writeNumberAsync(zero);
                }
                
            }
            else if (count == 6){
                LCD_writeNumberAsync(StopWatch.minutes);
            }
            else if (count == 7)
            {
                LCD_writeStringAsync(Timebreak,1);
            }
            else if (count == 8)
            {
                if (StopWatch.seconds <10)
                {
                    LCD_writeNumberAsync(zero);
                }
            }
            else if(count ==9){
                LCD_writeNumberAsync(StopWatch.seconds);
                count =0;
            }
        }
            }
        if (reset)
        {
            
            resetStopwatch(&StopWatch);
            reset =FALSE;
            //displayStopwatch(&StopWatch);
        }
        // displayStopwatch(&StopWatch);
            
        }
 }


void resetStopwatch(CustomTime *StopWatch) {
     StopWatch->hours = 0;
     StopWatch->minutes = 0;
     StopWatch->seconds = 0;
 }

void updateStopwatch(CustomTime *StopWatch) {
     StopWatch->seconds++;
     if (StopWatch->seconds >= 60) {
         StopWatch->seconds = 0;
         StopWatch->minutes++;
         if (StopWatch->minutes >= 60) {
             StopWatch->minutes = 0;
             StopWatch->hours++;
         }
     }
 }

/*static */void displayStopwatch(const CustomTime *StopWatch) {

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
            //updateStopwatch(&StopWatch);
            if (StopWatch->hours<10)
            {
                LCD_writeNumberAsync(zero);
            }
        } 
        else if (count == 3) {
            LCD_writeNumberAsync(StopWatch->hours);
        }  
        
        else if (count == 4)
        {
            LCD_writeStringAsync(Timebreak,1);
        }
        else if (count == 5)
        {
            if (StopWatch->minutes<10)
            {
                LCD_writeNumberAsync(zero);
            }
            
        }
         else if (count == 6){
            LCD_writeNumberAsync(StopWatch->minutes);
        }
        else if (count == 7)
        {
            LCD_writeStringAsync(Timebreak,1);
        }
        else if (count == 8)
        {
            if (StopWatch->seconds <10)
            {
                LCD_writeNumberAsync(zero);
            }
        }
        else if(count ==9){
            LCD_writeNumberAsync(StopWatch->seconds);
            count =0;
        }
    }

 }


void pauseStopwatch(char *paused) {
    *paused = 1; // Toggle paused state
 }

