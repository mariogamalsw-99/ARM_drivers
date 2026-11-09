#include "NVIC.h"
#include "NVIC_cfg.h"
#include "NVIC_private.h"
#include "../../include/bitwise_ops.h"
//_____________________________Static Functions__________________________
static NVIC_enuErrCode_t NVIC_enuIsValidIRQ(NVIC_enuIRQn_t cpy_IRQn)
{
    NVIC_enuErrCode_t loc_enuErrCode = NVIC_ERR;
    switch (cpy_IRQn)
    {
    case NVIC_IRQn_WWDG ... NVIC_IRQn_ADC:
    case NVIC_IRQn_EXTI9_5 ... NVIC_IRQn_USART2:
    case NVIC_IRQn_EXTI15_10 ... NVIC_IRQn_EXTI18:
    case NVIC_IRQn_DMA1_Stream7:
    case NVIC_IRQn_SDIO ... NVIC_IRQn_SPI3:
    case NVIC_IRQn_DMA2_Stream0 ... NVIC_IRQn_DMA2_Stream4:
    case NVIC_IRQn_OTG_FS ... NVIC_IRQn_I2C3_ER:
    case NVIC_IRQn_FPU:
    case NVIC_IRQn_SPI4:
        loc_enuErrCode = NVIC_OK;
        break;

    default:
        loc_enuErrCode = NVIC_INVALID_IRQ_ERR;
        break;
    }
    return loc_enuErrCode;
}

//_____________________________Global functins_____________________________
/**
 * Set the priority grouping
 */
NVIC_enuErrCode_t NVIC_SetPriorityGrouping(uint32_t priority_grouping)
{
    NVIC_enuErrCode_t loc_enuErrCode = NVIC_enuIsValidIRQ(cpy_enuIRQn);
    if (loc_enuErrCode == NVIC_OK)
    {
    }

    return loc_enuErrCode;
}
/**
 * Enable cpy_enuIRQn
 */
NVIC_enuErrCode_t NVIC_EnableIRQ(NVIC_enuIRQn_t cpy_enuIRQn)
{
    NVIC_enuErrCode_t loc_enuErrCode = NVIC_enuIsValidIRQ(cpy_enuIRQn);
    if (loc_enuErrCode == NVIC_OK)
    {
        SET_BIT(NVIC_ISER_ARR[cpy_enuIRQn / NVIC_REG_SIZE], cpy_enuIRQn % NVIC_REG_SIZE);
        if (GET_BIT(NVIC_ISER_ARR[cpy_enuIRQn / NVIC_REG_SIZE], cpy_enuIRQn % NVIC_REG_SIZE) == 0)
        {
            loc_enuErrCode = NVIC_ERR;
        }
    }
    return loc_enuErrCode;
}
/**
 * Disable cpy_enuIRQn
 */
NVIC_enuErrCode_t NVIC_DisableIRQ(NVIC_enuIRQn_t cpy_enuIRQn)
{
    NVIC_enuErrCode_t loc_enuErrCode = NVIC_enuIsValidIRQ(cpy_enuIRQn);
    if (loc_enuErrCode == NVIC_OK)
    {
        SET_BIT(NVIC_ICER_ARR[cpy_enuIRQn / NVIC_REG_SIZE], cpy_enuIRQn % NVIC_REG_SIZE);
        if (GET_BIT(NVIC_ICER_ARR[cpy_enuIRQn / NVIC_REG_SIZE], cpy_enuIRQn % NVIC_REG_SIZE) != 0)
        {
            loc_enuErrCode = NVIC_ERR;
        }
    }
    return loc_enuErrCode;
}
/**
 * Return true (IRQ-Number) if cpy_enuIRQn is
pending
 */
NVIC_enuErrCode_t NVIC_GetPendingIRQ(NVIC_enuIRQn_t cpy_enuIRQn, NVIC_enuPendingState_t *ref_enuPtrPendingState)
{
    NVIC_enuErrCode_t loc_enuErrCode = NVIC_enuIsValidIRQ(cpy_enuIRQn);
    if (loc_enuErrCode == NVIC_OK)
    {
        *ref_enuPtrPendingState = GET_BIT(NVIC_ISPR_ARR[cpy_enuIRQn / 32], cpy_enuIRQn % 32);
    }
    return loc_enuErrCode;
}
/**
 * Set cpy_enuIRQn pending
 */
NVIC_enuErrCode_t NVIC_SetPendingIRQ(NVIC_enuIRQn_t cpy_enuIRQn)
{
    NVIC_enuErrCode_t loc_enuErrCode = NVIC_enuIsValidIRQ(cpy_enuIRQn);
    if (loc_enuErrCode == NVIC_OK)
    {
        SET_BIT(NVIC_ISPR_ARR[cpy_enuIRQn / NVIC_REG_SIZE], cpy_enuIRQn % NVIC_REG_SIZE);
        if (GET_BIT(NVIC_ISPR_ARR[cpy_enuIRQn / NVIC_REG_SIZE], cpy_enuIRQn % NVIC_REG_SIZE) == 0)
        {
            loc_enuErrCode = NVIC_ERR;
        }
    }
    return loc_enuErrCode;
}
/**
 * Clear cpy_enuIRQn pending status
 */
NVIC_enuErrCode_t NVIC_ClearPendingIRQ(NVIC_enuIRQn_t cpy_enuIRQn)
{
    NVIC_enuErrCode_t loc_enuErrCode = NVIC_enuIsValidIRQ(cpy_enuIRQn);
    if (loc_enuErrCode == NVIC_OK)
    {
        SET_BIT(NVIC_ICPR_ARR[cpy_enuIRQn / NVIC_REG_SIZE], cpy_enuIRQn % NVIC_REG_SIZE);
        if (GET_BIT(NVIC_ICPR_ARR[cpy_enuIRQn / NVIC_REG_SIZE], cpy_enuIRQn % NVIC_REG_SIZE) != 0)
        {
            loc_enuErrCode = NVIC_ERR;
        }
    }
    return loc_enuErrCode;
}
/**
 * Return the IRQ number of the active interrupt
 */
NVIC_enuErrCode_t NVIC_GetActive(NVIC_enuIRQn_t cpy_enuIRQn, NVIC_enuActiveState_t *ref_enuPtrActiveState)
{
    NVIC_enuErrCode_t loc_enuErrCode = NVIC_enuIsValidIRQ(cpy_enuIRQn);
    if (loc_enuErrCode == NVIC_OK)
    {
        *ref_enuPtrActiveState = GET_BIT(NVIC_IABR_ARR[cpy_enuIRQn / NVIC_REG_SIZE], cpy_enuIRQn % NVIC_REG_SIZE);
    }
    return loc_enuErrCode;
}
/**
 * Set priority for cpy_enuIRQn
 */
NVIC_enuErrCode_t NVIC_SetPriority(NVIC_enuIRQn_t cpy_enuIRQn, uint32_t cpy_ui32Priority)
{
    NVIC_enuErrCode_t loc_enuErrCode = NVIC_enuIsValidIRQ(cpy_enuIRQn);
    if (loc_enuErrCode == NVIC_OK)
    {
        SET_BITS(&NVIC_IPR_ARR[cpy_enuIRQn / NVIC_NUM_OF_IRQ_PRIORITY_IN_REG], 8, (cpy_enuIRQn % NVIC_NUM_OF_IRQ_PRIORITY_IN_REG) * NVIC_NUM_OF_PRIORTY_BITS_ARM, (cpy_ui32Priority << NVIC_PRIORTY_BITS_OFFSET));
    }
    return loc_enuErrCode;
}
/**
 * Read priority of cpy_enuIRQn
 */
NVIC_enuErrCode_t NVIC_GetPriority(NVIC_enuIRQn_t cpy_enuIRQn, uint32_t *ref_ui32PtrPriority)
{
    NVIC_enuErrCode_t loc_enuErrCode = NVIC_enuIsValidIRQ(cpy_enuIRQn);
    if (loc_enuErrCode == NVIC_OK)
    {
        *ref_ui32PtrPriority = (GET_BITS(&NVIC_IPR_ARR[cpy_enuIRQn / NVIC_NUM_OF_IRQ_PRIORITY_IN_REG], MASK_8BIT, (cpy_enuIRQn % NVIC_NUM_OF_IRQ_PRIORITY_IN_REG) * NVIC_NUM_OF_PRIORTY_BITS_ARM) >> NVIC_PRIORTY_BITS_OFFSET);
    }
    return loc_enuErrCode;
}
/**
 * Reset the system
 */
NVIC_enuErrCode_t NVIC_SystemReset(void)
{
    NVIC_enuErrCode_t loc_enuErrCode = NVIC_enuIsValidIRQ(cpy_enuIRQn);
    if (loc_enuErrCode == NVIC_OK)
    {
    }
    return loc_enuErrCode;
}