#ifndef NVIC_PRIVATE_H
#define NVIC_PRIVATE_H
#include <stdint.h>


static uint32_t glob_uint32VTORValue=0;
#define VECTKEY_MASK 0x05fa0000
#define SYSRESETREQ 2

#define NVIC_REG_SIZE 32
#define NVIC_NUM_OF_PRIORTY_BITS_ARM 8
#define NVIC_NUM_OF_PRIORTY_BITS_USED 4
#define NVIC_NUM_OF_IRQ_PRIORITY_IN_REG 4
#define NVIC_PRIORTY_BITS_OFFSET (8 - NVIC_NUM_OF_PRIORTY_BITS_USED)

//_________________NVIC REGISTERS______________________
#ifdef PC_UNIT_TEST
extern uint32_t NVIC_ISER_ARR_testVar[8];
extern uint32_t NVIC_ICER_ARR_testVar[8];
extern uint32_t NVIC_ISPR_ARR_testVar[8];
extern uint32_t NVIC_ICPR_ARR_testVar[8];
extern uint32_t NVIC_IABR_ARR_testVar[8];
extern uint32_t NVIC_IPR_ARR_testVar[60];
extern uint32_t NVIC_STIR_testVar;
extern uint32_t SCB_VTOR_testVar;
extern uint32_t SCB_AIRCR_testVar;

#define NVIC_ISER_ARR (NVIC_ISER_ARR_testVar)
#define NVIC_ICER_ARR (NVIC_ICER_ARR_testVar)
#define NVIC_ISPR_ARR (NVIC_ISPR_ARR_testVar)
#define NVIC_ICPR_ARR (NVIC_ICPR_ARR_testVar)
#define NVIC_IABR_ARR (NVIC_IABR_ARR_testVar)
#define NVIC_IPR_ARR (NVIC_IPR_ARR_testVar)
#define NVIC_STIR (NVIC_STIR_testVar)
#define SCB_VTOR (SCB_VTOR_testVar)
#define SCB_AIRCR (SCB_AIRCR_testVar)
#else


#define SCB_BASE_ADDRESS 0xE000ED00
#define NVIC_BASE_ADDRESS 0xE000E000
#define SCB_VTOR (*(volatile uint32_t *)(SCB_BASE_ADDRESS + 0x08))
#define SCB_AIRCR (*(volatile uint32_t *)(SCB_BASE_ADDRESS + 0x0c))

#define NVIC_ISER_ARR ((volatile uint32_t *)(NVIC_BASE_ADDRESS + 0x100))
#define NVIC_ICER_ARR ((volatile uint32_t *)(NVIC_BASE_ADDRESS + 0x180))
#define NVIC_ISPR_ARR ((volatile uint32_t *)(NVIC_BASE_ADDRESS + 0x200))
#define NVIC_ICPR_ARR ((volatile uint32_t *)(NVIC_BASE_ADDRESS + 0x280))
#define NVIC_IABR_ARR ((volatile uint32_t *)(NVIC_BASE_ADDRESS + 0x300))
#define NVIC_IPR_ARR ((volatile uint32_t *)(NVIC_BASE_ADDRESS + 0x400))
#define NVIC_STIR (*(volatile uint32_t *)(NVIC_BASE_ADDRESS + 0xF00))
#endif
//_________________NVIC Bits______________________

#endif