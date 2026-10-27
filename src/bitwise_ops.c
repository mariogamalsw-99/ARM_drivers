#include "bitwise_ops.h"

void SET_BITS( uint32_t * reg, uint8_t size, uint8_t offset, uint32_t val)
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
