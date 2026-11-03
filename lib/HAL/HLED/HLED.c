#include "HLED_cfg.h"
#include "HLED.h"
#include <GPIO_driver/gpio.h>

//_____________________________Extern HLED_CFG array
extern const HLED_Cnfg_t HLED_cfg[];

HLED_ErrorCode_t HLED_enuInitLED()
{
    HLED_ErrorCode_t Loc_enuReturnErrCode = HLED_OK;
    GPIO_enuErrCode_t Loc_enuGPIOErrCode = GPIO_OK;
    for (int i = 0; i < NUM_OF_LEDS; i++)
    {
        Loc_enuGPIOErrCode = GPIO_enuPinCfgMode(HLED_cfg[i].port, HLED_cfg[i].pin, GPIO_DIGITAL_OUTPUT);
        if (Loc_enuGPIOErrCode != GPIO_OK)
        {
            Loc_enuReturnErrCode = HLED_ERR_GPIO_ERR;
            break;
        }
        Loc_enuGPIOErrCode = GPIO_enuPinCfgOutputType(HLED_cfg[i].port, HLED_cfg[i].pin, HLED_cfg[i].outType);
        if (Loc_enuGPIOErrCode != GPIO_OK)
        {
            Loc_enuReturnErrCode = HLED_ERR_GPIO_ERR;
            break;
        }
        Loc_enuGPIOErrCode = GPIO_enuPinCfgSpeed(HLED_cfg[i].port, HLED_cfg[i].pin, HLED_cfg[i].speed);
        if (Loc_enuGPIOErrCode != GPIO_OK)
        {
            Loc_enuReturnErrCode = HLED_ERR_GPIO_ERR;
            break;
        }
        Loc_enuReturnErrCode = HLED_enuSetLEDState(i, HLED_cfg[i].intialState);
    }
    return Loc_enuReturnErrCode;
}
HLED_ErrorCode_t HLED_enuTurnOnLED(HLED_LEDs_t cpy_enuLedIndex)
{
    HLED_ErrorCode_t Loc_enuReturnErrCode = HLED_OK;
    GPIO_enuErrCode_t Loc_enuGPIOErrCode = GPIO_OK;

    switch (HLED_cfg[cpy_enuLedIndex].activeState)
    {
    case HLED_ACTIVE_HIGH:
        Loc_enuGPIOErrCode = GPIO_enuPinWrite(HLED_cfg[cpy_enuLedIndex].port, HLED_cfg[cpy_enuLedIndex].pin, GPIO_DIGITAL_OUTPUT_HIGH);
        break;

    case HLED_ACTIVE_LOW:
        Loc_enuGPIOErrCode = GPIO_enuPinWrite(HLED_cfg[cpy_enuLedIndex].port, HLED_cfg[cpy_enuLedIndex].pin, GPIO_DIGITAL_OUTPUT_LOW);
        break;

    default:
        Loc_enuReturnErrCode = HLED_ERR_UNDEFIND_VALUE;
        break;
    }
    if (Loc_enuGPIOErrCode != GPIO_OK)
    {
        Loc_enuReturnErrCode = HLED_ERR_GPIO_ERR;
    }
    return Loc_enuReturnErrCode;
}
HLED_ErrorCode_t HLED_enuTurnOffLED(HLED_LEDs_t cpy_enuLedIndex)
{
    HLED_ErrorCode_t Loc_enuReturnErrCode = HLED_OK;
    GPIO_enuErrCode_t Loc_enuGPIOErrCode = GPIO_OK;

    switch (HLED_cfg[cpy_enuLedIndex].activeState)
    {
    case HLED_ACTIVE_HIGH:
        Loc_enuGPIOErrCode = GPIO_enuPinWrite(HLED_cfg[cpy_enuLedIndex].port, HLED_cfg[cpy_enuLedIndex].pin, GPIO_DIGITAL_OUTPUT_LOW);
        break;

    case HLED_ACTIVE_LOW:
        Loc_enuGPIOErrCode = GPIO_enuPinWrite(HLED_cfg[cpy_enuLedIndex].port, HLED_cfg[cpy_enuLedIndex].pin, GPIO_DIGITAL_OUTPUT_HIGH);
        break;

    default:
        Loc_enuReturnErrCode = HLED_ERR_UNDEFIND_VALUE;
        break;
    }
    if (Loc_enuGPIOErrCode != GPIO_OK)
    {
        Loc_enuReturnErrCode = HLED_ERR_GPIO_ERR;
    }
    return Loc_enuReturnErrCode;
}
HLED_ErrorCode_t HLED_enuToggleLED(HLED_LEDs_t cpy_enuLedIndex)
{
    HLED_ErrorCode_t Loc_enuReturnErrCode = HLED_OK;
    GPIO_enuErrCode_t Loc_enuGPIOErrCode = GPIO_OK;
    GPIO_enuDigitalState_t loc_enuLedPinStatus;
    Loc_enuGPIOErrCode = GPIO_enuPinRead(HLED_cfg[cpy_enuLedIndex].port, HLED_cfg[cpy_enuLedIndex].pin, &loc_enuLedPinStatus);
    if (Loc_enuGPIOErrCode == GPIO_OK)
    {
        Loc_enuReturnErrCode = GPIO_enuPinWrite(HLED_cfg[cpy_enuLedIndex].port, HLED_cfg[cpy_enuLedIndex].pin, ~loc_enuLedPinStatus);
        if (Loc_enuGPIOErrCode != GPIO_OK)
        {
            Loc_enuReturnErrCode = HLED_ERR_GPIO_ERR;
        }
    }
    else
    {
        Loc_enuReturnErrCode = HLED_ERR_GPIO_ERR;
    }
    return Loc_enuReturnErrCode;
}
HLED_ErrorCode_t HLED_enuSetLEDState(HLED_LEDs_t cpy_enuLedIndex, HLED_State_t cpy_enuLedState)
{
    HLED_ErrorCode_t Loc_enuReturnErrCode = HLED_OK;

    switch (cpy_enuLedState)
    {
    case HLED_ON:
        Loc_enuReturnErrCode = HLED_enuTurnOnLED(cpy_enuLedIndex);
        break;

    case HLED_OFF:
        Loc_enuReturnErrCode = HLED_enuTurnOffLED(cpy_enuLedIndex);
        break;

    default:
        Loc_enuReturnErrCode = HLED_ERR_UNDEFIND_VALUE;
        break;
    }
    return Loc_enuReturnErrCode;
}