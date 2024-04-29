#include "SWITCH.h"
#include "GPIO.h"

extern const switch_cfg_t SWITCHES[_switch_num];
static u8 g_state[_switch_num] ; 

void SWITCH_Init(void){
    gpiopin_t switch_var ;
    gpiomode_t mode = {.mode=gpio_mode_in};
    switch_var.mode_t =&mode;
    switch_var.speed=gpio_speed_high;
    for(u8 idx=0;idx<_switch_num ;idx++ ){
        switch_var.pin=SWITCHES[idx].pin;
        switch_var.port=SWITCHES[idx].port;
        if(SWITCHES[idx].connection == connection_PULL_DOWN){
            switch_var.mode_t->pupd=gpio_pupd_pd;
        }else{
            switch_var.mode_t->pupd=gpio_pupd_pu;
        }
        gpio_initPin(&switch_var);
    }
}

SWITCH_ErrorStatus_t SWITCH_getStatus(u32 switch_id,u8* state){
    SWITCH_ErrorStatus_t SWITCH_ErrorStatus= SWITCH_enumNok;
    if(!state){
        SWITCH_ErrorStatus = SWITCH_NullPtr;
    }
    else if (switch_id >= _switch_num ){
        SWITCH_ErrorStatus= SWITCH_enumNok;
    }
    else{
        SWITCH_ErrorStatus = SWITCH_EOk;
        #ifdef runnable_used
            *state = g_state[switch_id];
        #else
            *state = (SWITCHES[switch_id].connection ^gpio_getPinValue(SWITCHES[switch_id].port,SWITCHES[switch_id].pin));
        #endif
    }
    return SWITCH_ErrorStatus;
}

void switch_runnable_cb(void){
    u8 cur_state;
    static u8 prev_state[_switch_num];
    static u32 counts[_switch_num]={0};
    //SWITCH_getStatus(switch_1,&cur_state);
    for(u8 switch_id=0; switch_id<_switch_num ;switch_id++){
        cur_state=(SWITCHES[switch_id].connection ^gpio_getPinValue(SWITCHES[switch_id].port,SWITCHES[switch_id].pin));
        if(cur_state == prev_state[switch_id]){
            counts[switch_id]++;
        }
        else{
            counts[switch_id]=0;
        }
        if(counts [switch_id]== 5){
            g_state[switch_id] = cur_state;
            counts[switch_id] = 0;
        }
        prev_state[switch_id] = cur_state;
    }
    
}

