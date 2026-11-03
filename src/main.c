#include <stdio.h>
#include "../lib/MCAL/RCC_driver/rcc.h"
//#include "../lib/MCAL/GPIO_driver/gpio.h"
#include "../lib/MCAL/SYSTICK_driver/systick.h"
#include "../lib/HAL/HLED/HLED.h"
#include "bitwise_ops.h"
// #define Cport *((uint32_t *)(0x40020814UL))
// register uint32_t myvar  asm("r7") ;
// __attribute__ ((section(".mysection"),used)) volatile uint64_t blabla3 = 77;
// extern u_int32_t _smysection[];
// extern u_int32_t _emysection[];
// volatile uint8_t blabla4;
// volatile uint8_t blabla5;
// volatile uint8_t blabla6;
// volatile uint8_t blabla7;
// volatile uint64_t blabla;
// volatile uint32_t blabla2;
 int main()
{
//     myvar=0x55;
//     int* ptr = & blabla3;
//     blabla3=55;
//     printf("%d",&blabla3);
//  blabla3++;
//  blabla4++;
//  blabla5++;
//  blabla6++;
//  blabla7++;
//     printf("%d",blabla2);
//     blabla2++;
// ClckSrcCnfg_t myHseCnfg = {.status = CLCK_SRC_ENABLED, .bypass = CLK_HSE_BYPASS};
// RCC_CntrlSysClckSrc(SYSCLK_HSI_SRC, myHseCnfg);
// RCC_GetClckSrcStatus(SYSCLK_HSI_SRC);
// RCC_SelectSysClckSrc(SYSCLK_HSI_SRC);
// union_BusPrescaler_t myprescaler={.AHBPrescaler=BUS_AHB_NO_PRESCALER};
// RCC_SetBusPrescaler(AHB_BUS,myprescaler);
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
    // RCC_CntrlPeripheralClck(PERIPHERAL_AHB1_GPIOB, PERIPHERAL_ENABLED);
    RCC_CntrlPeripheralClck(PERIPHERAL_AHB1_GPIOC, PERIPHERAL_ENABLED);
    // volatile GPIO_enuErrCode_t gpio_status;
    // gpio_status = GPIO_enuPinCfgMode(GPIO_PORT_C, GPIO_PIN13, GPIO_DIGITAL_OUTPUT);
    // gpio_status = GPIO_enuPinCfgOutputType(GPIO_PORT_C, 13, OUTPUT_STATE_PUSH_PULL);
    // gpio_status = GPIO_enuPinCfgPUPD(GPIO_PORT_C, 13, NO_PULL_UP_PULL_DOWN);
    // gpio_status = GPIO_enuPinCfgSpeed(GPIO_PORT_C, 13, GPIO_MADIUM_SPEED_OUTPUT);
    // for (int i = 0; i < 8; i++)
    // {
    //     gpio_status = GPIO_enuPinCfgMode(GPIO_PORT_B, i, GPIO_DIGITAL_OUTPUT);
    //     gpio_status = GPIO_enuPinCfgOutputType(GPIO_PORT_B, i, OUTPUT_STATE_PUSH_PULL);
    //     gpio_status = GPIO_enuPinCfgPUPD(GPIO_PORT_B, i, NO_PULL_UP_PULL_DOWN);
    //     gpio_status = GPIO_enuPinCfgSpeed(GPIO_PORT_B, i, GPIO_MADIUM_SPEED_OUTPUT);
    // }
    // // set B13-15 input
    // for (int i = 13; i < 16; i++)
    // {
    //     gpio_status = GPIO_enuPinCfgMode(GPIO_PORT_B, i, GPIO_DIGITAL_INPUT);
    //     gpio_status = GPIO_enuPinCfgOutputType(GPIO_PORT_B, i, OUTPUT_STATE_OPEN_DRAIN);
    //     gpio_status = GPIO_enuPinCfgPUPD(GPIO_PORT_B, i, PULL_DOWN);
    // }

    // uint32_t x = 1;
    // uint8_t num = 0;
    // uint8_t sw[3] = {0};
    // uint8_t sw_prev[3] = {0};
    // uint8_t leds[3] = {0};
    // uint8_t toggle = 1;
    SysTick_Init();
    HLED_enuInitLED();
    while (1)
    {
        HLED_enuTurnOnLED(Brake_LED);
        SysTick_Delay(1000);
        HLED_enuTurnOffLED(Brake_LED);
        SysTick_Delay(1000);
        // num = 0;
        // GPIO_enuPinRead(GPIO_PORT_B, 13, sw);
        // GPIO_enuPinRead(GPIO_PORT_B, 14, sw + 1);
        // GPIO_enuPinRead(GPIO_PORT_B, 15, sw + 2);

        // for (int j = 0; j < 3; j++)
        // {
        //     leds[j] = 0;
        //     if (sw[j] == sw_prev[j] && sw[j] == 1)
        //     {
        //         leds[j] = 1;
        //     }
        //     sw_prev[j] = sw[j];
        // }

        // for (int i = 0; i < 8; i++)
        // {
        //     gpio_status = GPIO_enuPinWrite(GPIO_PORT_B, i, GPIO_DIGITAL_OUTPUT_LOW);
        // }
        // for (int i = 0; i < 3; i++)
        // {
        //     if (leds[i])
        //     {

        //         gpio_status = GPIO_enuPinWrite(GPIO_PORT_B, i, GPIO_DIGITAL_OUTPUT_HIGH);
        //         gpio_status = GPIO_enuPinWrite(GPIO_PORT_B,5-i, GPIO_DIGITAL_OUTPUT_HIGH);
        //     }
        // }
        // x = 1;
        // while (x < 0x2fffff)
        // {
        //     x++;
        // }
    }
}