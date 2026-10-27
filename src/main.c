#include <stdio.h>
#include <rcc.h>
#include <gpio.h>
#include "bitwise_ops.h"
#define Cport *((uint32_t *)(0x40020814UL))
int main()
{
    // RCC_SelectSysClckSrc(SYSCLK_HSE_SRC);
    // ClckSrcCnfg_t myHseCnfg = {.status = CLCK_SRC_ENABLED, .bypass = CLK_HSE_BYPASS};
    // RCC_CntrlSysClckSrc(SYSCLK_HSE_SRC, myHseCnfg);
    // PLLCnfg_t mypllcnfg = {
    //     .PLLSrc = PLL_HSI_SRC,
    //     .PLLm = 16,
    //     .PLLn = 288,
    //     .PLLp = PLL_P_4,  // sysclck72MHz
    //     .PLLq = PLL_Q_6}; // PLL48MHz
    // RCC_SetPLLConfig(mypllcnfg);
    // RCC_CntrlPeripheralClck(PERIPHERAL_AHB1_GPIOC, PERIPHERAL_ENABLED);
    // ClckSrcCnfg_t myPLLCnfg = {.status = CLCK_SRC_ENABLED, .bypass = CLK_HSE_BYPASS};
    // RCC_CntrlSysClckSrc(SYSCLK_PLL_SRC, myPLLCnfg);
    // RCC_GetClckSrcStatus(SYSCLK_PLL_SRC);
    //  RCC_SelectSysClckSrc(SYSCLK_PLL_SRC);
    // RCC_GetSysClkFreq();
    RCC_CntrlPeripheralClck(PERIPHERAL_AHB1_GPIOB, PERIPHERAL_ENABLED);
    RCC_CntrlPeripheralClck(PERIPHERAL_AHB1_GPIOC, PERIPHERAL_ENABLED);
    volatile GPIO_enuErrCode_t gpio_status;
    gpio_status = GPIO_enuPinCfgMode(GPIO_PORT_C, GPIO_PIN13, GPIO_DIGITAL_OUTPUT);
        gpio_status = GPIO_enuPinCfgOutputType(GPIO_PORT_C, 13, OUTPUT_STATE_PUSH_PULL);
        gpio_status = GPIO_enuPinCfgPUPD(GPIO_PORT_C, 13, NO_PULL_UP_PULL_DOWN);
        gpio_status = GPIO_enuPinCfgSpeed(GPIO_PORT_C, 13, GPIO_MADIUM_SPEED_OUTPUT);
    for (int i = 0; i < 8; i++)
    {
        gpio_status = GPIO_enuPinCfgMode(GPIO_PORT_B, i, GPIO_DIGITAL_OUTPUT);
        gpio_status = GPIO_enuPinCfgOutputType(GPIO_PORT_B, i, OUTPUT_STATE_PUSH_PULL);
        gpio_status = GPIO_enuPinCfgPUPD(GPIO_PORT_B, i, NO_PULL_UP_PULL_DOWN);
        gpio_status = GPIO_enuPinCfgSpeed(GPIO_PORT_B, i, GPIO_MADIUM_SPEED_OUTPUT);
    }
    // set B13-15 input
    for (int i = 13; i < 16; i++)
    {
        gpio_status = GPIO_enuPinCfgMode(GPIO_PORT_B, i, GPIO_DIGITAL_INPUT);
        gpio_status = GPIO_enuPinCfgOutputType(GPIO_PORT_B, i, OUTPUT_STATE_OPEN_DRAIN);
        gpio_status = GPIO_enuPinCfgPUPD(GPIO_PORT_B, i, PULL_DOWN);
    }

    uint32_t x = 1;
    uint8_t num = 0;
    uint8_t sw[3] = {0};
    uint8_t sw_prev[3] = {0};
    uint8_t toggle=1;
    while (1)
    {   
        TOOGLE_BIT(toggle,0);
        GPIO_enuPinWrite(GPIO_PORT_C,13,toggle);
        num = 0;
        GPIO_enuPinRead(GPIO_PORT_B, 13, sw);
        GPIO_enuPinRead(GPIO_PORT_B, 14, sw + 1);
        GPIO_enuPinRead(GPIO_PORT_B, 15, sw + 2);

       
            for (int j = 0; j < 3; j++)
            {
                if (sw[j] == sw_prev[j] && sw[j] == 1)
                {
                    num |= (1 << j);
                }
                sw_prev[j] = sw[j];
            }
        

        for (int i = 0; i < 8; i++)
        {
            gpio_status = GPIO_enuPinWrite(GPIO_PORT_B, i, GPIO_DIGITAL_OUTPUT_LOW);
        }
        for (int i = 0; i < num; i++)
        {
            if(num)
            gpio_status = GPIO_enuPinWrite(GPIO_PORT_B, i, GPIO_DIGITAL_OUTPUT_HIGH);
        }
        x = 1;
        while (x < 0x2fffff)
        {
            x++;
        }
    }
}