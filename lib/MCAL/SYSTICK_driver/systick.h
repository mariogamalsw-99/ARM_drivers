#ifndef SYSTICK_H
#define SYSTICK_H
#include<stdint.h>
//_______________________USER DEFINED TYPES________________________________
typedef enum
{
    SYSTICK_ClckSrc_AHB_Prescaler_8,
    SYSTICK_ClckSrc_AHB
}SYSTICK_SysTickClckSrc_t;

typedef void (*funcPtr_t)(void);

//________________________ERROR CODE ENUM_________________________________


//_______________________USER INTERFACE________________________________
void SysTick_Init();
void SysTick_Delay(uint32_t ms);
void SysTick_Delay_micro(uint32_t cpy_Delaymicors);
void SysTick_NotifyOnmicros(uint32_t cpy_uint32Timems);
void SysTick_NotifyOnms(uint32_t cpy_uint32Timems);
void SysTick_Stop();
void SysTick_Start();
void SysTick_setCallBack(funcPtr_t cpy_funcptrCallBack);
#endif