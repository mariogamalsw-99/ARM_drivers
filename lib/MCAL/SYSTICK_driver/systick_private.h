#ifndef SYSTICK_PRIVATE_H
#define SYSTICK_PRIVATE_H
#include <stdint.h>

#define SYSTICK_RELOD_VALUE_MAX 0x00FFFFFF
//_________________SYSTICK REGISTERS______________________
#define STK_CTRL (*(volatile uint32_t *)(0xE000E010))
#define STK_LOAD (*(volatile uint32_t *)(0xE000E014))
#define STK_VAL (*(volatile uint32_t *)(0xE000E018))
#define STK_CALIB (*(volatile uint32_t *)(0xE000E01c))
//_________________SYSTICK Bits______________________
#define COUNTFLAG_BIT 16
#define CLKSOURCE_BIT 2
#define TICKINT_BIT 1
#define ENABLE_BIT 0

#endif