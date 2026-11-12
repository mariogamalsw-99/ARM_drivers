#ifndef SCHED_H
#define SCHED_H
#include <stdint.h>
typedef void (*FuncPtr_t)(void);
typedef struct 
{
    FuncPtr_t func;
    uint32_t cyclicTimems;
    uint32_t delayms;
    uint32_t priority;

}SCHED_Runnable_t;

typedef enum
{
    SCHED_ERR,
    SCHED_OK,
    SCHED_ERR_DUPLICATE_PRIORITY,
    SCHED_ERR_NO_TAST_WITH__PRIORITY_TO_REMOVE,
    SCHED_ERR_REMOVE_DIFFERENT_TASK,
}SCHED_ErrCode_t;

SCHED_ErrCode_t SCHED_init(void);
SCHED_ErrCode_t SCHED_start(void);
SCHED_ErrCode_t SCHED_stop(void);
SCHED_ErrCode_t SCHED_registerRunnable(SCHED_Runnable_t* ref_enuRunnablePtr);
SCHED_ErrCode_t SCHED_removeRunnable(SCHED_Runnable_t* ref_enuRunnablePtr);



#endif