#include <stdio.h>
#include "../lib/MCAL/RCC_driver/rcc.h"
// #include "../lib/MCAL/GPIO_driver/gpio.h"
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
typedef struct main
{
    HLED_LEDs_t theLed;
    uint8_t intens;
    HLED_State_t state;
    uint32_t blinktime;
} PWM_LED;
typedef enum
{
    Pwm_testled_0,
    Pwm_testled_1,
    Pwm_testled_2,
    Pwm_testled_3,
    Pwm_testled_4,
    Pwm_testled_5,
    Pwm_testled_6,
    Pwm_testled_7,
    C13_LED,

    num_of_pwm_leds

} PWM_LEDs_enum;
PWM_LED PWM_LEDS[num_of_pwm_leds] = {
    [Pwm_testled_0] = {
        .theLed = tst_led0,
        .intens = 9,
        .state = HLED_ON,
        .blinktime = 0},
    [Pwm_testled_1] = {.theLed = tst_led1, .intens =9, .state = HLED_ON, .blinktime = 0},
    [Pwm_testled_2] = {.theLed = tst_led2, .intens =9, .state = HLED_ON, .blinktime = 0},
    [Pwm_testled_3] = {.theLed = tst_led3, .intens =9, .state = HLED_ON, .blinktime = 0},
    [Pwm_testled_4] = {.theLed = tst_led4, .intens =9, .state = HLED_ON, .blinktime = 0},
    [Pwm_testled_5] = {.theLed = tst_led5, .intens =9, .state = HLED_ON, .blinktime = 0},
    [Pwm_testled_6] = {.theLed = tst_led6, .intens =9, .state = HLED_ON, .blinktime = 0},
    [Pwm_testled_7] = {.theLed = tst_led7, .intens =9, .state = HLED_ON, .blinktime = 0},
    [C13_LED] = {.theLed = Brake_LED, .intens = 5, .state = HLED_ON, .blinktime = 500},

};

typedef enum
{
    sw_select,
    sw_change
} switchs_t;
uint32_t glob_timeout = 0;
uint8_t glob_curr_select = 0;
typedef enum
{
    select_mode,
    normal_mode
} app_mode_t;
app_mode_t glob_mode = normal_mode;
uint8_t readSwitch(switchs_t sw)
{
    uint8_t res = 0;
    GPIO_enuDigitalState_t currstate;
    static GPIO_enuDigitalState_t sw_select_prev = 0;
    static GPIO_enuDigitalState_t sw_change_prev = 0;
    switch (sw)
    {
    case sw_select:
        GPIO_enuPinRead(GPIO_PORT_B, GPIO_PIN13, &currstate);
        if (currstate == sw_select_prev && currstate == GPIO_DIGITAL_OUTPUT_HIGH)
        {
            res = 1;
        }
        sw_select_prev = currstate;
        break;
    case sw_change:
        GPIO_enuPinRead(GPIO_PORT_B, GPIO_PIN15, &currstate);
        if (currstate == sw_change_prev && currstate == GPIO_DIGITAL_OUTPUT_HIGH)
        {
            res = 1;
        }
        sw_change_prev = currstate;
        break;

    default:
        break;
    }
    return res;
}
void nextLED()
{
    // stop blink
    PWM_LEDS[glob_curr_select].blinktime = 0;
    PWM_LEDS[glob_curr_select].state = HLED_ON;

    glob_curr_select++;
    glob_curr_select %= 8;
    PWM_LEDS[glob_curr_select].blinktime = 500;
}

void changePWM()
{
    PWM_LEDS[glob_curr_select].intens++;
    PWM_LEDS[glob_curr_select].intens %= 11;
}

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
    // RCC_CntrlPeripheralClck(PERIPHERAL_AHB1_GPIOC, PERIPHERAL_ENABLED);
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
    RCC_CntrlPeripheralClck(PERIPHERAL_AHB1_GPIOC, PERIPHERAL_ENABLED);
    RCC_CntrlPeripheralClck(PERIPHERAL_AHB1_GPIOB, PERIPHERAL_ENABLED);

    GPIO_enuPinCfgMode(GPIO_PORT_B, GPIO_PIN13, GPIO_DIGITAL_INPUT);
    GPIO_enuPinCfgOutputType(GPIO_PORT_B, GPIO_PIN13, OUTPUT_STATE_OPEN_DRAIN);
    GPIO_enuPinCfgPUPD(GPIO_PORT_B, GPIO_PIN13, PULL_DOWN);

    GPIO_enuPinCfgMode(GPIO_PORT_B, GPIO_PIN15, GPIO_DIGITAL_INPUT);
    GPIO_enuPinCfgOutputType(GPIO_PORT_B, GPIO_PIN15, OUTPUT_STATE_OPEN_DRAIN);
    GPIO_enuPinCfgPUPD(GPIO_PORT_B, GPIO_PIN15, PULL_DOWN);

    HLED_enuInitLED();
    uint32_t tick = 0, i = 0;
    uint32_t pulsepos = 0;
    while (1)
    {

        tick++;
        pulsepos = tick % 10;
        for (i = 0; i < num_of_pwm_leds; i++)
        {
            // off every 5 ms
            if (pulsepos == 0)
            {
                HLED_enuTurnOffLED(PWM_LEDS[i].theLed);
            }
            // on on the righ pwm
            if (PWM_LEDS[i].state == HLED_ON)
            {
                if (pulsepos == PWM_LEDS[i].intens)
                {
                    HLED_enuTurnOnLED(PWM_LEDS[i].theLed);
                }
            }
            if (PWM_LEDS[i].blinktime > 0)
            {
                if (tick % (2 * PWM_LEDS[i].blinktime) == 0)
                {
                    if (PWM_LEDS[i].state == HLED_ON)
                    {
                        PWM_LEDS[i].state = HLED_OFF;
                    }
                    else
                    {
                        PWM_LEDS[i].state = HLED_ON;
                    }
                }
            }
        }

        // each 200 ms ched switch
        if (tick % 200 == 0)
        {
            glob_timeout++;
            if (readSwitch(sw_select))
            {
                glob_timeout = 0;
                switch (glob_mode)
                {
                case select_mode:
                    // next LED
                    nextLED();
                    break;
                case normal_mode:
                    glob_mode = select_mode;
                    glob_curr_select = 7;
                    nextLED();
                    break;
                }
            }
            if (readSwitch(sw_change))
            {
                if (glob_mode == select_mode)
                {
                    glob_timeout = 0;
                    changePWM();
                }
            }
            if (glob_timeout == 100)
            {
                glob_mode = normal_mode;
                for (i = 0; i < num_of_pwm_leds; i++)
                {
                    PWM_LEDS[i].blinktime = 0;
                    PWM_LEDS[i].state = HLED_ON;

                }
            }
        }

        SysTick_Delay_micro(500); // repeat every 0.5ms
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