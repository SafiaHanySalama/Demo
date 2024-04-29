#ifndef SWITCH_H
#define SWITCH_H

#include "std_types.h"
#include "SWITCH_CFG.h"

#define state_NOT_PRESSED       0
#define state_PRESSED           1
#define connection_PULL_UP      1
#define connection_PULL_DOWN    0
#define runnable_used

typedef struct{
    u32 * port;
    u32 pin;
    u8 state;
    u8 connection;
}switch_cfg_t;

typedef enum{
    SWITCH_enumNok,
    SWITCH_EOk,
    SWITCH_NullPtr
}SWITCH_ErrorStatus_t;

/// @brief get switch state
/// @param state ,options:  state_xx
/// @param switch_id ,options:  switch_xx
/// @return SWITCH_ErrorStatus
SWITCH_ErrorStatus_t SWITCH_getStatus(u32 switch_id ,u8* state);

void SWITCH_Init(void);

void switch_runnable_cb(void);

#endif