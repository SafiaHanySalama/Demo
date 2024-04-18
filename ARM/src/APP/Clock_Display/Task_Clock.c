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
/************************************************Defines*************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/

extern CustomTime currentTime;
extern CustomDate currentDate;

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

	 uint8 Buffer1[SIZE_BUFFER1];
	 uint8 Buffer2[SIZE_BUFFER2];

    updateCustomTime(&currentTime);

    updateCustomDate(&currentDate, &currentTime); // Pass both time and date structures

    sprintf(Buffer1,"%02d:%02d:%02d\n", currentTime.hours, currentTime.minutes, currentTime.seconds);
    sprintf(Buffer2,"%02d/%02d/%d\n", currentDate.day, currentDate.month, currentDate.year);

	LCD_setCursorPosAsync(START_X_POSITION, START_Y_POSITION);

    LCD_writeStringAsync(&Buffer1,SIZE_BUFFER1);

    LCD_setCursorPosAsync(START_X_POSITION+1,START_Y_POSITION);

    LCD_writeStringAsync(&Buffer2,SIZE_BUFFER2);
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
      if (time->seconds > 60) {
          time->seconds = 0;
          time->minutes++;
          if (time->minutes > 60) {
              time->minutes = 0;
              time->hours++;
              if (time->hours > 24) {
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


