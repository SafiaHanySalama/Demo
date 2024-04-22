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
#include <stdio.h>

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

#define LCD_NUM_DATA_PINS       8 
#define LCD_TOTAL_PINS          (LCD_NUM_DATA_PINS + 3)

#define CURSOR_HOME_LINE               0
#define CURSOR_HOME_COL                0

#define LCD_CURSOR_ON                  0x0E
#define LCD_CURSOR_OFF                 0x0C
#define LCD_CLEAR_COMMAND              0x01
#define LCD_SHIFT_RIGHT_CRUSOR         0x06

#define ENABLE_PIN_LOW                  0
#define ENABLE_PIN_HIGH                 1

#define LCD_LINE0                       0
#define LCD_LINE1                       1
#define LCD_LINE2                       2
#define LCD_LINE3                       3
/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/


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

typedef struct
{
    uint8 linePos;
    uint8 colPos;
}CursorPose_t;

typedef enum{
    USER_STATE_BUSY,
    USER_STATE_READY
}Userstate_t;

typedef enum{
    NO_REQ,
    WRITE_REQ,
    CLEAR_REQ,
    SET_POS_REQ,
    NUM_REQ
}CommandType_t;

typedef struct 
{
    const uint8 * name;
    uint8 len;
    CommandType_t type;
    Userstate_t state;
    CursorPose_t currentPose;
}User_Request_t;


typedef void (*CB_fn_t)(void);




/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/

extern const LCD_Conn_t LCD_Config;
User_Request_t User_Req;
uint8 g_useCurr_req = 0;
CursorPose_t g_currPos;
static LCD_Mode_t g_LCD_initMode = POWER_ON_MODE;
static LCD_State_t g_LCD_State = LCD_OFF;
static uint8 g_LCD_enablePin = ENABLE_PIN_LOW;
/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/

static void LCD_Init(void);
static void LCD_initSM();
static void LCD_writeProcess();
static void LCD_clearProcess();
static void LCD_setPose_Process();
static void LCD_WriteCommand(uint8 command);
static void LCD_writeNumber_Process(); 


/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/

static void LCD_Init(void)
{
    User_Req.state = USER_STATE_BUSY;
    //Configure LCD Pins
    GPIO_ConfigPin_t LCD_Pin;
    LCD_Pin.Mode = GPIO_MODE_OUT_PP;
    LCD_Pin.Speed = GPIO_MEDUIM_SPEED;
    //Configure Data Pins as Output
    for (uint8 idx=0 ; idx < LCD_NUM_DATA_PINS; idx++)
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
    User_Req.currentPose.linePos = CURSOR_HOME_LINE;
    User_Req.currentPose.colPos =CURSOR_HOME_COL;

}

void LCD_Runnable()
{
    if (g_LCD_State == LCD_INIT)
    {
        LCD_initSM();
    }
    else if (g_LCD_State == LCD_OPERATIONAL)
    {
        if (User_Req.state == USER_STATE_BUSY)
        {
            switch (User_Req.type)
            {
            case WRITE_REQ:
                LCD_writeProcess();
                break;
            case CLEAR_REQ:
                LCD_clearProcess();
                break;  
            case SET_POS_REQ:
                LCD_setPose_Process();
                break;  
            case NUM_REQ:
                LCD_writeNumber_Process();                       
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
        if (g_LCD_enablePin == ENABLE_PIN_LOW) g_LCD_initMode = DISPLAY_MODE;
        break;
    case DISPLAY_MODE:
        LCD_WriteCommand(LCD_CURSOR_ON);
        if (g_LCD_enablePin == ENABLE_PIN_LOW) g_LCD_initMode = CLEAR_MODE;
    case CLEAR_MODE:
        LCD_WriteCommand(LCD_CLEAR_COMMAND);
        if (g_LCD_enablePin == ENABLE_PIN_LOW) g_LCD_initMode = ENTRY_MODE;
        break;
    /* FIXME */
    case ENTRY_MODE:
        LCD_WriteCommand(LCD_SHIFT_RIGHT_CRUSOR);
        if (g_LCD_enablePin == ENABLE_PIN_LOW) g_LCD_initMode = END_MODE;
        break;  
    case END_MODE:
        //Configuration Done, LCD can handle the req.
        User_Req.state = USER_STATE_READY;
        g_LCD_State = LCD_OPERATIONAL;
        break;          
    default:
        break;
    }
}


static void LCD_WriteCommand(uint8 command)
{
    uint8 idx;
    uint8 pinValue;
    if (g_LCD_enablePin == ENABLE_PIN_LOW)
    {
        GPIO_setPinValue(LCD_Config.RW_Pin.port,LCD_Config.RW_Pin.pin,LOGIC_LOW);
        GPIO_setPinValue(LCD_Config.RS_Pin.port,LCD_Config.RS_Pin.pin,LOGIC_LOW);
        GPIO_setPinValue(LCD_Config.E_Pin.port,LCD_Config.E_Pin.pin,LOGIC_HIGH);
        //for loop
        for (idx = 0; idx < LCD_NUM_DATA_PINS ;idx++)
        {
            //Get the value of each bit
            pinValue = ((command >> idx) & 1) ;
            GPIO_setPinValue(LCD_Config.Data_Pins[idx].port,LCD_Config.Data_Pins[idx].pin,pinValue);
        }
        GPIO_setPinValue(LCD_Config.E_Pin.port,LCD_Config.E_Pin.pin,LOGIC_LOW);
    }
    else 
    {
        GPIO_setPinValue(LCD_Config.E_Pin.port,LCD_Config.E_Pin.pin,LOGIC_LOW);
    }
}

/**
 * @brief Writes data to the LCD.
 *
 * This function writes the given data to the LCD module. It sets the appropriate control signals
 * and data pins to send the data to the LCD.
 *
 * @param data The data to be written to the LCD.
 */
static void LCD_WriteData(uint8 data)
{
    uint8 idx;
    uint8 pinValue;
    if (g_LCD_enablePin == ENABLE_PIN_LOW)
    {
    GPIO_setPinValue(LCD_Config.RW_Pin.port,LCD_Config.RW_Pin.pin,LOGIC_LOW);
    GPIO_setPinValue(LCD_Config.RS_Pin.port,LCD_Config.RS_Pin.pin,LOGIC_HIGH);
    GPIO_setPinValue(LCD_Config.E_Pin.port,LCD_Config.E_Pin.pin,LOGIC_HIGH);
    //for loop
    for (idx = 0; idx < LCD_NUM_DATA_PINS ;idx++)
    {
        //Get the value of each bit
        pinValue = (data & (1 << idx)) ;
        GPIO_setPinValue(LCD_Config.Data_Pins[idx].port,LCD_Config.Data_Pins[idx].pin,pinValue);
    }
    GPIO_setPinValue(LCD_Config.E_Pin.port,LCD_Config.E_Pin.pin,LOGIC_LOW);
    }
}
void LCD_initAsync()
{
    g_LCD_State = LCD_INIT;
}
void LCD_writeStringAsync(const uint8* string,uint8 length){

    if (User_Req.state== USER_STATE_READY && g_LCD_State == LCD_OPERATIONAL)
    {
        User_Req.state= USER_STATE_BUSY ;
        User_Req.name = string;
        User_Req.len = length;
        User_Req.type = WRITE_REQ;
    }
}
void LCD_writeNumberAsync(uint32 Number)
{
    static char NumbersBuffer[16] = "";
    //uint8 counter = 0;
    volatile uint8 idx;

    if (User_Req.state== USER_STATE_READY && g_LCD_State == LCD_OPERATIONAL)
    {
        User_Req.state= USER_STATE_BUSY ;
        User_Req.type = NUM_REQ;
        sprintf((char*)NumbersBuffer, "%u", Number); 
        for(idx = 0; NumbersBuffer[idx] != '\0'; idx++);
        User_Req.len = idx;  
        User_Req.name = (const uint8*)NumbersBuffer;
    }

}
void LCD_setCursorPosAsync(uint8 posX, uint8 posY){

    if ((User_Req.state == USER_STATE_READY) && (g_LCD_State == LCD_OPERATIONAL))
    {
        User_Req.state = USER_STATE_BUSY ;
        User_Req.type = SET_POS_REQ;
        User_Req.currentPose.linePos = posX;
        User_Req.currentPose.colPos = posY;
    }
}

void LCD_clearScreenAsynch(void){
        if (User_Req.state== USER_STATE_READY )
    {
        User_Req.state= USER_STATE_BUSY ;
        User_Req.type = CLEAR_REQ;
    }  
}

uint8 LCD_getStatus(void){
    return g_LCD_State;
}

static void LCD_writeProcess(){

    //curr = 2 length 1 sum = 3 
    //
    static uint8 firsttime = 0;
    if (firsttime == 0)
    {
        g_currPos.colPos = 0;
        firsttime = 1;
    }
    else 
    {
        if (g_currPos.colPos != User_Req.len)
        {
            LCD_WriteData(User_Req.name[g_currPos.colPos]);
            g_currPos.colPos++;
            User_Req.currentPose.colPos++;
        }
        else
        {
            User_Req.state = USER_STATE_READY;
            User_Req.type = NO_REQ;
            firsttime = 0;
        }
    }
 
}
void LCD_writeNumber_Process()
{
    static uint8 firsttime = 0;
    if (firsttime == 0)
    {
        g_currPos.colPos = 0;
        firsttime = 1;
    }
    else 
    {
        if (g_currPos.colPos != User_Req.len)
        {
            LCD_WriteData(User_Req.name[g_currPos.colPos]);
            g_currPos.colPos++;
            User_Req.currentPose.colPos++;
        }
        else
        {
            User_Req.state = USER_STATE_READY;
            User_Req.type = NO_REQ;
            firsttime = 0;
        }
    } 
}
static void LCD_clearProcess(){
    LCD_WriteCommand(LCD_CLEAR_COMMAND);
    if (g_LCD_enablePin == ENABLE_PIN_LOW)
    {
        User_Req.state = USER_STATE_READY;
        User_Req.type = NO_REQ;
    }
}
static void LCD_setPose_Process(){
    uint8 lcd_memory_address = 0;

    switch (User_Req.currentPose.linePos)
    {
    case LCD_LINE0:
        lcd_memory_address = User_Req.currentPose.colPos;
        break;  
    case LCD_LINE1:
        lcd_memory_address =  User_Req.currentPose.colPos + 0x40;
        break;
    case LCD_LINE2:
        lcd_memory_address =  User_Req.currentPose.colPos + 0x10;
        break;
    case LCD_LINE3:
        lcd_memory_address =  User_Req.currentPose.colPos + 0x50;
        break;
    default:
        break;
    }
    LCD_WriteCommand(lcd_memory_address + LCD_SET_CURSOR_LOCATION);
    if (g_LCD_enablePin == ENABLE_PIN_LOW)
    {
        User_Req.state = USER_STATE_READY;
        User_Req.type = NO_REQ;
    }
}

#define LCD_DISPLAYCONTROL 0x08
#define LCD_BLINKON 0x01

void LCD_blinkOn() {
    LCD_WriteCommand(LCD_DISPLAYCONTROL | LCD_BLINKON);
}

void LCD_blinkOff() {
    LCD_WriteCommand(LCD_DISPLAYCONTROL & ~LCD_BLINKON);
}