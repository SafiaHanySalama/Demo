#include "SCHED.h"
#include "SYSTICK.h"

extern u8 tickMs;
extern const runnable_t runnables[_runnable_Max];
runnableInfo_t rInfo[_runnable_Max];
u32 pendingTicks = 0;

static void SCHED(void){
    u32 idx;
    for(idx=0 ;idx <_runnable_Max ;idx++){
        if(rInfo[idx].r->cb &&(rInfo[idx].remainingTimeMs == 0)){
            rInfo[idx].r->cb();
            rInfo[idx].remainingTimeMs = rInfo[idx].r->periodicityMs;
        }
        rInfo[idx].remainingTimeMs -= tickMs;
    }
}

static void tickCBF(void){
    pendingTicks++;
}

SCHED_Error_t SCHED_registerRunnable(runnable_t* runnable){
    SCHED_Error_t Ret_ErrorStatus = SCHED_enum_Nok;
    if(runnable && rInfo[runnable->priority].r == NULL){
        Ret_ErrorStatus = SCHED_enum_Ok;
        rInfo[runnable->priority].r = runnable;
        if(runnable->delay > 0){
            rInfo[runnable->priority].remainingTimeMs = runnable->delay;
        }else{
            rInfo[runnable->priority].remainingTimeMs = runnable->periodicityMs;
        }   
    }
    return Ret_ErrorStatus;
}

void SCHED_init(void){
    //init var
    for(u8 i=0;i<_runnable_Max;i++){
        SCHED_registerRunnable((runnable_t*)&runnables[i]);
    }
    SYSTICK_setTimeMS(tickMs);
    SYSTICK_setCallBackFunction(tickCBF);
    SCHED_start();
}

void SCHED_start(void){
    SYSTICK_start(mode_Periodic);
    while (1)
    {
        if(pendingTicks > 0){
            pendingTicks--;
            SCHED();
        }
    }
}


