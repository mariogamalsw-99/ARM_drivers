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
        RCC_REGS.RCC_CFGR &= (0b11 << SW);
        RCC_REGS.RCC_CFGR |= (clkSrc << SW);
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
    ulong pllsrc = (pllcnfg.PLLSrc == PLL_HSE_SRC) ? HES_FREQUANCY : HIS_FREQUANCY;
    // check rule 1
    ulong VCOinput = pllsrc / pllcnfg.PLLm;
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
    // set PLLN
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
ERCCS_Err RCC_CntrlPeripheralClck(rcc_enumPeripheralSelecotr_t peripheral, rss_enumPeripheralStatus_t status)
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
