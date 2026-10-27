#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H
#include <stdint.h>
//_________________GPIO REGISTERS STRUCT______________________
typedef struct 
{
    uint16_t BITSET_REG;
    uint16_t BITRESET_REG;
}GPIO_BSRR_t;

typedef struct
{
    uint32_t GPIOX_MODER;
    uint32_t GPIOX_OTYPER;
    uint32_t GPIOX_OSPEEDER;
    uint32_t GPIOX_PUPDR;
    uint32_t GPIOX_IDR;
    uint32_t GPIOX_ODR;
    GPIO_BSRR_t GPIOX_BSRR;
    uint32_t GPIOX_LCKR;
    uint64_t GPIOX_AFR;
} GPIO_REGS_T;

//_________________GPIO REGISTERS______________________
#define GPIOA_REGS (*(volatile GPIO_REGS_T *)(0X40020000))
#define GPIOB_REGS (*(volatile GPIO_REGS_T *)(0X40020400))
#define GPIOC_REGS (*(volatile GPIO_REGS_T *)(0X40020800))
#define GPIOD_REGS (*(volatile GPIO_REGS_T *)(0X40020C00))
#define GPIOE_REGS (*(volatile GPIO_REGS_T *)(0X40021000))
#define GPIOH_REGS (*(volatile GPIO_REGS_T *)(0X40021C00))

#endif