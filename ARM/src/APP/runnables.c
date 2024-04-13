/******************************************************************************
*
* Module: 
*
* File Name: runnable.c
*

* Description: 
*
* Author: Safia Hany
* 
* Date: 29/3/2024
******************************************************************************/


/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/

#include "app/runnables.h"


/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/
#define LED_GREEN   0
#define LED_RED     1
#define LED_YELLOW  2
#define GREEN_PERIOD_MS         9000
#define RED_PERIOD_MS           20000
#define YELLOW_PERIOD_MS        7000
#define TASK_PERIODICITY_MS     100


/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/

void Runnable_LED_Toggle()
{
   // led_toggle(led_red);
}

void Runnable_LED_SW(void)
{
    SWITCH_State_t sw_state;
    sw_state = SWITCH_Getstatus(SWITCH1);
    if (sw_state == BRESSED)
    {
        //led_setState(led_green,led_state_on);
    }
    else {
        //led_setState(led_green,led_state_off);
    }
}
void Runnable_LED_StateMachine(void)
{
    static uint8 light_state = LED_RED;
    volatile uint8 prev_light_state;
    static uint32 counter = 0;
    counter += TASK_PERIODICITY_MS;
    switch (light_state)
    {
    case LED_RED:
        led_setState(led_red,led_state_on);
        led_setState(led_green,led_state_off);
        led_setState(led_yellow,led_state_off);
        if(counter % RED_PERIOD_MS == 0)
        {
            light_state = LED_YELLOW;
            prev_light_state = LED_RED;
        }
        break; 
    case LED_YELLOW:
        led_setState(led_red,led_state_off);
        led_setState(led_green,led_state_off);
        led_setState(led_yellow,led_state_on);
        if(counter %YELLOW_PERIOD_MS == 0)
        {
            if (prev_light_state == LED_RED) light_state = LED_GREEN;
            else light_state = LED_RED;
            prev_light_state = LED_YELLOW;
        }
        break;
    case LED_GREEN:
        led_setState(led_red,led_state_off);
        led_setState(led_green,led_state_on);
        led_setState(led_yellow,led_state_off);
        if(counter%GREEN_PERIOD_MS==0)
        {
            light_state = LED_YELLOW;
            prev_light_state = LED_GREEN;
        }
        break;
    
    default:
        break;
    }
    //if (counter == (YELLOW_PERIOD_MS+RED_PERIOD_MS+GREEN_PERIOD_MS)) counter = 0;
}
void LCD_Test()
{
    static uint32 counts=0;
    counts++;
    if (counts == 1)
    {
        LCD_writeStringAsync("Eid Mobark",10);
    }
    else if (counts == 5)
    {
        LCD_clearScreenAsynch();
    }
}