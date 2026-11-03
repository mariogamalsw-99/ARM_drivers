#include "systick.h"
#include "systick_cfg.h"
#include "systick_private.h"
#include "bitwise_ops.h"
static uint32_t Global_Static_RelodValue = 0;
void SysTick_Init()
{
    // calc reload value
    uint32_t loc_uint32_CntrlRegVal = 0;
    //for 1ms delay  relodValue* 1/freq =1/1000 seconds
    Global_Static_RelodValue = (AHB_FREQUANCY / 1000.0);
    if (Global_Static_RelodValue > SYSTICK_RELOD_VALUE_MAX)
    {
        // PRESCALE AHB/8
        Global_Static_RelodValue = (AHB_FREQUANCY / 8000.0);
        CLEAR_BIT(loc_uint32_CntrlRegVal, CLKSOURCE_BIT);
    }
    else
    {
        SET_BIT(loc_uint32_CntrlRegVal, CLKSOURCE_BIT);
    }
    STK_LOAD = Global_Static_RelodValue;
    STK_VAL = 0;
    STK_CTRL|=loc_uint32_CntrlRegVal;
}
void SysTick_Delay(uint32_t cpy_Delayms)
{
    //enable counter
    STK_LOAD = Global_Static_RelodValue-1;
    STK_VAL = 0;
    SET_BIT(STK_CTRL,ENABLE_BIT);   
    for(uint32_t i=0;i<cpy_Delayms;i++)
    {
        while(GET_BIT(STK_CTRL,COUNTFLAG_BIT)==0);
    }
     CLEAR_BIT(STK_CTRL,ENABLE_BIT);

}
