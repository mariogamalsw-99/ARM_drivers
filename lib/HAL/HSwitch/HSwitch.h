#ifndef HSwitch_H
#define HSwitch_H
#include <GPIO_driver/gpio.h>
#include "HSwitch_cfg.h"
#include <stdint.h>
//___________________USER type ____________________
typedef enum
{
    HSWITCH_PRESSED_HIGH=0,
    HSWITCH_PRESSED_LOW=1,
}HSwitch_PressedState_t;
typedef enum
{
    HSwitch_PRESSED,
    HSwitch_PRERELEASED,
    HSwitch_RELEASED,
    HSwitch_PREPRESSED,
}HSwitch_State_t;

typedef struct 
{
    GPIO_enuPort_t port;
    GPIO_enuPin_t pin;
    GPIO_enuPUPD_t pupd;
    HSwitch_PressedState_t   pressedState;

}HSwitch_Cnfg_t;

typedef enum
{
    HSwitch_ERR,
    HSwitch_OK,
    HSwitch_OK_NEW_VAL,
    HSwitch_OK_OLD_VAL,
    HSwitch_ERR_GPIO_ERR,
    HSwitch_ERR_UNDEFIND_VALUE,

}HSwitch_ErrorCode_t;


//_______________________USER API________________
HSwitch_ErrorCode_t HSwitch_enuInitSwitches(uint8_t priority);
HSwitch_ErrorCode_t HSwitch_enuReadSwitch(HSwitch_Switches_t,HSwitch_State_t*);





#endif