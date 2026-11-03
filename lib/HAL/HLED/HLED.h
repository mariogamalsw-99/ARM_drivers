#ifndef HLED_H
#define HLED_H
#include <GPIO_driver/gpio.h>
#include "HLED_cfg.h"
//___________________USER type ____________________
typedef enum
{
    HLED_ACTIVE_LOW,
    HLED_ACTIVE_HIGH,
}HLED_ActiveState_t;
typedef enum
{
    HLED_OFF,
    HLED_ON,
}HLED_State_t;
typedef struct 
{
    GPIO_enuPort_t port;
    GPIO_enuPin_t pin;
    GPIO_enuOutputSpeed_t speed;
    GPIO_enuOutputType_t outType;
    HLED_State_t intialState;
    HLED_ActiveState_t   activeState;

}HLED_Cnfg_t;

typedef enum
{
    HLED_ERR,
    HLED_OK,
    HLED_ERR_GPIO_ERR,
    HLED_ERR_UNDEFIND_VALUE,

}HLED_ErrorCode_t;


//_______________________USER API________________
HLED_ErrorCode_t HLED_enuInitLED();
HLED_ErrorCode_t HLED_enuTurnOnLED(HLED_LEDs_t);
HLED_ErrorCode_t HLED_enuTurnOffLED(HLED_LEDs_t);
HLED_ErrorCode_t HLED_enuToggleLED(HLED_LEDs_t);
HLED_ErrorCode_t HLED_enuSetLEDState(HLED_LEDs_t cpy_enuLedIndex,HLED_State_t cpy_enuLedState);




#endif