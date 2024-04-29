#include "SWITCH.h"
#include "GPIO.h"

const switch_cfg_t SWITCHES[_switch_num]={
    [switch_1]={
        .port=GPIOA,
        .pin=PIN6,
        .state=state_NOT_PRESSED,
        .connection=connection_PULL_UP
    },
    [switch_2]={
        .port=GPIOA,
        .pin=PIN0,
        .state=state_NOT_PRESSED,
        .connection=connection_PULL_UP
    }
};