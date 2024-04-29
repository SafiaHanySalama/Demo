#include "NVIC.h"

#define _NVIC_PRIO_BITS 3
typedef struct{
    u32     ISER[8];
    u32     _res[24];
    u32     ICER[8];
    u32     __res[24];
    u32     ISPR[8];
    u32     ___res[24];
    u32     ICPR[8];
    u32     ____res[24];
    u32     IABR[8];
    u32     _____res[56];
    u8      IP[240];
    u32     ______res[644];
    u32     STIR;
}NVIC_t;

volatile NVIC_t * const NVIC = (NVIC_t *)(0xE000E100);

Error_status_t NVIC_enableIRQ(u8 IRQn){
    Error_status_t Ret_errorStatus=enum_NOK ;
    if((IRQn < 0 || IRQn >81)&&(IRQn !=84)){
        Ret_errorStatus = enum_invalidIRQn;
    }else{
        Ret_errorStatus = enum_OK;
        NVIC->ISER[(u32)IRQn>>5]=(u32)(1<<((u32)IRQn&(u32)0x1f));
    }
    return Ret_errorStatus;
}

Error_status_t NVIC_disableIRQ(u8 IRQn){
    Error_status_t Ret_errorStatus=enum_NOK ;
    if((IRQn < 0 || IRQn >81)&&(IRQn !=84)){
        Ret_errorStatus = enum_invalidIRQn;
    }else{
        Ret_errorStatus = enum_OK;
        NVIC->ICER[(u32)IRQn>>5]=(u32)(1<<((u32)IRQn&(u32)0x1f));
    }
    return Ret_errorStatus;
}

Error_status_t NVIC_setPendingIRQ(u8 IRQn){
    Error_status_t Ret_errorStatus=enum_NOK ;
    if((IRQn < 0 || IRQn >81)&&(IRQn !=84)){
        Ret_errorStatus = enum_invalidIRQn;
    }else{
        Ret_errorStatus = enum_OK;
        NVIC->ISPR[(u32)IRQn>>5]=(u32)(1<<((u32)IRQn&(u32)0x1f));
    }
    return Ret_errorStatus;
}

Error_status_t NVIC_clearPendingIRQ(u8 IRQn){
    Error_status_t Ret_errorStatus=enum_NOK ;
    if((IRQn < 0 || IRQn >81)&&(IRQn !=84)){
        Ret_errorStatus = enum_invalidIRQn;
    }else{
        Ret_errorStatus = enum_OK;
        NVIC->ICPR[(u32)IRQn>>5]=(u32)(1<<((u32)IRQn&(u32)0x1f));
    }
    return Ret_errorStatus;
}

Error_status_t NVIC_getPendingIRQ(u8 IRQn,u32* value){
    Error_status_t Ret_errorStatus=enum_NOK ;
    if((IRQn < 0 || IRQn >81)&&(IRQn !=84)){
        Ret_errorStatus = enum_invalidIRQn;
    }else if(value == NULL){
        Ret_errorStatus = enum_nullPointer;
    }
    else{
        Ret_errorStatus = enum_OK;
        *value= (u32)((NVIC->ISPR[(u32)IRQn>>5]&(u32)( 1<< ((u32)IRQn & 0x1f)))?1:0);
    }
    return Ret_errorStatus;
}

Error_status_t NVIC_getActiveStatus(u8 IRQn,u32* status){
    Error_status_t Ret_errorStatus=enum_NOK ;
    if((IRQn < 0 || IRQn >81)&&(IRQn !=84)){
        Ret_errorStatus = enum_invalidIRQn;
    }else if(status == NULL){
        Ret_errorStatus = enum_nullPointer;
    }
    else{
        Ret_errorStatus = enum_OK;
        *status= (u32)((NVIC->IABR[(u32)IRQn>>5]&(u32)( 1<< ((u32)IRQn & 0x1f)))?1:0);
    }
    return Ret_errorStatus;
}

Error_status_t NIVC_setPriority(u8 IRQn,u32 priority){
    Error_status_t Ret_errorStatus=enum_NOK ;
    if((IRQn < 0 || IRQn >81)&&(IRQn !=84)){
        Ret_errorStatus = enum_invalidIRQn;
    }else if(priority >255 || priority <0){
        Ret_errorStatus = enum_invalidPriority;
    }else{
        Ret_errorStatus = enum_OK;
        NVIC->IP[(u32)IRQn]=(priority << (8- _NVIC_PRIO_BITS))&0xff;
    }
    return Ret_errorStatus;   
}

Error_status_t NVIC_generateSoftwareInterrupt(u8 IRQn){
    Error_status_t Ret_errorStatus=enum_NOK ;
    if((IRQn < 0 || IRQn >81)&&(IRQn !=84)){
        Ret_errorStatus = enum_invalidIRQn;
    }else{
        Ret_errorStatus = enum_OK;
        NVIC->STIR=(u32)IRQn;
    }
    return Ret_errorStatus;   
}

Error_status_t NIVC_encodePriority(u32* priority,u32 priorityGroup, u32 preemptPriority, u32 subPriority){
    Error_status_t Ret_errorStatus=enum_NOK ;
    if(priority == NULL){
        Ret_errorStatus = enum_nullPointer;
    }
    else{
        Ret_errorStatus = enum_OK;
        //implementation
    }
    return Ret_errorStatus;
}
