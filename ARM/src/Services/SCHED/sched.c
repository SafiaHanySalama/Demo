/******************************************************************************
 *
 * Module: 
 *
 * File Name: sched.c
 *
 * Description: 
 *
 * Author: Safia Hany
 * 
 * Date:  Mar 24, 2024
 ******************************************************************************/

/*******************************************************************************
 *                                Includes	                                   *
 *******************************************************************************/
#include "services/sched.h"
#include "services/sched_cfg.h"
#include "mcal/systick.h"

typedef struct{
	runnable_t *runnable;
	uint32 remainTimeMS;
}runnableinfo_t;

/*******************************************************************************
 *                              Variables		                               *
 *******************************************************************************/
runnableinfo_t rinfo[_num_runnable];
extern const runnable_t runnable_list[_num_runnable];

// variable to determine if we should call schedule
static volatile uint32 pendingTicks=0;
/*******************************************************************************
 *                         Static Function Prototypes		                   *
 *******************************************************************************/
static void sched(void);
static void tickcb(void) ;
/*******************************************************************************
 *                             Implementation   				               *
 *******************************************************************************/
void tickcb(void)
{
	pendingTicks++;
}
void sched_init(void)
{
    SYSTICK_set_ms(TICK_TIME);
    SYSTICK_setCallBack(tickcb);
	for (uint8 idx = 0;idx<_num_runnable;idx++)
	{
		rinfo[idx].runnable = &runnable_list[idx];
		rinfo[idx].remainTimeMS = runnable_list[idx].delayms;
	}
}

void sched_start(void)
{
	SYSTICK_Init(SYSTICK_MODE);
	while(1)
	{
		// if pendingTicks is greater than one, it means
		// that cpu load is over 100%, because two syscalls
		// occurred when sched was already running
		if(pendingTicks)
		{
			pendingTicks--;
			sched();
		}
	}
}
// void sched_registerrunnable(runnable_t* r)
// {
// 	if(r && (rinfo[r->priority].runnable == NULL_PTR))
// 	{
// 		rinfo[r->priority].runnable = r;
// 		rinfo[r->priority].remainTimeMS = r->delayms;
// 	}
// }


static void sched(void)
{
	uint32 idx;
	for(idx = 0; idx < _num_runnable; idx++)
	{
		// if task not initialized, calling cb will cause a crash as cb is null
		if(rinfo[idx].runnable->cb && rinfo[idx].remainTimeMS == 0)
		{

			rinfo[idx].runnable->cb();

			rinfo[idx].remainTimeMS = rinfo[idx].runnable->periodicity_ms;
		}

		rinfo[idx].remainTimeMS -= TICK_TIME; // One MS passed

	}
}
