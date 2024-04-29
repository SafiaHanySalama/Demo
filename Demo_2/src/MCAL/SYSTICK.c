#include "SYSTICK.h"

#define Systick_enableMask 1
#define Systick_disableMask 0
#define empty_value 0
#define timeOfTenMilliSecondMask 0xffffff
#define SYSTICK_pendingBit 25
#define SYSTICK_enableTickInterruptMask 0x2
#define SYSTICK_CoreClkSourceMask 0x4


typedef struct{
    u32 CTRL;
    u32 LOAD;
    u32 VAL;
    u32 CALIB;
}SYSTICK_reg_t;

static SYSTICK_CBF_t AppCB;
volatile SYSTICK_reg_t * const SYSTICK = (SYSTICK_reg_t *)0xE000E010;
volatile u32 * const SCB_ICSR =(u32 * const)0xE000ED04;
static u8 Mode ;
static u8 systickFired ;
static u32 time_ms =0;
static u32 timeWhenCallBack;

void SYSTICK_start(u8 mode){
    SYSTICK->VAL=empty_value;
    Mode =mode;
    SYSTICK->CTRL=(Systick_enableMask | SYSTICK_enableTickInterruptMask | SYSTICK_CoreClkSourceMask);
}

void SYSTICK_stop(void){
    SYSTICK->CTRL=Systick_disableMask;
}

SYSTICK_Error_Status_t SYSTICK_setTimeMS(u32 timeMs){
    SYSTICK_Error_Status_t Ret_errorStatus = SYSTICK_enum_NOk;
    if(timeMs > 0xffffff){
        Ret_errorStatus =  SYSTICK_enum_invalidTickValue;
    }else{
        Ret_errorStatus = SYSTICK_enum_OK;
        timeWhenCallBack = timeMs;
        u32 tickCountForOneMs = ((SYSTICK->CALIB) & timeOfTenMilliSecondMask)/10;
        SYSTICK->LOAD=(timeMs*tickCountForOneMs)-1 ;
    }
    return Ret_errorStatus;
}

void SYSTICK_setCallBackFunction(SYSTICK_CBF_t cbf){
    if(cbf){
        AppCB= cbf;
    }
}

void SysTick_Handler(void){
    if(Mode == mode_OneShot && systickFired==0){
        SYSTICK->CTRL = Systick_disableMask;
        *SCB_ICSR |= SYSTICK_pendingBit;
        systickFired++;
    }
    else{
        systickFired++;
        time_ms++;
        if(time_ms == timeWhenCallBack){
            time_ms =0;
            if(AppCB){
                AppCB();
            }
        }
    }

}
