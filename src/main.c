#include <stdio.h>
#include "../lib/MCAL/RCC_driver/rcc.h"
// #include "../lib/MCAL/GPIO_driver/gpio.h"
#include "../lib/MCAL/SYSTICK_driver/systick.h"
#include "../lib/HAL/HLED/HLED.h"
#include "bitwise_ops.h"
#include "NVIC_driver/nvic.h"
#include "SCHED/SCHED.h"
#include "HSwitch/HSwitch.h"
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
#define NO_ACTION_TIMEOUT 160 // 4sec 4000ms/25ms

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
    [Pwm_testled_1] = {.theLed = tst_led1, .intens = 9, .state = HLED_ON, .blinktime = 0},
    [Pwm_testled_2] = {.theLed = tst_led2, .intens = 9, .state = HLED_ON, .blinktime = 0},
    [Pwm_testled_3] = {.theLed = tst_led3, .intens = 9, .state = HLED_ON, .blinktime = 0},
    [Pwm_testled_4] = {.theLed = tst_led4, .intens = 9, .state = HLED_ON, .blinktime = 0},
    [Pwm_testled_5] = {.theLed = tst_led5, .intens = 9, .state = HLED_ON, .blinktime = 0},
    [Pwm_testled_6] = {.theLed = tst_led6, .intens = 9, .state = HLED_ON, .blinktime = 0},
    [Pwm_testled_7] = {.theLed = tst_led7, .intens = 9, .state = HLED_ON, .blinktime = 0},
    [C13_LED] = {.theLed = Brake_LED, .intens = 5, .state = HLED_ON, .blinktime = 500},

};

typedef enum
{
    sw_select,
    sw_change
} switchs_t;

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
    PWM_LEDS[glob_curr_select].blinktime = 100;
}

void changeUpPWM()
{
    PWM_LEDS[glob_curr_select].intens++;
    PWM_LEDS[glob_curr_select].intens %= 11;
}
void changeDownPWM()
{
    PWM_LEDS[glob_curr_select].intens += (11 - 1);
    PWM_LEDS[glob_curr_select].intens %= 11;
}

void LED_Dimming_task()
{
    static uint32_t tick = 0, i = 0;
    static uint32_t pulsepos = 0;
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
            if (tick % (PWM_LEDS[i].blinktime) == 0)
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
}
void switchesControl_task()
{
    static uint32_t loc_statTimeOut = 0;
    if (loc_statTimeOut <= NO_ACTION_TIMEOUT)
    {
        loc_statTimeOut++;
    }
    HSwitch_State_t loc_enuSwState;
    HSwitch_ErrorCode_t loc_enuSwtichErrcode = HSwitch_enuReadSwitch(Select_SW, &loc_enuSwState);
    // if selecte pressed and this is new state
    if (loc_enuSwState == HSwitch_PRESSED && loc_enuSwtichErrcode == HSwitch_OK_NEW_VAL)
    {
        loc_statTimeOut = 0;
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
    loc_enuSwtichErrcode = HSwitch_enuReadSwitch(Up_SW, &loc_enuSwState);
    if (loc_enuSwState == HSwitch_PRESSED && loc_enuSwtichErrcode == HSwitch_OK_NEW_VAL)
    {
        if (glob_mode == select_mode)
        {
            loc_statTimeOut = 0;
            changeUpPWM();
        }
    }
    loc_enuSwtichErrcode = HSwitch_enuReadSwitch(Down_SW, &loc_enuSwState);
    if (loc_enuSwState == HSwitch_PRESSED && loc_enuSwtichErrcode == HSwitch_OK_NEW_VAL)
    {
        if (glob_mode == select_mode)
        {
            loc_statTimeOut = 0;
            changeDownPWM();
        }
    }
    if (loc_statTimeOut == NO_ACTION_TIMEOUT)
    {
        glob_mode = normal_mode;
        for (int i = 0; i < num_of_pwm_leds-1; i++)
        {
            PWM_LEDS[i].blinktime = 0;
            PWM_LEDS[i].state = HLED_ON;
        }
    }
}

int main()
{
    HLED_enuInitLED();
    HSwitch_enuInitSwitches(1);
    SCHED_init();
    SCHED_Runnable_t LedsTask = {
        .cyclicTimems = 1,
        .delayms = 20,
        .func = LED_Dimming_task,
        .priority = 0};
    SCHED_registerRunnable(&LedsTask);
    SCHED_Runnable_t ControlSwitchesTask = {
        .cyclicTimems = 25,
        .delayms = 21,
        .func = switchesControl_task,
        .priority = 2};
    SCHED_registerRunnable(&LedsTask);
    SCHED_registerRunnable(&ControlSwitchesTask);
    SCHED_start();
    // SysTick_setCallBack(LED_Dimming_task);
    // SysTick_NotifyOnmicros(500);
    // SysTick_Start();
    while (1)
    {

        // SysTick_Delay_micro(500); // repeat every 0.5ms
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