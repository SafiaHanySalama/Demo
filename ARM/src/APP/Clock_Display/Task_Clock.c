/******************************************************************************
*
* Module: 
*
* File Name: Task_Clock.c
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
/************************************************Variables***********************************************/
/********************************************************************************************************/

extern CustomTime currentTime;
extern CustomDate currentDate;
extern uint32 g_timer;
/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/


 static void updateCustomTime(CustomTime *time);
 static uint8 isLeapYear(uint8 year) ;
 static void updateCustomDate(CustomDate *date, CustomTime *time) ;

/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/


 /*
  * Runnable for CLOCK -> 100 ms
  * The clock needs to be updated even if this mode is not activated
  * date
  * time
  */



 void MCU1_Clock(void)
 {
 /* We need to check if it's the first tkime to start the system */
    static uint8 count=0;
    const uint8 Timebreak = ":";
    const uint8 Daybreak = "/";
    const uint8 zero = "0";

	uint8 Buffer1[SIZE_BUFFER1];
    uint8 Buffer2[SIZE_BUFFER2];
    sprintf(Buffer1,"%02d:%02d:%02d", currentTime.hours, currentTime.minutes, currentTime.seconds);
    sprintf(Buffer2,"%02d/%02d/%04d", currentDate.day, currentDate.month, currentDate.year);
    count++;
    if (count == 1)
    {
        //LCD_clearScreenAsynch();
        LCD_setCursorPosAsync(START_X_POSITION, START_Y_POSITION);
    }
    else if (count == 2)
    {
        updateCustomTime(&currentTime);
        LCD_writeStringAsync(&Buffer1,SIZE_BUFFER1);
/*         if (currentTime.hours<10)
        {
            LCD_writeStringAsync(&zero,1);
        }
        LCD_writeNumberAsync(currentTime.hours);
        LCD_writeStringAsync(&Timebreak,1);
        if (currentTime.hours<10)
        {
            LCD_writeStringAsync(&zero,1);
        }
        LCD_writeNumberAsync(currentTime.minutes);
        LCD_writeStringAsync(&Timebreak,1);
        if (currentTime.seconds<10)
        {
            LCD_writeStringAsync(&zero,1);
        }
        LCD_writeNumberAsync(currentTime.seconds);*/
    } 
    else if (count == 3)
    {
        LCD_setCursorPosAsync(START_X_POSITION+1,START_Y_POSITION);
    }
    else if (count == 4)
    {
        updateCustomDate(&currentDate, &currentTime); // Pass both time and date structures
        LCD_writeStringAsync(&Buffer2,SIZE_BUFFER2);
/*         LCD_writeNumberAsync(currentDate.day);
        LCD_writeStringAsync(&Daybreak,1);
        LCD_writeNumberAsync(currentDate.month);
        LCD_writeStringAsync(&Daybreak,1);
        LCD_writeNumberAsync(currentDate.year);  */      
        count =0;
    }

    
}

 /* Displaying runnable for lcd */

static uint8 isLeapYear(uint8 year)
 {
	  if (year % 400 == 0) {
	        return TRUE;
	    } else if (year % 100 == 0) {
	        return FALSE;
	    } else if (year % 4 == 0) {
	        return TRUE;
	    }
	    return FALSE;
 }

  // Function to update custom time
static void updateCustomTime(CustomTime *time) {

      time->seconds++;
      if (time->seconds >= 60) {
          time->seconds = 0;
          //g_timer = 0;
          time->minutes++;
          if (time->minutes >= 60) {
              time->minutes = 0;
              time->hours++;
              if (time->hours >= 24) {
                  time->hours = 0;
                  time->dayPassed = TRUE; // Set flag when a day has passed
              }
          }
      }
  }
  // Function to update custom date
  static void updateCustomDate(CustomDate *date, CustomTime *time)
  {
      if (time->dayPassed) {
          time->dayPassed = FALSE; // Reset flag
          date->day++;
          uint8 maxDays = 31; // Default to 31 days

          switch (date->month) {
              case 4: case 6: case 9: case 11:
                  maxDays = 30;
                  break;
              case 2:
                  maxDays = isLeapYear(date->year) ? 29 : 28;
                  break;
          }

          if (date->day > maxDays) {
              date->day = 1;
              date->month++;
              if (date->month > 12) {
                  date->month = 1;
                  date->year++;
              }
          }
      }
}


