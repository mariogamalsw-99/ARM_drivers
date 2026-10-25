#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H
#include "./Helpers/STD_types.h"
/* Private declarations for the RCC driver. */
typedef struct 
{
    u32 RCC_CR;
    u32 RCC_PLLCFGR;
    u32 RCC_CFGR;
    u32 RCC_CIR;
    u32 RCC_AHB1RSTR;
    u32 RCC_AHB2RSTR;
    u32 RESERVED[2];
    u32 RCC_APB1RSTR;
    u32 RCC_APB2RSTR;
    u32 RESERVED1[2];
    u32 RCC_AHB1ENR;
    u32 RCC_AHB2ENR;
    u32 RESERVED2[2];
    u32 RCC_APB1ENR;
    u32 RCC_APB2ENR;
    u32 RESERVED3[2];
    u32 RCC_AHB1LPENR;
    u32 RCC_AHB2LPENR;
    u32 RESERVED4[2];
    u32 RCC_APB1LPENR;
    u32 RCC_APB2LPENR;
    u32 RESERVED5[2];
    u32 RCC_BDCR;
    u32 RCC_CSR;
    u32 RESERVED6[2];
    u32 RCC_SSCGR;
    u32 RCC_PLLI2SCFGR;
    u32 RESERVED7;
    u32 RCC_DCKCFGR;
}RCC_REGS_t;
#define RCC_REGS (*(volatile RCC_REGS_t*)(0x40023800))

#endif /* RCC_PRIVATE_H */
