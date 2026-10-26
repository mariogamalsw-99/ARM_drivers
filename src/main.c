#include <stdio.h>
#include <rcc.h>
#define Cport *((uint32_t *)(0x40020814UL))
int main()
{
    RCC_SelectSysClckSrc(SYSCLK_HSE_SRC);
    ClckSrcCnfg_t myHseCnfg = {.status = CLCK_SRC_ENABLED, .bypass = CLK_HSE_BYPASS};
    RCC_CntrlSysClckSrc(SYSCLK_HSE_SRC, myHseCnfg);
    PLLCnfg_t mypllcnfg = {
        .PLLSrc = PLL_HSI_SRC,
        .PLLm = 16,
        .PLLn = 288,
        .PLLp = PLL_P_4,  // sysclck72MHz
        .PLLq = PLL_Q_6}; // PLL48MHz
    RCC_SetPLLConfig(mypllcnfg);
    RCC_CntrlPeripheralClck(PERIPHERAL_AHB1_GPIOC, PERIPHERAL_ENABLED);
    ClckSrcCnfg_t myPLLCnfg = {.status = CLCK_SRC_ENABLED, .bypass = CLK_HSE_BYPASS};
    RCC_CntrlSysClckSrc(SYSCLK_PLL_SRC, myPLLCnfg);
    RCC_GetClckSrcStatus(SYSCLK_PLL_SRC);
     RCC_SelectSysClckSrc(SYSCLK_PLL_SRC);
    RCC_GetSysClkFreq();
    while (1)
    {
        uint32_t x = 1;
        Cport ^= 0xffffffff;
        while (x < 0x2fffff)
        {
            x++;
        }
    }
}