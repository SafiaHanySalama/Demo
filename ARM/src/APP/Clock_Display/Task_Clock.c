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
extern uint8 Edit_flag;
extern volatile uint8 running;
/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/


 void updateCustomTime(CustomTime *time);
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
 
    static uint8 count= 0;
    const uint8* Timebreak = ":";
    const uint8* Daybreak = "/";
    const uint32 zero = 0;
    static uint8 Firstflag = 0;
    if(Edit_flag==1 /*|| running ==1*/){
        // do nothing
        count=0;
    }
    else{
    if (Firstflag == 0)
    {
        LCD_clearScreenAsynch();
        Firstflag = 1;
    }
    else if(Firstflag == 1 && running == FALSE)
    {
        count++;
        if (count == 1)
        {
            LCD_setCursorPosAsync(START_X_POSITION, START_Y_POSITION);
        }
        else if (count == 2)
        {
            updateCustomTime(&currentTime);
            if (currentTime.hours<10)
            {
                LCD_writeNumberAsync(zero);
            }   
        }
        else if (count == 3)
        {
            LCD_writeNumberAsync(currentTime.hours);
        }
        else if (count == 4)
        {
            LCD_writeStringAsync(Timebreak,1);
        }
        else if (count == 5)
        {
            if (currentTime.minutes<10)
            {
                LCD_writeNumberAsync(zero);
            }
        }
        else if (count == 6)
        {
            LCD_writeNumberAsync(currentTime.minutes);
        }
        else if (count == 7)
        {
            LCD_writeStringAsync(Timebreak,1);
        }
        else if (count == 8)
        {
            if (currentTime.seconds<10)
            {
                LCD_writeNumberAsync(zero);
            }
        }
        else if (count == 9)
        {
            LCD_writeNumberAsync(currentTime.seconds);
        }
        else if (count == 10)
        {
            LCD_setCursorPosAsync(START_X_POSITION+1,START_Y_POSITION);
        }
        else if (count == 11)
        {
            updateCustomDate(&currentDate, &currentTime); // Pass both time and date structures
            if (currentDate.day<10)
            {
                LCD_writeNumberAsync(zero);
            }

        }
        else if (count == 12)
        {
            LCD_writeNumberAsync(currentDate.day);
        }
        else if (count == 13)
        {
            LCD_writeStringAsync(Daybreak,1);
        }
        else if (count == 14)
        {
            if (currentDate.month<10)
            {
                LCD_writeNumberAsync(zero);
            }
        }
        else if (count == 15)
        {
            LCD_writeNumberAsync(currentDate.month);
        }
        else if (count == 16)
        {
            LCD_writeStringAsync(Daybreak,1);
        }
        else if (count == 17)
        {
            if (currentDate.year<10)
            {
                LCD_writeNumberAsync(zero);
            }

        }
        else if (count == 18)
        {
            LCD_writeNumberAsync(currentDate.year);
            count =0;
        }
    }
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
void updateCustomTime(CustomTime *time) {

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


