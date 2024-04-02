/******************************************************************************
*
* Module: 
*
* File Name: lcd.c
*

* Description: 
*
* Author: Safia Hany
* 
* Date:  1/4/2024
******************************************************************************/

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/

#include "hal/lcd.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

#define LCD_NUM_DATA_PINS       LCD_BIT_MODE 
#define LCD_TOTAL_PINS          (LCD_BIT_MODE + 3)
#define MAX_NUM_REQ             3

#define CURSOR_HOME_LINE               0
#define CURSOR_HOME_COL                0

#define LCD_CURSOR_ON                  1
#define LCD_CLEAR_COMMAND              0
#define LCD_SHIFT_RIGHT_CRUSOR         0

#define ENABLE_PIN_LOW                  0
#define ENABLE_PIN_HIGH                 1
/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/
typedef enum{
    USER_STATE_BUSY,
    USER_STATE_READY
}Userstate_t;

typedef enum{
    WRITE_REQ,
    CLEAR_REQ,
    SET_POS_REQ
}CommandType_t;

typedef enum{
    POWER_ON_MODE,
    FUNC_SET_MODE,
    DISPLAY_MODE,
    ENTRY_MODE,
    CLEAR_MODE,
    END_MODE
}LCD_Mode_t;

typedef enum{
    LCD_OFF,
    LCD_INIT,
    LCD_OPERATIONAL
}LCD_State_t;

typedef void (*CB_fn_t)(void);
typedef struct
{
    uint8 linePos;
    uint8 colPos;
}CursorPose_t;

typedef struct 
{
    const uint8 * name;
    uint8 len;
    CommandType_t type;
    Userstate_t state;
    CursorPose_t currentPose;
}User_Request_t;





/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/

extern const LCD_Conn_t LCD_Config;
User_Request_t User_Req[MAX_NUM_REQ];
uint8 g_useCurr_req = 0;
static LCD_Mode_t g_LCD_initMode = POWER_ON_MODE;
static LCD_State_t g_LCD_State = LCD_OFF;
static uint8 g_LCD_enablePin = ENABLE_PIN_LOW;

/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/

static void LCD_initSM();
static void LCD_writeProcess();
static void LCD_clearProcess();
static void LCD_setPose_Process();


/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/

void LCD_Init(void)
{
    //Configure LCD Pins
    GPIO_ConfigPin_t LCD_Pin;
    LCD_Pin.Mode = GPIO_MODE_OUT_PP;
    LCD_Pin.Speed = GPIO_MEDUIM_SPEED;
    //Configure Data Pins as Output
    for (uint8 idx ; idx < LCD_NUM_DATA_PINS; idx++)
    {
        LCD_Pin.Port = LCD_Config.Data_Pins[idx].port;
        LCD_Pin.Pin = LCD_Config.Data_Pins[idx].pin;
        GPIO_init(&LCD_Pin);
    }
    //Configure RS Pin
    LCD_Pin.Port = LCD_Config.RS_Pin.port;
    LCD_Pin.Pin = LCD_Config.RS_Pin.pin;
    GPIO_init(&LCD_Pin);
    //Configure RW Pin
    LCD_Pin.Port = LCD_Config.RW_Pin.port;
    LCD_Pin.Pin = LCD_Config.RW_Pin.pin;
    GPIO_init(&LCD_Pin);
    //Configure E Pin
    LCD_Pin.Port = LCD_Config.E_Pin.port;
    LCD_Pin.Pin = LCD_Config.E_Pin.pin;
    GPIO_init(&LCD_Pin);
    //Assign the cursor position to 1st pos
    User_Req[g_useCurr_req].currentPose.linePos = CURSOR_HOME_LINE;
    User_Req[g_useCurr_req].currentPose.colPos =CURSOR_HOME_COL;

}

void LCD_Runnable()
{
    if (g_LCD_State == LCD_INIT)
    {
        LCD_initSM();
    }
    else if (g_LCD_State == LCD_OPERATIONAL)
    {
        if (User_Req[g_useCurr_req].state = USER_STATE_BUSY)
        {
            switch (User_Req[g_useCurr_req].type)
            {
            case WRITE_REQ:
                LCD_writeProcess();
                break;
            case CLEAR_REQ:
                LCD_clearProcess();
                break;  
            case SET_POS_REQ:
                LCD_clearProcess();
                break;                         
            default:
                break;
            }
        }
    }
    else{
        //DO NOTHING if LCD_OFF
    }
}
static void LCD_initSM()
{
    switch (g_LCD_initMode)
    {
    case POWER_ON_MODE:
        LCD_Init();
        g_LCD_initMode = FUNC_SET_MODE;
        break;
    
    case FUNC_SET_MODE:
        LCD_WriteCommand(LCD_BIT_MODE);
        //Check that the configuration is completed 
        if (g_LCD_enablePin = ENABLE_PIN_LOW) g_LCD_initMode = DISPLAY_MODE;
        break;
    case DISPLAY_MODE:
        LCD_WriteCommand(LCD_CURSOR_ON);
        if (g_LCD_enablePin = ENABLE_PIN_LOW) g_LCD_initMode = CLEAR_MODE;
    case CLEAR_MODE:
        LCD_WriteCommand(LCD_CLEAR_COMMAND);
        if (g_LCD_enablePin = ENABLE_PIN_LOW) g_LCD_initMode = ENTRY_MODE;
        break;
    case ENTRY_MODE:
        LCD_WriteCommand(LCD_SHIFT_RIGHT_CRUSOR);
        g_LCD_initMode = END_MODE;
        break;  
    case END_MODE:
        //Configuration Done, LCD can handle the req.
        User_Req[g_useCurr_req].state = USER_STATE_READY;
        g_LCD_State = LCD_OPERATIONAL;
        break;
              
    default:
        break;
    }
}



void LCD_writeStringAsync(uint8* string,uint8 length){

    for(uint8 idx; idx< MAX_NUM_REQ;idx++)
    {
        if (User_Req[idx].state== USER_STATE_READY )
        {
            User_Req[idx].state= USER_STATE_BUSY ;
            User_Req[idx].name = string;
            User_Req[idx].len = length;
            User_Req[idx].type = WRITE_REQ;
        }
    }


}

static void LCD_WriteCommand(uint8 command)
{
    if (g_LCD_enablePin == ENABLE_PIN_LOW)
    {
        GPIO_setPinValue(LCD_Config.RW_Pin.port,LCD_Config.RW_Pin.pin,GPIO_RESET_PIN);
        GPIO_setPinValue(LCD_Config.RS_Pin.port,LCD_Config.RS_Pin.pin,GPIO_RESET_PIN);
        //for loop
        GPIO_setPinValue(LCD_Config.RW_Pin.port,LCD_Config.RW_Pin.pin,GPIO_SET_PIN);
    }

}
void LCD_setCursorPosAsync(uint8 posX, uint8 posY){

}

void LCD_clearScreenAsynch(void){

}

uint8 LCD_getStatus(void){

}



static void LCD_writeProcess(){

}
static void LCD_clearProcess(){

}
static void LCD_setPose_Process(){

}
