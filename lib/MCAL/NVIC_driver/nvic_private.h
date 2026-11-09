#ifndef NVIC_PRIVATE_H
#define NVIC_PRIVATE_H
#include <stdint.h>

#define NVIC_REG_SIZE 32
#define NVIC_NUM_OF_PRIORTY_BITS_ARM 8
#define NVIC_NUM_OF_PRIORTY_BITS_USED 4
#define NVIC_NUM_OF_IRQ_PRIORITY_IN_REG 4
#define NVIC_PRIORTY_BITS_OFFSET (8-NVIC_NUM_OF_PRIORTY_BITS_USED)


//_________________NVIC REGISTERS______________________

#define NVIC_BASE_ADDRESS 0xdff
#define NVIC_ISER_ARR ((volatile uint32_t *)(NVIC_BASE_ADDRESS+0x100))
#define NVIC_ICER_ARR ((volatile uint32_t *)(NVIC_BASE_ADDRESS+0x180))
#define NVIC_ISPR_ARR ((volatile uint32_t *)(NVIC_BASE_ADDRESS+0x200))
#define NVIC_ICPR_ARR ((volatile uint32_t *)(NVIC_BASE_ADDRESS+0x280))
#define NVIC_IABR_ARR ((volatile uint32_t *)(NVIC_BASE_ADDRESS+0x300))
#define NVIC_IPR_ARR ((volatile uint32_t *)(NVIC_BASE_ADDRESS+0x400))
#define NVIC_STIR (*(volatile uint32_t *)(NVIC_BASE_ADDRESS+0xE00))

//_________________NVIC Bits______________________


#endif