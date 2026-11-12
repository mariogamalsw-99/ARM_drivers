#include "sched.h"
#include "SYSTICK_driver/systick.h"
#include "SHED_cfg.h"
#include "SCHED_priveate.h"

static SCHED_Runnable_t *Glob_staticRunnableArr[MAX_NUM_OF_RUNNABLES] = {0};
static uint8_t Glob_staticUint32isTriggerdFlag = 0;
static uint64_t Glob_staticUint64Timems = 0;

SCHED_ErrCode_t SCHED_init(void)
{
    SCHED_ErrCode_t loc_enuretErrCode = SCHED_OK;

    SysTick_Init();
    SysTick_setCallBack(SCHED_Handler);
    SysTick_NotifyOnms(1);
    return loc_enuretErrCode;
}
SCHED_ErrCode_t SCHED_start(void)
{
    SysTick_Start();
    while (1)
    {
        uint32_t i;
        if (Glob_staticUint32isTriggerdFlag)
        {
            Glob_staticUint32isTriggerdFlag = 0;
            Glob_staticUint64Timems++;
            for (i = 0; i < MAX_NUM_OF_RUNNABLES; i++)
            {
                if (Glob_staticRunnableArr[i] != 0 && Glob_staticRunnableArr[i]->func != 0)
                {
                    if(--(Glob_staticRunnableArr[i]->delayms) == 0)
                    {
                        Glob_staticRunnableArr[i]->func();
                        if(Glob_staticRunnableArr[i]->cyclicTimems != 0)
                        {
                            Glob_staticRunnableArr[i]->delayms=Glob_staticRunnableArr[i]->cyclicTimems;
                        }
                    }
                }
            }
        }
    }
    return SCHED_ERR;
}
SCHED_ErrCode_t SCHED_stop(void)
{
    SysTick_Stop();
    return SCHED_OK;
}
SCHED_ErrCode_t SCHED_registerRunnable(SCHED_Runnable_t *ref_enuRunnablePtr)
{
    SCHED_ErrCode_t loc_enuretErrCode = SCHED_OK;
    if (Glob_staticRunnableArr[ref_enuRunnablePtr->priority] != 0)
    {
        loc_enuretErrCode = SCHED_ERR_DUPLICATE_PRIORITY;
    }
    else
    {
        Glob_staticRunnableArr[ref_enuRunnablePtr->priority] = ref_enuRunnablePtr;
    }
    return loc_enuretErrCode;
}
SCHED_ErrCode_t SCHED_removeRunnable(SCHED_Runnable_t *ref_enuRunnablePtr)
{
    SCHED_ErrCode_t loc_enuretErrCode = SCHED_OK;
    if (Glob_staticRunnableArr[ref_enuRunnablePtr->priority] == 0)
    {
        loc_enuretErrCode = SCHED_ERR_NO_TAST_WITH__PRIORITY_TO_REMOVE;
    }
    else
    {
        // must be same func and same cyclictime
        if (
            ref_enuRunnablePtr->func == Glob_staticRunnableArr[ref_enuRunnablePtr->priority]->func &&
            ref_enuRunnablePtr->cyclicTimems == Glob_staticRunnableArr[ref_enuRunnablePtr->priority]->cyclicTimems )
        {
            loc_enuretErrCode = SCHED_ERR_REMOVE_DIFFERENT_TASK;
        }
        else
        {
            Glob_staticRunnableArr[ref_enuRunnablePtr->priority] = 0;
        }
    }
    return loc_enuretErrCode;
}

static void SCHED_Handler()
{
    Glob_staticUint32isTriggerdFlag = 1;
}