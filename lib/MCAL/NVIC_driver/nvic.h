#ifndef NVIC_H
#define NVIC_H
#include <stdint.h>
//_______________________USER DEFINED TYPES________________________________
typedef enum
{
    NVIC_IRQn_WWDG = 0,
    NVIC_IRQn_EXTI16_PVD = 1,
    NVIC_IRQn_EXTI21_TAMP_STAMP = 2,
    NVIC_IRQn_EXTI22_RTC_WKUP = 3,
    NVIC_IRQn_FLASH = 4,
    NVIC_IRQn_RCC = 5,
    NVIC_IRQn_EXTI0 = 6,
    NVIC_IRQn_EXTI1 = 7,
    NVIC_IRQn_EXTI2 = 8,
    NVIC_IRQn_EXTI3 = 9,
    NVIC_IRQn_EXTI4 = 10,
    NVIC_IRQn_DMA1_Stream0 = 11,
    NVIC_IRQn_DMA1_Stream1 = 12,
    NVIC_IRQn_DMA1_Stream2 = 13,
    NVIC_IRQn_DMA1_Stream3 = 14,
    NVIC_IRQn_DMA1_Stream4 = 15,
    NVIC_IRQn_DMA1_Stream5 = 16,
    NVIC_IRQn_DMA1_Stream6 = 17,
    NVIC_IRQn_ADC = 18,
    /* Reserved IRQs */
    NVIC_IRQn_RESERVED_19 = 19,
    NVIC_IRQn_RESERVED_20 = 20,
    NVIC_IRQn_RESERVED_21 = 21,
    NVIC_IRQn_RESERVED_22 = 22,
    NVIC_IRQn_EXTI9_5 = 23,
    NVIC_IRQn_TIM1_BRK_TIM9 = 24,
    NVIC_IRQn_TIM1_UP_TIM10 = 25,
    NVIC_IRQn_TIM1_TRG_COM_TIM11 = 26,
    NVIC_IRQn_TIM1_CC = 27,
    NVIC_IRQn_TIM2 = 28,
    NVIC_IRQn_TIM3 = 29,
    NVIC_IRQn_TIM4 = 30,
    NVIC_IRQn_I2C1_EV = 31,
    NVIC_IRQn_I2C1_ER = 32,
    NVIC_IRQn_I2C2_EV = 33,
    NVIC_IRQn_I2C2_ER = 34,
    NVIC_IRQn_SPI1 = 35,
    NVIC_IRQn_SPI2 = 36,
    NVIC_IRQn_USART1 = 37,
    NVIC_IRQn_USART2 = 38,
    NVIC_IRQn_EXTI15_10 = 40,
    NVIC_IRQn_RTC_Alarm = 41,
    NVIC_IRQn_EXTI17 = 41,
    NVIC_IRQn_OTG_FS_WKUP = 42,
    NVIC_IRQn_EXTI18 = 42,
    /* Reserved IRQs */
    NVIC_IRQn_RESERVED_43 = 43,
    NVIC_IRQn_RESERVED_44 = 44,
    NVIC_IRQn_RESERVED_45 = 45,
    NVIC_IRQn_RESERVED_46 = 46,
    NVIC_IRQn_DMA1_Stream7 = 47,
    NVIC_IRQn_RESERVED_48 = 48,
    NVIC_IRQn_SDIO = 49,
    NVIC_IRQn_TIM5 = 50,
    NVIC_IRQn_SPI3 = 51,
    /* Reserved IRQs */
    NVIC_IRQn_RESERVED_52 = 52,
    NVIC_IRQn_RESERVED_53 = 53,
    NVIC_IRQn_RESERVED_54 = 54,
    NVIC_IRQn_RESERVED_55 = 55,
    NVIC_IRQn_DMA2_Stream0 = 56,
    NVIC_IRQn_DMA2_Stream1 = 57,
    NVIC_IRQn_DMA2_Stream2 = 58,
    NVIC_IRQn_DMA2_Stream3 = 59,
    NVIC_IRQn_DMA2_Stream4 = 60,
    /* Reserved IRQs */
    NVIC_IRQn_RESERVED_61 = 61,
    NVIC_IRQn_RESERVED_62 = 62,
    NVIC_IRQn_RESERVED_63 = 63,
    NVIC_IRQn_RESERVED_64 = 64,
    NVIC_IRQn_RESERVED_65 = 65,
    NVIC_IRQn_RESERVED_66 = 66,
    NVIC_IRQn_OTG_FS = 67,
    NVIC_IRQn_DMA2_Stream5 = 68,
    NVIC_IRQn_DMA2_Stream6 = 69,
    NVIC_IRQn_DMA2_Stream7 = 70,
    NVIC_IRQn_USART6 = 71,
    NVIC_IRQn_I2C3_EV = 72,
    NVIC_IRQn_I2C3_ER = 73,
    /* Reserved IRQs */
    NVIC_IRQn_RESERVED_74 = 74,
    NVIC_IRQn_RESERVED_75 = 75,
    NVIC_IRQn_RESERVED_76 = 76,
    NVIC_IRQn_RESERVED_77 = 77,
    NVIC_IRQn_RESERVED_78 = 78,
    NVIC_IRQn_RESERVED_79 = 79,
    NVIC_IRQn_RESERVED_80 = 80,
    NVIC_IRQn_FPU = 81,
    /* Reserved IRQs */
    NVIC_IRQn_RESERVED_82 = 82,
    NVIC_IRQn_RESERVED_83 = 83,
    NVIC_IRQn_SPI4 = 84

} NVIC_enuIRQn_t;
typedef enum
{
    NVIC_IRQ_IS_NOT_PENDING ,
    NVIC_IRQ_IS_PENDING ,
}NVIC_enuPendingState_t;
typedef enum
{
    NVIC_IRQ_IS_NOT_ACTIVE ,
    NVIC_IRQ_IS_ACTIVE ,
}NVIC_enuActiveState_t;
//________________________ERROR CODE ENUM_________________________________
typedef enum
{
    NVIC_ERR,
    NVIC_OK,
    NVIC_INVALID_IRQ_ERR,


} NVIC_enuErrCode_t;

//_______________________USER INTERFACE________________________________
/**
 * Set the priority grouping
 */
NVIC_enuErrCode_t NVIC_SetPriorityGrouping(uint32_t priority_grouping);
/**
 * Enable IRQn
 */
NVIC_enuErrCode_t NVIC_EnableIRQ(NVIC_enuIRQn_t IRQn);
/**
 * Disable IRQn
 */
NVIC_enuErrCode_t NVIC_DisableIRQ(NVIC_enuIRQn_t IRQn);
/**
 * Return true (IRQ-Number) if IRQn is
pending
 */
NVIC_enuErrCode_t NVIC_GetPendingIRQ(NVIC_enuIRQn_t IRQn);
/**
 * Set IRQn pending
 */
NVIC_enuErrCode_t NVIC_SetPendingIRQ(NVIC_enuIRQn_t IRQn);
/**
 * Clear IRQn pending status
 */
NVIC_enuErrCode_t NVIC_ClearPendingIRQ(NVIC_enuIRQn_t IRQn);
/**
 * Return the IRQ number of the active interrupt
 */
NVIC_enuErrCode_t NVIC_GetActive(NVIC_enuIRQn_t IRQn);
/**
 * Set priority for IRQn
 */
NVIC_enuErrCode_t NVIC_SetPriority(NVIC_enuIRQn_t IRQn, uint32_t priority);
/**
 * Read priority of IRQn
 */
NVIC_enuErrCode_t NVIC_GetPriority(NVIC_enuIRQn_t IRQn);
/**
 * Reset the system
 */
void NVIC_SystemReset(void);

#endif