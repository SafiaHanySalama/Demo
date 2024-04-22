/******************************************************************************
 *
 * Module: 
 *
 * File Name: systick.c
 *
 * Description: 
 *
 * Author: Safia Hany
 * 
 * Date:  Mar 23, 2024
 ******************************************************************************/

#include "mcal/systick.h"
#include "mcal/systick_cfg.h"
#include "Std_Types.h"

#define SYSTICK_BASE_ADDRESS		0xE000E010

/* SysTick Control / Status Register Definitions */
#define SysTick_CTRL_COUNTFLAG_Pos         16                                             /*!< SysTick CTRL: COUNTFLAG Position */
#define SysTick_CTRL_COUNTFLAG_Msk         (1UL << SysTick_CTRL_COUNTFLAG_Pos)            /*!< SysTick CTRL: COUNTFLAG Mask */

#define SysTick_CTRL_CLKSOURCE_Pos          2                                             /*!< SysTick CTRL: CLKSOURCE Position */
#define SysTick_CTRL_CLKSOURCE_Msk         (1UL << SysTick_CTRL_CLKSOURCE_Pos)            /*!< SysTick CTRL: CLKSOURCE Mask */

#define SysTick_CTRL_TICKINT_Pos            1                                             /*!< SysTick CTRL: TICKINT Position */
#define SysTick_CTRL_TICKINT_Msk           (1UL << SysTick_CTRL_TICKINT_Pos)              /*!< SysTick CTRL: TICKINT Mask */

#define SysTick_CTRL_ENABLE_Pos             0                                             /*!< SysTick CTRL: ENABLE Position */
#define SysTick_CTRL_ENABLE_Msk            (1UL << SysTick_CTRL_ENABLE_Pos)               /*!< SysTick CTRL: ENABLE Mask */


typedef struct
{
	uint32 CTRL;                    /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
	uint32 LOAD;                    /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register       */
	uint32 VAL;                     /*!< Offset: 0x008 (R/W)  SysTick Current Value Register      */
	uint32 CALIB;                   /*!< Offset: 0x00C (R/ )  SysTick Calibration Register        */
} SysTick_Peri_t;

volatile SysTick_Peri_t *const Systick = (volatile SysTick_Peri_t *)SYSTICK_BASE_ADDRESS;

static systick_cbf_t APP_cbf= NULL_PTR;
uint8 systick_mode = SYSTICK_MODE;

void SYSTICK_Init(uint8 mode)
{
	systick_mode = mode;
	/*Reset reload value*/
	Systick->VAL   = 0;
	/*select system clock
	 * enable interrupt
	 * enable systick timer*/
	Systick -> CTRL |= SysTick_CTRL_TICKINT_Msk ;
	Systick -> CTRL |=SysTick_CTRL_ENABLE_Msk;

}
void SYSTICK_set_ms(uint32 time){

	/*reload_val = system clock * delay per ms*/
	uint32 sysClk = ((Systick -> CTRL) & SysTick_CTRL_CLKSOURCE_Msk)?SystemClock: SystemClock/8;
	//convert sysclk to ms
	uint32 reload_val = ((sysClk/1000) * time - 1);
	Systick->LOAD   = reload_val;
	Systick->VAL   = 0;
}
void SYSTICK_stop()
{
	uint32 systick_temp = Systick -> CTRL;
	systick_temp &= ~(SysTick_CTRL_ENABLE_Msk);
	 Systick -> CTRL = systick_temp;

}
void SYSTICK_setCallBack(systick_cbf_t cbf)
{
	if(cbf != NULL_PTR)
	{
		APP_cbf = cbf;
	}
}
void SysTick_Handler(void)
{
    if (APP_cbf)
	{
        if (systick_mode == ONESHOOT)
        {
        	Systick -> CTRL &= ~SysTick_CTRL_ENABLE_Msk;
        }
        APP_cbf();
	}
}
