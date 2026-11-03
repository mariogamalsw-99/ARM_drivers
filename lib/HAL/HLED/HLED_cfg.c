#include "HLED.h"
#include "HLED_cfg.h"

const HLED_Cnfg_t HLED_cfg[NUM_OF_LEDS] =
    {
        //**USER LEDS configuration code start here**//
            [Brake_LED]={
                .port=GPIO_PORT_C,
                .pin=GPIO_PIN13,
                .speed=GPIO_LOW_SPEED_OUTPUT,
                .outType=OUTPUT_STATE_OPEN_DRAIN,
                .intialState=HLED_OFF,
                .activeState=HLED_ACTIVE_LOW
            }
        //**USER LEDS configuration code end here**//
};