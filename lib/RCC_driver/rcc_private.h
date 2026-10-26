#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H
#include <stdint.h>
/* Private declarations for the RCC driver. */
typedef struct 
{
    uint32_t RCC_CR;
    uint32_t RCC_PLLCFGR;
    uint32_t RCC_CFGR;
    uint32_t RCC_CIR;
    uint32_t RCC_AHB1RSTR;
    uint32_t RCC_AHB2RSTR;
    uint32_t RESERVED[2];
    uint32_t RCC_APB1RSTR;
    uint32_t RCC_APB2RSTR;
    uint32_t RESERVED1[2];
    uint32_t RCC_AHB1ENR;
    uint32_t RCC_AHB2ENR;
    uint32_t RESERVED2[2];
    uint32_t RCC_APB1ENR;
    uint32_t RCC_APB2ENR;
    uint32_t RESERVED3[2];
    uint32_t RCC_AHB1LPENR;
    uint32_t RCC_AHB2LPENR;
    uint32_t RESERVED4[2];
    uint32_t RCC_APB1LPENR;
    uint32_t RCC_APB2LPENR;
    uint32_t RESERVED5[2];
    uint32_t RCC_BDCR;
    uint32_t RCC_CSR;
    uint32_t RESERVED6[2];
    uint32_t RCC_SSCGR;
    uint32_t RCC_PLLI2SCFGR;
    uint32_t RESERVED7;
    uint32_t RCC_DCKCFGR;
}RCC_REGS_t;
#define RCC_REGS (*(volatile RCC_REGS_t*)(0x40023800))

//bits defines in TCC_CR
#define HSION 0
#define HSIRDY 1
#define HSEON 16
#define HSERDY 17
#define HSEBYP 18
#define PLLON 24
#define PLLRDY 25

//bits defines in RCC_CFGR
#define SW 0
#define SWs 2
#define HPRE 4
#define PPRE1 10
#define PPRE2 13
#define RTCPRE 16
#define MCO1 21
#define MCO1PRE 24
#define MCO2 30
#define MCO2PRE 27

//bits defines in RCC_PLLCFGR
#define PLLSRC 22
#define PLLM 0
#define PLLN 6
#define PLLQ 24
#define PLLP 16
//

#endif /* RCC_PRIVATE_H */
