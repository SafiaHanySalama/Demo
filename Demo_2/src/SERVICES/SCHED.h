#include "std_types.h"

//#define MAX 2

typedef void(* runnableCB_t)(void);

typedef struct{
    char* name;
    u32 periodicityMs;
    u32 priority;
    runnableCB_t cb;
    u32 delay;
}runnable_t;

typedef struct{
    runnable_t* r;
    u32 remainingTimeMs;
}runnableInfo_t;

typedef enum{
    SCHED_enum_Nok,
    SCHED_enum_Ok
}SCHED_Error_t;

typedef enum{
    switch_runnable,
    app_runnable,
    _runnable_Max
}Runnables_num;

SCHED_Error_t SCHED_registerRunnable(runnable_t* r);
void SCHED_init(void);
void SCHED_start(void);

