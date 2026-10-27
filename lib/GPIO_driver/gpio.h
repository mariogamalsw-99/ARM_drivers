#ifndef GPIO_H
#define GPIO_H

//_______________________USER DEFINED TYPES________________________________
// Output States
typedef enum
{
    OUTPUT_STATE_PUSH_PULL,
    OUTPUT_STATE_OPEN_DRAIN,
} GPIO_enuOutputType_t;
// Pull-up Pull-down internal resistor
typedef enum
{
    NO_PULL_UP_PULL_DOWN,
    PULL_UP,
    PULL_DOWN,
} GPIO_enuPUPD_t;
// PIN MODE
typedef enum
{
    GPIO_DIGITAL_INPUT,
    GPIO_DIGITAL_OUTPUT,
    GPIO_ALTERNATE_FUNCTION,
    GPIO_ANALOG
} GPIO_enuMode_t;
// output speed
typedef enum
{
    GPIO_LOW_SPEED_OUTPUT,
    GPIO_MADIUM_SPEED_OUTPUT,
    GPIO_HIGH_SPEED_OUTPUT,
    GPIO_VERY_HIGH_SPEED_OUTPUT,
} GPIO_enuOutputSpeed_t;
// PORTS
typedef enum
{
    GPIO_PORT_A,
    GPIO_PORT_B,
    GPIO_PORT_C,
    GPIO_PORT_D,
    GPIO_PORT_E,
    GPIO_PORT_H
} GPIO_enuPort_t;
// PINS
typedef enum
{
    GPIO_PIN0 = 0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7,
    GPIO_PIN8,
    GPIO_PIN9,
    GPIO_PIN10,
    GPIO_PIN11,
    GPIO_PIN12,
    GPIO_PIN13,
    GPIO_PIN14,
    GPIO_PIN15
} GPIO_enuPin_t;
// GPIO - DIGITAL OUTPUT
typedef enum
{
    GPIO_DIGITAL_OUTPUT_LOW,
    GPIO_DIGITAL_OUTPUT_HIGH
} GPIO_enuDigitalState_t;
//________________________ERROR CODE ENUM_________________________________
typedef enum
{
    GPIO_ERR,
    GPIO_OK,
    GPIO_ERR_UNDEFINED_VALUE,
} GPIO_enuErrCode_t;
//_______________________USER INTERFACE________________________________
//____Pin level functions_____
GPIO_enuErrCode_t GPIO_enuPinWrite(GPIO_enuPort_t cpy_enuPort, GPIO_enuPin_t cpy_enuPin, GPIO_enuDigitalState_t cpy_enuState);
GPIO_enuErrCode_t GPIO_enuPinRead(GPIO_enuPort_t cpy_enuPort, GPIO_enuPin_t cpy_enuPin, GPIO_enuDigitalState_t *ref_enuStatePtr);
GPIO_enuErrCode_t GPIO_enuPinCfgMode(GPIO_enuPort_t cpy_enuPort, GPIO_enuPin_t cpy_enuPin, GPIO_enuMode_t cpy_enumMode);
GPIO_enuErrCode_t GPIO_enuPinCfgOutputType(GPIO_enuPort_t cpy_enuPort, GPIO_enuPin_t cpy_enuPin, GPIO_enuOutputType_t cpy_enuOutType);
GPIO_enuErrCode_t GPIO_enuPinCfgSpeed(GPIO_enuPort_t cpy_enuPort, GPIO_enuPin_t cpy_enuPin, GPIO_enuOutputSpeed_t cpy_enuSpeed);
GPIO_enuErrCode_t GPIO_enuPinCfgPUPD(GPIO_enuPort_t cpy_enuPort, GPIO_enuPin_t cpy_enuPin, GPIO_enuPUPD_t cpy_enuPUPD);

#endif