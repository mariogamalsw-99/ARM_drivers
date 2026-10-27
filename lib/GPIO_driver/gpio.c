#include "gpio.h"
#include "gpio_cfg.h"
#include "gpio_private.h"
#include "../../Helpers/bitwise_ops.h"

GPIO_enuErrCode_t GPIO_enuPinWrite(GPIO_enuPort_t cpy_enuPort, GPIO_enuPin_t cpy_enuPin, GPIO_enuDigitalState_t cpy_enuState)
{
    GPIO_enuErrCode_t ret = GPIO_OK;
    GPIO_REGS_T enuPortRegs;
    // Get the right Port Registers
    switch (cpy_enuPort)
    {
    case GPIO_PORT_A:
        enuPortRegs = GPIOA_REGS;
        break;

    case GPIO_PORT_B:
        enuPortRegs = GPIOB_REGS;
        break;

    case GPIO_PORT_C:
        enuPortRegs = GPIOC_REGS;
        break;

    case GPIO_PORT_D:
        enuPortRegs = GPIOD_REGS;
        break;

    case GPIO_PORT_E:
        enuPortRegs = GPIOE_REGS;
        break;

    case GPIO_PORT_H:
        enuPortRegs = GPIOH_REGS;
        break;

    default:
        ret = GPIO_ERR_UNDEFINED_VALUE;
        break;
    }
    // Validate Port
    if (ret = GPIO_OK)
    {
        // Validate Pin
        if (cpy_enuPin >= GPIO_PIN0 && cpy_enuPin <= GPIO_PIN15)
        {
            switch (cpy_enuState)
            {
            case GPIO_DIGITAL_OUTPUT_HIGH:
                enuPortRegs.GPIOX_BSRR.BITSET_REG |= (1 << cpy_enuPin);
                break;
            case GPIO_DIGITAL_OUTPUT_LOW:
                enuPortRegs.GPIOX_BSRR.BITRESET_REG |= (1 << cpy_enuPin);
                break;

            default:
                ret = GPIO_ERR_UNDEFINED_VALUE;
                break;
            }
        }
    }
    return ret;
}
GPIO_enuErrCode_t GPIO_enuPinRead(GPIO_enuPort_t cpy_enuPort, GPIO_enuPin_t cpy_enuPin, GPIO_enuDigitalState_t *ref_enuStatePtr)
{
    GPIO_enuErrCode_t ret = GPIO_OK;
    GPIO_REGS_T enuPortRegs;
    // Get the right Port Registers
    switch (cpy_enuPort)
    {
    case GPIO_PORT_A:
        enuPortRegs = GPIOA_REGS;
        break;

    case GPIO_PORT_B:
        enuPortRegs = GPIOB_REGS;
        break;

    case GPIO_PORT_C:
        enuPortRegs = GPIOC_REGS;
        break;

    case GPIO_PORT_D:
        enuPortRegs = GPIOD_REGS;
        break;

    case GPIO_PORT_E:
        enuPortRegs = GPIOE_REGS;
        break;

    case GPIO_PORT_H:
        enuPortRegs = GPIOH_REGS;
        break;

    default:
        ret = GPIO_ERR_UNDEFINED_VALUE;
        break;
    }
    // Validate Port
    if (ret = GPIO_OK)
    {
        // Validate Pin
        if (cpy_enuPin >= GPIO_PIN0 && cpy_enuPin <= GPIO_PIN15)
        {
            ref_enuStatePtr = GET_BIT(enuPortRegs.GPIOX_IDR, cpy_enuPin);
        }
    }
    return ret;
}
GPIO_enuErrCode_t GPIO_enuPinCfgMode(GPIO_enuPort_t cpy_enuPort, GPIO_enuPin_t cpy_enuPin, GPIO_enuMode_t cpy_enumMode);
GPIO_enuErrCode_t GPIO_enuPinCfgOutputType(GPIO_enuPort_t cpy_enuPort, GPIO_enuPin_t cpy_enuPin, GPIO_enuOutputType_t cpy_enuOutType);
GPIO_enuErrCode_t GPIO_enuPinCfgSpeed(GPIO_enuPort_t cpy_enuPort, GPIO_enuPin_t cpy_enuPin, GPIO_enuOutputSpeed_t cpy_enuSpeed);
GPIO_enuErrCode_t GPIO_enuPinCfgPUPD(GPIO_enuPort_t cpy_enuPort, GPIO_enuPin_t cpy_enuPin, GPIO_enuPUPD_t cpy_enuPUPD);