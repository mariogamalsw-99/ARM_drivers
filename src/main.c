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
        .PLLm = 15,
        .PLLn = 200,
        .PLLp = PLL_P_6,
        .PLLq = PLL_Q_13};
    RCC_SetPLLConfig(mypllcnfg);
    RCC_CntrlPeripheralClck(PERIPHERAL_AHB1_GPIOC, PERIPHERAL_ENABLED);
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