#ifndef BITWISE_OPS
#define  BITWISE_OPS
#include <stdint.h>
/*define helper bitwise operation in function macro */
#define SET_BIT(reg,n)			reg|=(1<<n)
#define CLEAR_BIT(reg,n)		reg&=(~(1<<n))
#define TOOGLE_BIT(reg,n)		reg^=(1<<n)
#define GET_BIT(reg,n)			((reg>>n)&1)
void SET_BITS(volatile uint32_t* reg, uint8_t size, uint8_t offset, uint32_t val)
{
    // create window size
    uint16_t i = 0;
    for (uint8_t j = 0; j < size; j++)
    {
        i <<= 1;
        i += 1;
    }
    // clear the window
    *reg &= (~(i << offset));
    // set val
    *reg |= (val << offset);
}

#define SET_REG(REG)			(REG = 0xffff)
#define CLEAR_REG(REG)			(REG = 0)
#define TOOGLE_REG(REG)			(REG ^= 0xffff)

#endif /* BITWISE_OPS  */