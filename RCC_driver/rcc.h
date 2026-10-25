#ifndef RCC_H
#define RCC_H

/* User interface*/
/*enums*/
//Error status
typedef enum
{ 
    RCC_ERROR,
    RCC_OK,
} ERCCStatus;

typedef enum
{
    SYSCLK_HSI_SRC=0 ,//sw&&sws == 0 
    SYSCLK_HSE_SRC=1 ,//sw&&sws == 1
    SYSCLK_PLL_SRC=2 ,//sw&&sws == 2
}ESysClkSrc;
typedef enum
{
    CLCK_SRC_DISABLED,
    CLCK_SRC_ENABLED
}EClkSrcStatus;
typedef enum
{
    PLL_Q_2=2,
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
}EPLL_Q;
typedef enum
{
    PLL_HSI_SRC,
    PLL_HSE_SRC,
}EPLL_Src;
typedef enum
{
    PLL_P_2=0, // equal values for PLLP[1:0] bits 
    PLL_P_4=1,
    PLL_P_6=2,
    PLL_P_8=3,
}EPLL_P;
typedef enum
{
    PLL_N_MIN=192, 
    PLL_N_MAX=432
}EPLL_N;
typedef enum
{
    PLL_M_MIN=2, 
    PLL_M_MAX=63
}EPLL_M;
/*public functions*/
ERCCStatus RCC_CntrlSysClckSrc(ESysClkSrc,EClkSrcStatus);
ERCCStatus RCC_SelectSysClckSrc(ESysClkSrc);
ERCCStatus RCC_SetPLLConfig();

#endif /* RCC_H */