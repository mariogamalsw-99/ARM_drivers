#ifndef RCC_H
#define RCC_H
#include <stdint.h>
/* User interface*/
/*enums*/
// Error status
typedef enum
{
    RCC_ERR_ERROR,
    RCC_OK,
    RCC_ERR_UNDEFINED_VALUE,
    RCC_ERR_PLL_Wrong_Configuration,
    RCC_ERR_PLL_M_OUT_OF_RANGE,
    RCC_ERR_PLL_N_OUT_OF_RANGE,
    RCC_ERR_PLL_P_OUT_OF_RANGE,
    RCC_ERR_PLL_Q_OUT_OF_RANGE,
    RCC_ERR_PLL_48_NOT_SET_TO_48,
    RCC_ERR_TIMEOUT
} ERCCS_Err;
// sysclck sources
typedef enum
{
    SYSCLK_HSI_SRC = 0, // sw&&sws == 0
    SYSCLK_HSE_SRC = 1, // sw&&sws == 1
    SYSCLK_PLL_SRC = 2, // sw&&sws == 2
} ESysClkSrc;
// sysclck status
typedef enum
{
    CLCK_SRC_DISABLED,
    CLCK_SRC_ENABLED,
    CLCK_SRC_READY,
    CLCK_SRC_NOT_READY
} EClkSrcStatus;
// HSE bypass ors not
typedef enum
{
    CLK_HSE_RESONATOR,
    CLK_HSE_BYPASS
} EHSEBypass;
// hold status and bypass for HSE
typedef struct
{

    EClkSrcStatus status;
    EHSEBypass bypass;

} ClckSrcCnfg_t;

typedef enum
{
    PLL_Q_2 = 2,
    PLL_Q_3,
    PLL_Q_4,
    PLL_Q_5,
    PLL_Q_6,
    PLL_Q_7,
    PLL_Q_8,
    PLL_Q_9,
    PLL_Q_10,
    PLL_Q_11,
    PLL_Q_12,
    PLL_Q_13,
    PLL_Q_14,
    PLL_Q_15,
} EPLL_Q;
typedef enum
{
    PLL_HSI_SRC,
    PLL_HSE_SRC,
} EPLL_Src;
typedef enum
{
    PLL_P_2 = 0, // equal values for PLLP[1:0] bits
    PLL_P_4 = 1,
    PLL_P_6 = 2,
    PLL_P_8 = 3,
} EPLL_P;
typedef enum
{
    PLL_N_MIN = 192,
    PLL_N_MAX = 432
} EPLL_N;
typedef enum
{
    PLL_M_LESS_THAN_VALID,
    PLL_M_MIN = 2,
    PLL_M_MAX = 63,
    PLL_M_GREATER_THAN_VALID,
} EPLL_M;
typedef struct
{
    EPLL_Src PLLSrc;
    EPLL_Q PLLq;
    EPLL_P PLLp;
    EPLL_N PLLn;
    EPLL_M PLLm;
} PLLCnfg_t;
typedef enum
{
    BUS_APB_NO_PRESCALER,
    BUS_APB_PRESCALER_2 = 4,
    BUS_APB_PRESCALER_4,
    BUS_APB_PRESCALER_8,
    BUS_APB_PRESCALER_16
} EAPBBusPrescaler;
typedef enum
{
    BUS_AHB_NO_PRESCALER,
    BUS_AHB_PRESCALER_2 = 8,
    BUS_AHB_PRESCALER_4,
    BUS_AHB_PRESCALER_8,
    BUS_AHB_PRESCALER_16,
    BUS_AHB_PRESCALER_32,
    BUS_AHB_PRESCALER_64,
    BUS_AHB_PRESCALER_128,
    BUS_AHB_PRESCALER_256,
    BUS_AHB_PRESCALER_512
} EAHBBusPrescaler;
typedef union
{
    EAPBBusPrescaler APBPrescaler;
    EAHBBusPrescaler AHBPrescaler;
} union_BusPrescaler_t;

typedef enum
{
    APB1_BUS,
    APB2_BUS,
    AHB_BUS
} EBusSelctor;

typedef enum
{
    PERIPHERAL_AHB1EN_REG_BASE = 0, ///(peripheral_enum_val - peripheral_en_reg_base) == bit number in reg
    PERIPHERAL_AHB1_GPIOA = 0,      // bit0
    PERIPHERAL_AHB1_GPIOB,          // bit1
    PERIPHERAL_AHB1_GPIOC,          // bit2
    PERIPHERAL_AHB1_GPIOD,          // bit3
    PERIPHERAL_AHB1_GPIOE,          // bit4
    PERIPHERAL_AHB1_GPIOH = 7,      // bit7
    PERIPHERAL_AHB1_CRC = 12,       // bit12
    PERIPHERAL_AHB1_DMA1 = 21,      // bit21
    PERIPHERAL_AHB1_DMA2 = 22,      // bit22
    PERIPHERAL_AHB2EN_REG_BASE = 30,
    PERIPHERAL_AHB2_OTGFS = 30 + 7,  // bit7
    PERIPHERAL_APB1EN_REG_BASE = 40, // BASE
    PERIPHERAL_APB1_TIM2 = 40 + 0,
    PERIPHERAL_APB1_TIM3,
    PERIPHERAL_APB1_TIM4,
    PERIPHERAL_APB1_TIM5,
    PERIPHERAL_APB1_WWDG = 40 + 11,
    PERIPHERAL_APB1_SPI2 = 40 + 14,
    PERIPHERAL_APB1_SPI3 = 40 + 15,
    PERIPHERAL_APB1_USART2 = 40 + 17,
    PERIPHERAL_APB1_I2C1 = 40 + 21,
    PERIPHERAL_APB1_I2C2 = 40 + 22,
    PERIPHERAL_APB1_I2C3 = 40 + 23,
    PERIPHERAL_APB1_PWR = 40 + 28,
    PERIPHERAL_APB2EN_REG_BASE = 70, // BASE
    PERIPHERAL_APB2_TIM1 = 70 + 0,
    PERIPHERAL_APB2_USART1 = 70 + 4,
    PERIPHERAL_APB2_USART6 = 70 + 5,
    PERIPHERAL_APB2_ADC1 = 70 + 8,
    PERIPHERAL_APB2_SDIO = 70 + 11,
    PERIPHERAL_APB2_SPI1 = 70 + 12,
    PERIPHERAL_APB2_SPI4 = 70 + 13,
    PERIPHERAL_APB2_SYSCFG = 70 + 14,
    PERIPHERAL_APB2_TIM9 = 70 + 16,
    PERIPHERAL_APB2_TIM10 = 70 + 17,
    PERIPHERAL_APB2_TIM11 = 70 + 18,
    PERIPHERALS_LIMIT // END OF PERIPHERALS
} rcc_enumPeripheralSelecotr_t;
typedef enum
{
    PERIPHERAL_ENABLED,
    PERIPHERAL_DISABLED
} rcc_enumPeripheralStatus_t;
typedef enum
{
    BOR_RESET=25,
    PIN_RESET,
    POR_RESET,
    SFT_RESET,
    IWDG_RESET,
    WWDG_RESET,
    LPWR_RESET,
} rcc_enumResteCause_t;

/*public functions*/
ERCCS_Err RCC_SelectSysClckSrc(ESysClkSrc);
ERCCS_Err RCC_CntrlSysClckSrc(ESysClkSrc, ClckSrcCnfg_t);
ERCCS_Err RCC_SetPLLConfig(PLLCnfg_t);
ERCCS_Err RCC_SetBusPrescaler(EBusSelctor, union_BusPrescaler_t);
ERCCS_Err RCC_CntrlPeripheralClck(rcc_enumPeripheralSelecotr_t, rcc_enumPeripheralStatus_t);
int64_t RCC_GetSysClkFreq();
rcc_enumResteCause_t RCC_GetResetCause();
EClkSrcStatus RCC_GetClckSrcStatus(ESysClkSrc);
ESysClkSrc RCC_GetSystemClk(); 
#endif /* RCC_H */