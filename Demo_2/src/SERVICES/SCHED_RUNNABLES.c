#include "SCHED.h"
#include "SWITCH.h"
#include "app_sw_led.h"
u8 tickMs = 25;


const runnable_t runnables[_runnable_Max]={
    [switch_runnable]={
        .name="switch",
        .periodicityMs=50,
        .priority=0,
        .cb=switch_runnable_cb,
        .delay=0
    },
    [app_runnable]={
        .name="app",
        .periodicityMs=100,
        .priority=1,
        .cb=App,
        .delay=0
    }
};