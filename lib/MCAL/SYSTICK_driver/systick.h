#ifndef SYSTICK_H
#define SYSTICK_H
#include<stdint.h>
//_______________________USER DEFINED TYPES________________________________
typedef enum
{
    SYSTICK_ClckSrc_AHB_Prescaler_8,
    SYSTICK_ClckSrc_AHB
}SYSTICK_SysTickClckSrc_t;

//________________________ERROR CODE ENUM_________________________________


//_______________________USER INTERFACE________________________________
void SysTick_Init();
void SysTick_Delay(uint32_t ms);

#endif