#ifndef BITWISE_OPS
#define BITWISE_OPS
#include <stdint.h>
// enum for masks by 1 size
typedef enum
{
    MASK_1BIT = 0x1,
    MASK_2BIT = 0x3,
    MASK_3BIT = 0x7,
    MASK_4BIT = 0xf,
    MASK_5BIT = 0x1f,
    MASK_6BIT = 0x3f,
    MASK_7BIT = 0x7f,
    MASK_8BIT = 0xff,
    MASK_9BIT = 0x1ff,
    MASK_10BIT = 0x3ff,
    MASK_11BIT = 0x7ff,
    MASK_12BIT = 0xfff,
    MASK_13BIT = 0x1fff,
    MASK_14BIT = 0x3fff,
    MASK_15BIT = 0x7fff,
    MASK_16BIT = 0xffff,
    MASK_17BIT = 0x1ffff,
    MASK_18BIT = 0x3ffff,
    MASK_19BIT = 0x7ffff,
    MASK_20BIT = 0xfffff,
    MASK_21BIT = 0x1fffff,
    MASK_22BIT = 0x3fffff,
    MASK_23BIT = 0x7fffff,
    MASK_24BIT = 0xffffff,
    MASK_25BIT = 0x1ffffff,
    MASK_26BIT = 0x3ffffff,
    MASK_27BIT = 0x7ffffff,
    MASK_28BIT = 0xfffffff,
    MASK_29BIT = 0x1fffffff,
    MASK_30BIT = 0x3fffffff,
    MASK_31BIT = 0x7fffffff,
    MASK_32BIT = 0xffffffff,

} Enum_MASK_t;
/*define helper bitwise operation in function macro */
#define SET_BIT(reg, n) reg |= (1 << n)
#define CLEAR_BIT(reg, n) reg &= (~(1 << n))
#define TOOGLE_BIT(reg, n) reg ^= (1 << n)
#define GET_BIT(reg, n) ((reg >> n) & 1)


void SET_BITS(volatile uint32_t *reg, uint8_t size, uint8_t offset, uint32_t val)
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
uint32_t GET_BITS(volatile const uint32_t *reg, Enum_MASK_t mask, uint8_t offset)
{
    return ((*reg >> offset) & mask);
}

#define SET_REG(REG) (REG = 0xffff)
#define CLEAR_REG(REG) (REG = 0)
#define TOOGLE_REG(REG) (REG ^= 0xffff)

#endif /* BITWISE_OPS  */