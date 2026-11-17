#include "HSwitch.h"
#include "HSwitch_cfg.h"

const HSwitch_Cnfg_t HSwitch_cfg[NUM_OF_SWITCHES] =
    {
        //**USER SWITCHES configuration code start here**//
            [Select_SW]={
                .port=GPIO_PORT_B,
                .pin=GPIO_PIN13,
                .pupd=PULL_DOWN,
                .pressedState=HSWITCH_PRESSED_HIGH
            },
            [Up_SW]={
                .port=GPIO_PORT_B,
                .pin=GPIO_PIN14,
                .pupd=PULL_DOWN,
                .pressedState=HSWITCH_PRESSED_HIGH
            },
            [Down_SW]={
                .port=GPIO_PORT_B,
                .pin=GPIO_PIN15,
                .pupd=PULL_DOWN,
                .pressedState=HSWITCH_PRESSED_HIGH
            }
            
        //**USER SWITCHES configuration code end here**//
};