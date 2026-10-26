#include "rcc.h"
#include "rcc_cfg.h"
#include "rcc_private.h"
#include "../../Helpers/bitwise_ops.h"
#include <stdio.h>
#include <stdint.h>

// public functions
ERCCS_Err RCC_SelectSysClckSrc(ESysClkSrc clkSrc)
{
    switch (clkSrc)
    {
    case SYSCLK_HSI_SRC:
    case SYSCLK_HSE_SRC:
    case SYSCLK_PLL_SRC:
        SET_BITS(&RCC_REGS.RCC_CFGR, 2, SW, clkSrc);
        break;

    default:
        return RCC_ERR_UNDEFINED_VALUE;
    }
    return RCC_OK;
}

ERCCS_Err RCC_CntrlSysClckSrc(ESysClkSrc clkSrc, ClckSrcCnfg_t clckCnfg)
{
    int16_t timeout = 120;
    switch (clkSrc)
    {
    case SYSCLK_HSI_SRC:
        switch (clckCnfg.status)
        {
        case CLCK_SRC_ENABLED:
            SET_BIT(RCC_REGS.RCC_CR, HSION);
            while (!GET_BIT(RCC_REGS.RCC_CR, HSIRDY) && timeout--)
                ;
            break;
        case CLCK_SRC_DISABLED:
            CLEAR_BIT(RCC_REGS.RCC_CR, HSION);
            break;
        default:
            return RCC_ERR_UNDEFINED_VALUE;
        }
        break;
    case SYSCLK_HSE_SRC:
        switch (clckCnfg.status)
        {
        case CLCK_SRC_ENABLED:
            // disable HSE to be able to set bypass status
            CLEAR_BIT(RCC_REGS.RCC_CR, HSEON);
            switch (clckCnfg.bypass)

            {
            case CLK_HSE_RESONATOR:
                CLEAR_BIT(RCC_REGS.RCC_CR, HSEBYP);
                break;
            case CLK_HSE_BYPASS:
                SET_BIT(RCC_REGS.RCC_CR, HSEBYP);
                break;
            default:
                return RCC_ERR_UNDEFINED_VALUE;
            }
            SET_BIT(RCC_REGS.RCC_CR, HSEON);
            while (!GET_BIT(RCC_REGS.RCC_CR, HSERDY) && timeout--)
                ;
            break;
        case CLCK_SRC_DISABLED:
            CLEAR_BIT(RCC_REGS.RCC_CR, HSION);
            break;
        default:
            return RCC_ERR_UNDEFINED_VALUE;
        }
        break;
    case SYSCLK_PLL_SRC:
        switch (clckCnfg.status)
        {
        case CLCK_SRC_ENABLED:
            SET_BIT(RCC_REGS.RCC_CR, PLLON);
            while (!GET_BIT(RCC_REGS.RCC_CR, PLLRDY) && timeout--)
                ;
            break;
        case CLCK_SRC_DISABLED:
            CLEAR_BIT(RCC_REGS.RCC_CR, PLLON);
            break;
        default:
            return RCC_ERR_UNDEFINED_VALUE;
        }
        break;

    default:
        return RCC_ERR_UNDEFINED_VALUE;
    }
    if (timeout <= 0)
        return RCC_ERR_TIMEOUT;
    else
    {
        return RCC_OK;
    }
}

ERCCS_Err RCC_SetPLLConfig(PLLCnfg_t pllcnfg)
{
    // set PLLSRC
    SET_BITS(&RCC_REGS.RCC_PLLCFGR, 1, PLLSRC, pllcnfg.PLLSrc);
    // calc rule 1 VCOinput = Pllsrc/m >>    1 < VCOinput < 2  (2 preferrent to limit PLL jitter)
    double pllsrc = (pllcnfg.PLLSrc == PLL_HSE_SRC) ? HES_FREQUANCY : HIS_FREQUANCY;
    // check rule 1
    double VCOinput = pllsrc / pllcnfg.PLLm;
    if (VCOinput > 2000000UL || VCOinput < 1000000UL)
        return RCC_ERR_PLL_Wrong_Configuration;
    // set PLLM
    switch (pllcnfg.PLLm)
    {
    case PLL_M_MIN ... PLL_M_MAX:
        SET_BITS(&RCC_REGS.RCC_PLLCFGR, 6, PLLM, pllcnfg.PLLm);
        break;
    default:
        return RCC_ERR_PLL_M_OUT_OF_RANGE;
    }
    // set PLLN rule2
    switch (pllcnfg.PLLn)
    {
    case PLL_N_MIN ... PLL_N_MAX:
        SET_BITS(&RCC_REGS.RCC_PLLCFGR, 9, PLLN, pllcnfg.PLLn);
        break;

    default:
        return RCC_ERR_PLL_N_OUT_OF_RANGE;
    }
    // set PPLP
    switch (pllcnfg.PLLp)
    {
    case PLL_P_2 ... PLL_P_8:
        SET_BITS(&RCC_REGS.RCC_PLLCFGR, 2, PLLP, pllcnfg.PLLp);
        break;

    default:
        return RCC_ERR_PLL_P_OUT_OF_RANGE;
    }
    // set PPLQ
    switch (pllcnfg.PLLq)
    {
    case PLL_Q_2 ... PLL_Q_15:
        SET_BITS(&RCC_REGS.RCC_PLLCFGR, 4, PLLQ, pllcnfg.PLLq);
        break;

    default:
        return RCC_ERR_PLL_Q_OUT_OF_RANGE;
    }
    // check rule 3
    double PLL48ck = (VCOinput / pllcnfg.PLLq) * pllcnfg.PLLn;
    if (PLL48ck != 48000000UL)
    {
        return RCC_ERR_PLL_48_NOT_SET_TO_48;
    }

    return RCC_OK;
}

ERCCS_Err RCC_SetBusPrescaler(EBusSelctor bus, union_BusPrescaler_t prescaler)
{
    ERCCS_Err ret = RCC_OK;
    switch (bus)
    {
    case APB1_BUS:
        SET_BITS(&RCC_REGS.RCC_CFGR, 3, PPRE1, prescaler.APBPrescaler);
        break;
    case APB2_BUS:
        SET_BITS(&RCC_REGS.RCC_CFGR, 3, PPRE2, prescaler.APBPrescaler);
        break;
    case AHB_BUS:
        SET_BITS(&RCC_REGS.RCC_CFGR, 4, HPRE, prescaler.AHBPrescaler);
        break;
    default:
        ret = RCC_ERR_UNDEFINED_VALUE;
        break;
    }
    return ret;
}
ERCCS_Err RCC_CntrlPeripheralClck(rcc_enumPeripheralSelecotr_t peripheral, rcc_enumPeripheralStatus_t status)
{
    ERCCS_Err ret = RCC_OK;
    if (peripheral >= PERIPHERAL_AHB1EN_REG_BASE && peripheral < PERIPHERAL_AHB2EN_REG_BASE)
    {
        // AHB1 peripheral
        uint8_t bitnum = peripheral - PERIPHERAL_AHB1EN_REG_BASE;
        if (bitnum > 31)
        {
            ret = RCC_ERR_UNDEFINED_VALUE;
        }
        switch (status)
        {
        case PERIPHERAL_ENABLED:
            SET_BIT(RCC_REGS.RCC_AHB1ENR, bitnum);
            break;
        case PERIPHERAL_DISABLED:
            CLEAR_BIT(RCC_REGS.RCC_AHB1ENR, bitnum);
            break;
        default:
            ret = RCC_ERR_UNDEFINED_VALUE;
            break;
        }
    }
    else if (peripheral > PERIPHERAL_AHB2EN_REG_BASE && peripheral < PERIPHERAL_APB1EN_REG_BASE)
    {
        // AHB2 peripheral
        uint8_t bitnum = peripheral - PERIPHERAL_AHB2EN_REG_BASE;
        if (bitnum > 31)
        {
            ret = RCC_ERR_UNDEFINED_VALUE;
        }
        switch (status)
        {
        case PERIPHERAL_ENABLED:
            SET_BIT(RCC_REGS.RCC_AHB2ENR, bitnum);
            break;
        case PERIPHERAL_DISABLED:
            CLEAR_BIT(RCC_REGS.RCC_AHB2ENR, bitnum);
            break;
        default:
            ret = RCC_ERR_UNDEFINED_VALUE;
            break;
        }
    }
    else if (peripheral >= PERIPHERAL_APB1EN_REG_BASE && peripheral < PERIPHERAL_APB2EN_REG_BASE)
    {
        // APB1 peripheral
        uint8_t bitnum = peripheral - PERIPHERAL_APB1EN_REG_BASE;
        if (bitnum > 31)
        {
            ret = RCC_ERR_UNDEFINED_VALUE;
        }
        switch (status)
        {
        case PERIPHERAL_ENABLED:
            SET_BIT(RCC_REGS.RCC_APB1ENR, bitnum);
            break;
        case PERIPHERAL_DISABLED:
            CLEAR_BIT(RCC_REGS.RCC_APB1ENR, bitnum);
            break;
        default:
            ret = RCC_ERR_UNDEFINED_VALUE;
            break;
        }
    }
    else if (peripheral >= PERIPHERAL_APB2EN_REG_BASE && peripheral < PERIPHERALS_LIMIT)
    {
        // APB2 peripheral
        uint8_t bitnum = peripheral - PERIPHERAL_APB2EN_REG_BASE;
        if (bitnum > 31)
        {
            ret = RCC_ERR_UNDEFINED_VALUE;
        }
        switch (status)
        {
        case PERIPHERAL_ENABLED:
            SET_BIT(RCC_REGS.RCC_APB2ENR, bitnum);
            break;
        case PERIPHERAL_DISABLED:
            CLEAR_BIT(RCC_REGS.RCC_APB2ENR, bitnum);
            break;
        default:
            ret = RCC_ERR_UNDEFINED_VALUE;
            break;
        }
    }
    else
    {
        ret = RCC_ERR_UNDEFINED_VALUE;
    }

    return ret;
}

int64_t RCC_GetSysClkFreq()
{
    int64_t myfreq = -1;
    ESysClkSrc myClkSrc = RCC_GetSystemClk();
    switch (myClkSrc)
    {
    case SYSCLK_HSE_SRC:
        myfreq = HES_FREQUANCY;
        break;
    case SYSCLK_HSI_SRC:
        myfreq = HIS_FREQUANCY;
        break;
    case SYSCLK_PLL_SRC:
        // calc pll out
        myfreq = RCC_GetPLLFreq();
        break;
    default:
        myfreq = -1;
        break;
    }
    return myfreq;
}
rcc_enumResteCause_t RCC_GetResetCause()
{
    rcc_enumResteCause_t resetCause = 0;
    uint8_t isAllChecked = 0;
    if (GET_BIT(RCC_REGS.RCC_CSR, LPWR_RESET))
    {
        resetCause = LPWR_RESET;
    }
    else if (GET_BIT(RCC_REGS.RCC_CSR, WWDG_RESET))
    {
        resetCause = WWDG_RESET;
    }
    else if (GET_BIT(RCC_REGS.RCC_CSR, IWDG_RESET))
    {
        resetCause = IWDG_RESET;
    }
    else if (GET_BIT(RCC_REGS.RCC_CSR, SFT_RESET))
    {
        resetCause = SFT_RESET;
    }
    else if (GET_BIT(RCC_REGS.RCC_CSR, POR_RESET))
    {
        resetCause = POR_RESET;
    }
    else if (GET_BIT(RCC_REGS.RCC_CSR, PIN_RESET))
    {
        resetCause = PIN_RESET;
    }
    else if (GET_BIT(RCC_REGS.RCC_CSR, BOR_RESET) || (isAllChecked++))
    {
        isAllChecked++;
        resetCause = BOR_RESET;
    }
    // if all reset causes checked reset all flags
    if (isAllChecked)
    {
        SET_BIT(RCC_REGS.RCC_CSR, RMVF);
    }
    return resetCause;
}
EClkSrcStatus RCC_GetClckSrcStatus(ESysClkSrc src)
{
    EClkSrcStatus ret = -1;
    switch (src)
    {
    case SYSCLK_HSE_SRC:
        ret = (GET_BIT(RCC_REGS.RCC_CSR, HSERDY) == 0) ? CLCK_SRC_NOT_READY : CLCK_SRC_READY;
        break;
    case SYSCLK_HSI_SRC:
        ret = (GET_BIT(RCC_REGS.RCC_CSR, HSIRDY) == 0) ? CLCK_SRC_NOT_READY : CLCK_SRC_READY;
        break;
    case SYSCLK_PLL_SRC:
        ret = (GET_BIT(RCC_REGS.RCC_CSR, PLLRDY) == 0) ? CLCK_SRC_NOT_READY : CLCK_SRC_READY;
        break;
    default:
        ret = -1;
        break;
    }
    return ret;
}
ESysClkSrc RCC_GetSystemClk()
{
    ESysClkSrc ret = GET_BITS(RCC_REGS.RCC_CFGR, MASK_2BIT, 2);
    return ret;
}

// private functions
static int64_t RCC_GetPLLFreq()
{
    int64_t pllfreq = -1;
    PLLCnfg_t myPllCnfg;
    myPllCnfg.PLLSrc = GET_BITS(RCC_REGS.RCC_PLLCFGR, MASK_1BIT, 22);
    myPllCnfg.PLLm = GET_BITS(RCC_REGS.RCC_PLLCFGR, MASK_6BIT, 0);
    myPllCnfg.PLLn = GET_BITS(RCC_REGS.RCC_PLLCFGR, MASK_9BIT, 6);
    myPllCnfg.PLLp = GET_BITS(RCC_REGS.RCC_PLLCFGR, MASK_2BIT, 16);
    myPllCnfg.PLLq = GET_BITS(RCC_REGS.RCC_PLLCFGR, MASK_4BIT, 24);
    switch (myPllCnfg.PLLSrc)
    {
    case PLL_HSE_SRC:
        pllfreq = HES_FREQUANCY;
        break;
    case PLL_HSI_SRC:
        pllfreq = HIS_FREQUANCY;
        break;
    default:
        pllfreq = -1;
    }
    pllfreq /= myPllCnfg.PLLm;
    pllfreq *= myPllCnfg.PLLn;
    switch (myPllCnfg.PLLp)
    {
    case PLL_P_2:
        pllfreq /= 2;
        break;

    case PLL_P_4:
        pllfreq /= 4;
        break;

    case PLL_P_6:
        pllfreq /= 6;
        break;

    case PLL_P_8:
        pllfreq /= 8;
        break;

    default:
        pllfreq = -1;
        break;
    }
    return pllfreq;
}
