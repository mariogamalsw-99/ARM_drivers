#include "systick.h"
#include "systick_cfg.h"
#include "systick_private.h"
#include "bitwise_ops.h"
#include "RCC_driver/rcc.h"


static uint32_t Global_Static_RelodValue = 0;
static funcPtr_t glob_funcptrSystcCallBack = 0;

void SysTick_Init()
{
    // calc reload value
    uint64_t loc_uint64Freq = RCC_GetSysClkFreq();
    uint32_t loc_uint32_CntrlRegVal = 0;
    // for 1ms delay  relodValue* 1/freq =1/1000 seconds
    Global_Static_RelodValue = (loc_uint64Freq / 1000.0);
    if (Global_Static_RelodValue > SYSTICK_RELOD_VALUE_MAX)
    {
        // PRESCALE AHB/8
        Global_Static_RelodValue = (loc_uint64Freq / 8000.0);
        CLEAR_BIT(loc_uint32_CntrlRegVal, CLKSOURCE_BIT);
    }
    else
    {
        SET_BIT(loc_uint32_CntrlRegVal, CLKSOURCE_BIT);
    }
    STK_LOAD = Global_Static_RelodValue;
    STK_VAL = 0;
    STK_CTRL |= loc_uint32_CntrlRegVal;
}
void SysTick_Delay(uint32_t cpy_Delayms)
{
    // enable counter
    STK_LOAD = Global_Static_RelodValue - 1;
    STK_VAL = 0;
    SET_BIT(STK_CTRL, ENABLE_BIT);
    for (uint32_t i = 0; i < cpy_Delayms; i++)
    {
        while (GET_BIT(STK_CTRL, COUNTFLAG_BIT) == 0)
            ;
    }
    CLEAR_BIT(STK_CTRL, ENABLE_BIT);
}
void SysTick_Delay_micro(uint32_t cpy_Delaymicors)
{
    // enable counter
    STK_LOAD = (Global_Static_RelodValue / 1000) - 1;
    STK_VAL = 0;
    SET_BIT(STK_CTRL, ENABLE_BIT);
    for (uint32_t i = 0; i < cpy_Delaymicors; i++)
    {
        while (GET_BIT(STK_CTRL, COUNTFLAG_BIT) == 0)
            ;
    }
    CLEAR_BIT(STK_CTRL, ENABLE_BIT);
}

void SysTick_setCallBack(funcPtr_t cpy_funcptrCallBack)
{
    glob_funcptrSystcCallBack = cpy_funcptrCallBack;
     SET_BIT(STK_CTRL,TICKINT_BIT);
}

void SysTick_Start()
{
    SET_BIT(STK_CTRL, ENABLE_BIT);
}
void SysTick_Stop()
{
    SET_BIT(STK_CTRL, ENABLE_BIT);
}
void SysTick_NotifyOnms(uint32_t cpy_uint32Timems)
{
    uint64_t loc_uint64Freq = RCC_GetSysClkFreq();
    Global_Static_RelodValue = (loc_uint64Freq / 1000.0) * cpy_uint32Timems;
    if (Global_Static_RelodValue > SYSTICK_RELOD_VALUE_MAX)
    {
        // PRESCALE AHB/8
        Global_Static_RelodValue = (loc_uint64Freq / 8000.0)* cpy_uint32Timems;
    }
}
void SysTick_NotifyOnmicros(uint32_t cpy_uint32Timems)
{
    uint64_t loc_uint64Freq = RCC_GetSysClkFreq();
    Global_Static_RelodValue = (loc_uint64Freq / 1000000.0) * cpy_uint32Timems;
    if (Global_Static_RelodValue > SYSTICK_RELOD_VALUE_MAX)
    {
        // PRESCALE AHB/8
        Global_Static_RelodValue = (loc_uint64Freq / 8000000.0)* cpy_uint32Timems;
    }

}

void SysTick_Handler()
{
    if(glob_funcptrSystcCallBack != 0)
    {
        glob_funcptrSystcCallBack();
    }
}
