/******************************************************************************
 *
 * Module: 
 *
 * File Name: sched.h
 *
 * Description: 
 *
 * Author: Safia Hany
 * 
 * Date:  Mar 24, 2024
 ******************************************************************************/
#ifndef INCLUDE_SERVICES_SCHED_H_
#define INCLUDE_SERVICES_SCHED_H_

#include "Std_Types.h"

#define TICK_TIME		100

typedef void (*runnablecb_t) (void);
typedef struct{
    char * name;
    uint32 periodicity_ms;
    uint32 priority;
    runnablecb_t cb;
    uint32 delayms;
}runnable_t;

//void sched_registerrunnable(runnable_t *runnable);
void sched_init(void);
void sched_start(void);

#endif /* INCLUDE_SERVICES_SCHED_H_ */
