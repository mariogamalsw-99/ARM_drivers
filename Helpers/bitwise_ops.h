#ifndef BITWISE_OPS
#define  BITWISE_OPS
/*define helper bitwise operation in function macro */
#define SET_BIT(reg,n)			reg|=(1<<n)3
#define CLEAR_BIT(reg,n)		reg&=(~(1<<n))
#define TOOGLE_BIT(reg,n)		reg^=(1<<n)
#define GET_BIT(reg,n)			((reg>>n)&1)


#define SET_REG(REG)			(REG = 0xffff)
#define CLEAR_REG(REG)			(REG = 0)
#define TOOGLE_REG(REG)			(REG ^= 0xffff)

#endif /* BITWISE_OPS  */