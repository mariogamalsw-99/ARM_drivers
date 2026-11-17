#include "HSwitch_cfg.h"
#include "HSwitch.h"
#include "HSwitch_private.h"
#include <GPIO_driver/gpio.h>
#include "SCHED/SCHED.h"
#include "GPIO_driver/gpio.h"
#include "RCC_driver/rcc.h"

//_____________________________Extern HSwitch_CFG array
extern const HSwitch_Cnfg_t HSwitch_cfg[];
static HSwitch_track_t HSwitch_track[NUM_OF_SWITCHES];
static SCHED_Runnable_t Glob_staticenuHSwitch_runnable={
    .cyclicTimems=5,
    .delayms=10,
    .func=HSwitch_Runnable,
    .priority=INT8_MAX
    };

static void HSwitch_Runnable()
{
    GPIO_enuDigitalState_t loc_enuPinState;
    for (int i = 0; i < NUM_OF_SWITCHES; i++)
    {
        // remove 5th read and add new read
        HSwitch_track[i].readHistory = (HSwitch_track[i].readHistory << 1);
        GPIO_enuPinRead(HSwitch_cfg[i].port, HSwitch_cfg[i].pin, &loc_enuPinState);
        // invert it pressedLow only
        loc_enuPinState ^= HSwitch_cfg[i].pressedState;
        HSwitch_track[i].readHistory = HSwitch_track[i].readHistory | loc_enuPinState;
        // if fully zero (released)
        if (HSwitch_track[i].readHistory == SWITCH_FULLY_RELEASED)
        {
            if (HSwitch_track[i].State != HSwitch_RELEASED)
            {
                HSwitch_track[i].State = HSwitch_RELEASED;
                HSwitch_track[i].isNewRead = 1;
            }
            else
            {
                // do nothing as its already set as released
            }
        }
        // if fully one (pressed)
        if (HSwitch_track[i].readHistory == SWITCH_FULLY_PRESSED)
        {
            if (HSwitch_track[i].State != HSwitch_PRESSED)
            {
                HSwitch_track[i].State = HSwitch_PRESSED;
                HSwitch_track[i].isNewRead = 1;
            }
            else
            {
                // do nothing as its already set as pressed
            }
        }
        // if in between
        else
        {
            if (HSwitch_track[i].State == HSwitch_PRESSED)
            {
                HSwitch_track[i].State = HSwitch_PRERELEASED;
                HSwitch_track[i].isNewRead = 1;
            }
            else if (HSwitch_track[i].State == HSwitch_RELEASED)
            {
                HSwitch_track[i].State = HSwitch_PREPRESSED;
                HSwitch_track[i].isNewRead = 1;
            }
            else
            {
                // do nothing as its already set to unstable state
            }
        }
    }
}
HSwitch_ErrorCode_t HSwitch_enuInitSwitches(uint8_t priority)
{
    // read all ports and enable thim only one time
    uint8_t loc_portsArray[NUM_OF_PORTS] = {0};
    for (int i = 0; i < NUM_OF_SWITCHES; i++)
    {
        loc_portsArray[HSwitch_cfg[i].port]++;
    }
    for (int i = 0; i < NUM_OF_PORTS; i++)
    {
        if (loc_portsArray[i] != 0)
        {
            switch (i)
            {
            case GPIO_PORT_A:
                RCC_CntrlPeripheralClck(PERIPHERAL_AHB1_GPIOA, PERIPHERAL_ENABLED);
                break;

            case GPIO_PORT_B:
                RCC_CntrlPeripheralClck(PERIPHERAL_AHB1_GPIOB, PERIPHERAL_ENABLED);
                break;

            case GPIO_PORT_C:
                RCC_CntrlPeripheralClck(PERIPHERAL_AHB1_GPIOC, PERIPHERAL_ENABLED);
                break;

            case GPIO_PORT_D:
                RCC_CntrlPeripheralClck(PERIPHERAL_AHB1_GPIOD, PERIPHERAL_ENABLED);
                break;

            case GPIO_PORT_E:
                RCC_CntrlPeripheralClck(PERIPHERAL_AHB1_GPIOE, PERIPHERAL_ENABLED);
                break;

            case GPIO_PORT_H:
                RCC_CntrlPeripheralClck(PERIPHERAL_AHB1_GPIOH, PERIPHERAL_ENABLED);
                break;

            default:
                break;
            }
        }
    }
    
    for (int i = 0; i < NUM_OF_SWITCHES; i++)
    {
       GPIO_enuPinCfgMode(HSwitch_cfg[i].port,HSwitch_cfg[i].pin,GPIO_DIGITAL_INPUT);
       GPIO_enuPinCfgPUPD(HSwitch_cfg[i].port,HSwitch_cfg[i].pin ,HSwitch_cfg[i].pupd);
       HSwitch_track[i].isNewRead=0;
       HSwitch_track[i].readHistory=0;
       HSwitch_track[i].State=HSwitch_RELEASED;
    }
    Glob_staticenuHSwitch_runnable.priority=priority;
    SCHED_registerRunnable(&Glob_staticenuHSwitch_runnable);
    return HSwitch_OK;
}
HSwitch_ErrorCode_t HSwitch_enuReadSwitch(HSwitch_Switches_t cpy_enuSw , HSwitch_State_t* ref_SWState)
{
    *ref_SWState=HSwitch_track[cpy_enuSw].State;
    if(HSwitch_track[cpy_enuSw].isNewRead)
    {
        HSwitch_track[cpy_enuSw].isNewRead=0;
        return HSwitch_OK_NEW_VAL;
    }
    else
    {
        return HSwitch_OK_OLD_VAL;
    }
}
