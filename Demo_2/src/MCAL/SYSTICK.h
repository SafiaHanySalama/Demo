#ifndef SYSTICK_H
#define SYSTICK_H

#include "std_types.h"

#define mode_OneShot 0
#define mode_Periodic 1

typedef void(* SYSTICK_CBF_t)(void);
typedef enum{
    SYSTICK_enum_NOk,
    SYSTICK_enum_OK,
    SYSTICK_enum_invalidTickValue
}SYSTICK_Error_Status_t;


void SYSTICK_start(u8 mode);
void SYSTICK_stop(void);
SYSTICK_Error_Status_t SYSTICK_setTimeMS(u32 timeMs);
void SYSTICK_setCallBackFunction(SYSTICK_CBF_t cbf);

#endif