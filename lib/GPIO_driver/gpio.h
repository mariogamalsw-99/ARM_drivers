#ifndef GPIO_H
#define GPIO_H

//_______________________USER DEFINED TYPES________________________________
// Output States
typedef enum
{
    OUTPUT_STATE_PUSH_PULL,
    OUTPUT_STATE_OPEN_DRAIN,
} GPIO_OutputType_t;
// Pull-up Pull-down internal resistor
typedef enum
{
    NO_PULL_UP_PULL_DOWN,
    PULL_UP,
    PULL_DOWN,
} GPIO_PUPD_t;
// PIN MODE
typedef enum
{
    GPIO_DIGITAL_INPUT,
    GPIO_DIGITAL_OUTPUT,
    GPIO_ALTERNATE_FUNCTION,
    GPIO_ANALOG
} GPIO_Mode_t;
// output speed
typedef enum
{
    GPIO_LOW_SPEED_OUTPUT,
    GPIO_MADIUM_SPEED_OUTPUT,
    GPIO_HIGH_SPEED_OUTPUT,
    GPIO_VERY_HIGH_SPEED_OUTPUT,
} GPIO_OutputSpeed_t;

//_______________________USER INTERFACE________________________________
#endif