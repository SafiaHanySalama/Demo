/******************************************************************************
*
* Module: 
*
* File Name: Task_Switches.c
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

extern uint8 lcdx;
extern uint8 lcdy;

CustomTime currentTime = {10, 56, 0, 0};


CustomDate currentDate = {22, 4, 2024}; // Initial date: January 1, 2024

static uint8 Mode_Flag = MODE_TIMENDATE;
uint8 Edit_flag=0;
static uint8 Y_position= 0;
static uint8 X_position= 0;

/*static*/ extern volatile uint8 running; 

/*static*/ uint8 paused = FALSE;
uint8 UART_RecivedByte = 100 ;
/*static*/ uint8 reset = FALSE ;

uint8 Switch_State[_sw_num]={REALESED,REALESED,REALESED,REALESED,REALESED,REALESED,REALESED} ;
uint8 switchMsg[_sw_num] = {1, 2, 3, 4, 5, 6, 7};
uint8 recievedMsg;

UART_UserReq_t uart_SW_req = {
	.usartID = USART1_IDX,
	.ptr_buffer = &Switch_State[0], //Only for Initialization
	.size = 1,
	.cbf = NULL_PTR
};

UART_UserReq_t uart_recievedMsg = {
	.usartID = USART1_IDX,
	.ptr_buffer = &recievedMsg, 
	.size = 1,
	.cbf = RecieverCallBack
};


/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/


/*
 * Runnable for switches

   - SW_mode -

 	1- Timer
 			I need to check if i want to edit
 			if yes ,
			SW_edit ->
			-- LCD should start blinking
			4 switches ( up down right left )

			SW_okey ->
			done editing


 	2- Stop watch
 	4 switches ( up down right left )
 	 are now
 	( start , end , pause , reset )

 /*
 * step 1: check if the switch is pressed or not
 * step 2: if it's pressed then send char through UART
 */

/*

 SWITCH_State_t SWITCH_Getstatus(uint32 switch_num);
 */


/* typedef enum {
	REALESED,
	BRESSED
}SWITCH_State_t;
 */

void MCU1_SwitchesTx(void)
{
	// Iterate through all the switches
	for (uint8 Switches_Count = 0; Switches_Count < _sw_num ; Switches_Count++)
	{
		// Get the status of the switch
		Switch_State[Switches_Count] = SWITCH_Getstatus(Switches_Count);
	}

	// Check if the Up_Start switch is pressed
	if (Switch_State[Up_Start] == BRESSED)
	{
		// Send the corresponding switch message through UART
		uart_SW_req.ptr_buffer = &switchMsg[Up_Start];
		UART_sendByte(&uart_SW_req);
		Switch_State[Up_Start] = REALESED;
	}
	// Check if the Down_End switch is pressed
	else if (Switch_State[Down_End] == BRESSED)
	{
		// Send the corresponding switch message through UART
		uart_SW_req.ptr_buffer = &switchMsg[Down_End];
		UART_sendByte(&uart_SW_req);
		Switch_State[Down_End] = REALESED;
	}
	// Check if the Right_Pause switch is pressed
	else if (Switch_State[Right_Pause] == BRESSED)
	{
		// Send the corresponding switch message through UART
		uart_SW_req.ptr_buffer = &switchMsg[Right_Pause];
		UART_sendByte(&uart_SW_req);
		Switch_State[Right_Pause] = REALESED;
	}
	// Check if the Left_Reset switch is pressed
	else if (Switch_State[Left_Reset] == BRESSED)
	{
		// Send the corresponding switch message through UART
		uart_SW_req.ptr_buffer = &switchMsg[Left_Reset];
		UART_sendByte(&uart_SW_req);
		Switch_State[Left_Reset] = REALESED;
	}
	// Check if the Edit switch is pressed
	else if (Switch_State[Edit] == BRESSED)
	{
		// Send the corresponding switch message through UART
		uart_SW_req.ptr_buffer = &switchMsg[Edit];
		UART_sendByte(&uart_SW_req);
		Switch_State[Edit] = REALESED;
	}
	// Check if the Mode switch is pressed
	else if (Switch_State[Mode] == BRESSED)
	{
		// Send the corresponding switch message through UART
		uart_SW_req.ptr_buffer = &switchMsg[Mode];
		UART_sendByte(&uart_SW_req);
		Switch_State[Mode] = REALESED;
	}
	// Check if the Okay switch is pressed
	else if (Switch_State[Okay] == BRESSED)
	{
		// Send the corresponding switch message through UART
		uart_SW_req.ptr_buffer = &switchMsg[Okay];
		UART_sendByte(&uart_SW_req);
		Switch_State[Okay] = REALESED;
	}
	else
	{
		// Error Handling
	}
}


/*
 * Runnable for switches signals
 * step 1: check if the UART has sent any chars
 * step 2: if a char is sent , check which switch is pressed
 */

void MCU1_UARTSignalRx(void)
{
	USART_RxBufferAsyncZeroCopy(&uart_recievedMsg);

}

void RecieverCallBack(void){
	

	/**
	 * @todo Uart Recive Byte take req as argument
	*/
	UART_RecivedByte = *(uart_recievedMsg.ptr_buffer);

	if (UART_RecivedByte != 0)
	{
		/***************for testing********/
		UART_sendByte(&uart_recievedMsg);
		/*********************************/
		switch (Mode_Flag)
		{
			case (MODE_TIMENDATE):
				switch (UART_RecivedByte-1)
				{
					case Up_Start:
						if (Edit_flag == 1)
						{
							// LCD_setCursorPosAsync(uint8 posX, uint8 posY);
							if ((X_position == START_X_POSITION) && (Y_position == START_Y_POSITION))
							{
								currentTime.hours += 10;
							}
							else if ((X_position == START_X_POSITION) && (Y_position == START_Y_POSITION + 1))
							{
								currentTime.hours += 1;
							}
							else if ((X_position == START_X_POSITION) && (Y_position == START_Y_POSITION + 3))
							{
								currentTime.minutes += 10;
							}
							else if ((X_position == START_X_POSITION) && (Y_position == START_Y_POSITION + 4))
							{
								currentTime.minutes += 1;
							}
							else if ((X_position == START_X_POSITION) && (Y_position == START_Y_POSITION + 6))
							{
								currentTime.seconds += 10;
							}
							else if ((X_position == START_X_POSITION) && (Y_position == START_Y_POSITION + 7))
							{
								currentTime.seconds += 1;
							}
							/****************************************/
							if ((X_position == START_X_POSITION + 1) && (Y_position == START_Y_POSITION))
							{
								currentDate.day += 10;
							}
							else if ((X_position == START_X_POSITION + 1) && (Y_position == START_Y_POSITION + 1))
							{
								currentDate.day += 1;
							}
							else if ((X_position == START_X_POSITION + 1) && (Y_position == START_Y_POSITION + 3))
							{
								currentDate.month += 10;
							}
							else if ((X_position == START_X_POSITION + 1) && (Y_position == START_Y_POSITION + 4))
							{
								currentDate.month += 1;
							}
							else if ((X_position == START_X_POSITION + 1) && (Y_position == START_Y_POSITION + 6))
							{
								currentDate.year += 1000;
							}
							else if ((X_position == START_X_POSITION + 1) && (Y_position == START_Y_POSITION + 7))
							{
								currentDate.year += 100;
							}
							else if ((X_position == START_X_POSITION + 1) && (Y_position == START_Y_POSITION + 8))
							{
								currentDate.year += 10;
							}
							else if ((X_position == START_X_POSITION + 1) && (Y_position == START_Y_POSITION + 9))
							{
								currentDate.year += 1;
							}
							else
							{

							}

						}

						break;
					case Down_End:
						if (Edit_flag == 1)
						{
							// LCD_setCursorPosAsync(uint8 posX, uint8 posY);
							if ((X_position == START_X_POSITION) && (Y_position == START_Y_POSITION))
							{
								currentTime.hours -= 10;
							}
							else if ((X_position == START_X_POSITION) && (Y_position == START_Y_POSITION + 1))
							{
								currentTime.hours -= 1;
							}
							else if ((X_position == START_X_POSITION) && (Y_position == START_Y_POSITION + 3))
							{
								currentTime.minutes -= 10;
							}
							else if ((X_position == START_X_POSITION) && (Y_position == START_Y_POSITION + 4))
							{
								currentTime.minutes -= 1;
							}
							else if ((X_position == START_X_POSITION) && (Y_position == START_Y_POSITION + 6))
							{
								currentTime.seconds -= 10;
							}
							else if ((X_position == START_X_POSITION) && (Y_position == START_Y_POSITION + 7))
							{
								currentTime.seconds -= 1;
							}
							/****************************************/
							if ((X_position == START_X_POSITION + 1) && (Y_position == START_Y_POSITION))
							{
								currentDate.day -= 10;
							}
							else if ((X_position == START_X_POSITION + 1) && (Y_position == START_Y_POSITION + 1))
							{
								currentDate.day -= 1;
							}
							else if ((X_position == START_X_POSITION + 1) && (Y_position == START_Y_POSITION + 3))
							{
								currentDate.month -= 10;
							}
							else if ((X_position == START_X_POSITION + 1) && (Y_position == START_Y_POSITION + 4))
							{
								currentDate.month -= 1;
							}
							else if ((X_position == START_X_POSITION + 1) && (Y_position == START_Y_POSITION + 6))
							{
								currentDate.year -= 1000;
							}
							else if ((X_position == START_X_POSITION + 1) && (Y_position == START_Y_POSITION + 7))
							{
								currentDate.year -= 100;
							}
							else if ((X_position == START_X_POSITION + 1) && (Y_position == START_Y_POSITION + 8))
							{
								currentDate.year -= 10;
							}
							else if ((X_position == START_X_POSITION + 1) && (Y_position == START_Y_POSITION + 9))
							{
								currentDate.year -= 1;
							}
							else
							{

							}

						}

						break;

					case Right_Pause:
						if (Edit_flag == 1)
						{
							if ((Y_position== MAX_LCD_COL) && (X_position  == 1))
							{
								Y_position = 0;
								X_position = 0;
								LCD_setCursorPosAsync(X_position , Y_position);
							}
							else if ((Y_position >= MAX_LCD_COL) && (X_position == 0))
							{
								X_position = 1;
								Y_position=0;
								LCD_setCursorPosAsync(X_position , Y_position);
							}
							else
							{
								Y_position +=1;
								LCD_setCursorPosAsync(X_position, Y_position);

							}


						}

						break;

					case Left_Reset:
						if (Edit_flag == 1)
						{
							if ((X_position == 0) && (Y_position == 0))
							{
								Y_position = MAX_LCD_COL;
								X_position =1;
								LCD_setCursorPosAsync(X_position , Y_position);
							}
							else if ((Y_position == 0) && (X_position == 1))
							{
								Y_position = MAX_LCD_COL;
								X_position =0;
								LCD_setCursorPosAsync(X_position , Y_position);
							}
							else
							{
								Y_position --;
								LCD_setCursorPosAsync(X_position, Y_position );
							}


						}
						break;

					case Edit:
						Edit_flag = 1;
						/* Blinking LCD */

						break;

					case Mode:
						Mode_Flag = MODE_SW;//~ Mode_Flag;
						LCD_clearScreenAsynch();
						//running =1;

						break;

					case Okay:
						//Y_position = 0;
						//X_position = 0;
						LCD_setCursorPosAsync(X_position , Y_position);
						Edit_flag = 0;
						/* Not Blinking LCD */
						
						break;
					default :

						break;


				}


				break;
			case (MODE_SW):
				switch (UART_RecivedByte-1)
				{
					case Up_Start:
						running = TRUE ;
						break;
					case Down_End:
						running = FALSE;
						break;

					case Right_Pause:
						paused ^= TRUE;

						break;

					case Left_Reset:
						reset = TRUE ;

						break;

					case Mode:
						Mode_Flag = MODE_TIMENDATE;//~Mode_Flag;
						running = FALSE;
						LCD_clearScreenAsynch();
						break;

					default :

						break;


				}


				break;
		}

	}
}
