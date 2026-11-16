#ifndef HSWITCH_PRIVATE_H
#define HSWITCH_PRIVATE_H

#include "HSwitch.h"
#include <stdint.h>
//___________________PrivateType type ____________________

#define SWITCH_FULLY_RELEASED  0
#define SWITCH_FULLY_PRESSED 0x1f

typedef struct 
{
    uint8_t isNewRead:3;
    uint8_t readHistory:5;
    HSwitch_State_t   State;

}HSwitch_track_t;


static void HSwitch_Runnable();


#endif