# C Project Naming Convention

## Summary

Use this table as the quick reference. Select a link in the **Details**
column to jump to the full rule. Every detailed section links back here.

| Category | Rule / item | Short description | Example | Details |
| --- | --- | --- | --- | --- |
| Variables | Local variable | Start with `Loc_`, then optional const marker, type prefix, and name. | `Loc_uint32TimeoutMs` | [Local variables](#local-variables) |
| Variables | Static variable | Start with `Static_`, then optional const marker, type prefix, and name. | `Static_uint8RetryCount` | [Static variables](#static-variables) |
| Variables | Global variable | Start with `Global_`, then optional const marker, type prefix, and name. | `Global_uint32SystemTicks` | [Global variables](#global-variables) |
| Variables | Constant object | Put `cons` immediately before the type prefix. | `Loc_consUint32MaxRetries` | [Constants](#constants) |
| Variables | Function parameter: reference/pointer | Start with `ref_`, then type prefix and name. | `ref_uint8Buffer` | [Function parameters](#function-parameters) |
| Variables | Function parameter: copy/value | Start with `cpy_`, then type prefix and name. | `cpy_uint16BufferSize` | [Function parameters](#function-parameters) |
| Variables | Boolean | Name should read like a condition. | `Loc_boolIsReady` | [Boolean variables](#boolean-variables) |
| Variables | Array / pointer | Use the underlying data type prefix and a purpose-based name. | `Loc_uint8RxBuffer` | [Arrays and pointers](#arrays-and-pointers) |
| Variables | Integer types | Prefix indicates signedness and bit width. | `Loc_int16Offset`, `Loc_uint32Count` | [Type-prefix reference](#type-prefix-reference) |
| Variables | Floating-point types | Use `float32` for `float`, `float64` for `double`. | `Loc_float32VoltageV` | [Type-prefix reference](#type-prefix-reference) |
| Variables | Character | Use `char` as the type prefix. | `Loc_charDelimiter` | [Type-prefix reference](#type-prefix-reference) |
| User-defined types | All user-defined types | Every user-defined type ends with `_t`; use `PascalCase`. | `SensorData_t` | [User-defined types](#user-defined-types) |
| User-defined types | Structure / union type | Type name ends with `_t`. | `SensorReading_t`, `DataWord_t` | [Structures and unions](#structures-and-unions) |
| User-defined types | Enumeration type | Type ends with `_t`; enumerator values are uppercase. | `SensorStatus_t` | [Enumerations](#enumerations) |
| User-defined types | `typedef` alias | Alias ends with `_t`. | `Milliseconds_t` | [Typedef aliases](#typedef-aliases) |
| User-defined type members | Structure / union member | Use type prefix plus descriptive `PascalCase` name; no `Loc_`/`Static_` scope prefix. | `uint16RawValue` | [User-defined type members](#user-defined-type-members) |
| User-defined type members | Enum member / enumerator | Uppercase with underscores; prefix with module or enum name. | `SENSOR_STATUS_READY` | [Enumerations](#enumerations) |
| Functions | Function name | Format: `MODULE_ReturnTypeFunctionName`. | `UART_uint32GetBaudRate()` | [Function names](#function-names) |
| Functions | Void function | Use `void` in the return-type part. | `UART_voidInit()` | [Function names](#function-names) |
| Functions | Function with custom return type | Use a consistent readable token for the return type. | `ADC_ErrorCodeStartConversion()` | [Function names](#function-names) |
| Macros | `#define` | All macro names are uppercase with underscores. | `MAX_BUFFER_SIZE` | [Macros and `#define`](#macros-and-define) |
| Files and modules | Filenames | Use lowercase `snake_case`; keep module names consistent. | `uart_driver.c` | [Files and modules](#files-and-modules) |

------------------------------------------------------------------------

## Variables

[↑ Back to summary](#summary)

### General variable format

Use this general pattern:

`[ScopePrefix]_[ConstMarker][TypePrefix][DescriptiveName]`

-   Scope prefix: `Loc_`, `Static_`, or `Global_` as applicable.
-   Const marker: `cons`, **only for constant objects**, placed
    immediately before the type prefix.
-   Type prefix: identifies the declared data type.
-   Descriptive name: use `PascalCase`, with units included when useful.

Examples: - `Loc_uint32TimeoutMs` - `Loc_consUint32MaxRetries` -
`Static_consFloat32ReferenceVoltageV` - `ref_uint8Buffer`

The name is a convention only; the C declaration determines the actual
type and whether an object is constant.

### Local variables

[↑ Back to summary](#summary)

Local variables declared inside a function start with `Loc_`.

``` c
uint32_t Loc_uint32TimeoutMs;
uint8_t  Loc_uint8RetryCount;
bool     Loc_boolIsReady;
const uint32_t Loc_consUint32MaxRetries = 5U;
```

For constant local objects, place `cons` immediately after `Loc_` and
before the type prefix, as in `Loc_consUint32MaxRetries`.

### Static variables

[↑ Back to summary](#summary)

Static variables start with `Static_`. This applies to file-scope static
variables and function-local static variables.

``` c
static uint8_t Static_uint8RetryCount;
static const uint32_t Static_consUint32TimeoutMs = 1000U;
```

The `static` keyword controls storage duration/linkage; the `Static_`
name prefix does not replace it.

### Global variables

[↑ Back to summary](#summary)

Avoid global variables when practical. If one is required, start its
name with `Global_`.

``` c
uint32_t Global_uint32SystemTicks;
const uint16_t Global_consUint16DeviceId = 42U;
```

Declare shared globals with `extern` in a header and define each object
in exactly one source file. Prefer module APIs over exposing mutable
global state.

### Function parameters

[↑ Back to summary](#summary)

Function parameters start with `ref_` or `cpy_`, followed by the type
prefix and descriptive name.

  ------------------------------------------------------------------------
  Prefix                  Meaning                 Example
  ----------------------- ----------------------- ------------------------
  `ref_`                  Pointer parameter used  `ref_uint8Buffer`
                          to access caller-owned  
                          data; use for           
                          input/output or output  
                          buffers according to    
                          the API                 

  `cpy_`                  Value parameter passed  `cpy_uint16BufferSize`
                          by value, generally     
                          used as an input copy   
  ------------------------------------------------------------------------

``` c
void UART_voidReadData(uint8_t *ref_uint8Buffer,
                       uint16_t cpy_uint16BufferSize);

void GPIO_voidSetPinLevel(bool cpy_boolLevel);
void UART_voidWriteData(const uint8_t *ref_uint8Data,
                        uint16_t cpy_uint16Length);
```

In C, `ref_` is a project naming convention, not a language-level
reference. The pointer declaration and `const` qualifier define what the
function can access or modify.

### Constants

[↑ Back to summary](#summary)

For constant objects declared with `const`, add `cons` immediately
before the type prefix. Keep the scope prefix first.

``` c
const uint32_t Loc_consUint32MaxRetries = 5U;
static const uint32_t Static_consUint32TimeoutMs = 1000U;
```

Use `#define` names in uppercase with underscores for macros; see
[Macros and `#define`](#macros-and-define).

### Arrays and pointers

[↑ Back to summary](#summary)

Use the type prefix for the element or pointed-to type and a name that
describes the purpose.

``` c
uint8_t  Loc_uint8Buffer[RX_BUFFER_SIZE];
uint8_t *ref_uint8PtrData;
uint32_t *Loc_uint32PtrCounters;
const uint8_t *ref_constUInt8PtrData;
```

Use `Buffer`, `Array`, or `Ptr` only when it improves clarity. Avoid
redundant names such as `Loc_uint8BufferArray`.

### Boolean variables

[↑ Back to summary](#summary)

Boolean names should read as a condition, commonly starting with `Is`,
`Has`, `Can`, or `Enable`.

``` c
bool Loc_boolIsConnected;
bool Loc_boolHasError;
bool Loc_boolCanTransmit;
```

------------------------------------------------------------------------

## User-defined types

[↑ Back to summary](#summary)

### General rule

Every project-defined type must end with `_t`. Use `PascalCase` before
the suffix.

Examples: `SensorData_t`, `MotorControl_t`, `ErrorCode_t`.

### Structures and unions

[↑ Back to summary](#summary)

Structure and union type names use `PascalCase` and end with `_t`.

``` c
typedef struct
{
    uint16_t uint16RawValue;
    bool     boolIsValid;
} SensorReading_t;

typedef union
{
    uint32_t uint32Value;
    uint8_t  uint8Bytes[4];
} DataWord_t;
```

### Enumerations

[↑ Back to summary](#summary)

The enum type name ends in `_t` and uses `PascalCase`. All enumerator
names must be uppercase with underscores. Prefix enumerators with the
enum or module name to avoid collisions.

``` c
typedef enum
{
    SENSOR_STATUS_UNINITIALIZED,
    SENSOR_STATUS_READY,
    SENSOR_STATUS_ERROR
} SensorStatus_t;
```

### Typedef aliases

[↑ Back to summary](#summary)

Any project-defined alias created with `typedef` ends with `_t`.

``` c
typedef uint32_t Milliseconds_t;
typedef int32_t TemperatureCelsius_t;
```

Avoid aliases that hide important properties such as signedness, units,
or ownership.

### User-defined type members

[↑ Back to summary](#summary)

Structure and union members are **not local variables**, so do not add
`Loc_`, `Static_`, or `Global_`. Use the type prefix followed by a
descriptive `PascalCase` name.

``` c
typedef struct
{
    uint16_t uint16RawValue;
    bool     boolIsValid;
    uint32_t uint32TimestampMs;
} SensorReading_t;
```

Rules: - Start each member name with the type prefix matching its
declared type. - Do not add `cons` solely because a member is read-only
in a particular function; `const` is applied to objects/pointers in
declarations, not as a general member naming marker. - Enum members
follow the separate uppercase rule in [Enumerations](#enumerations). -
Use meaningful names and include units where helpful, such as
`uint32TimestampMs`.

------------------------------------------------------------------------

## Functions

[↑ Back to summary](#summary)

### Function names

[↑ Back to summary](#summary)

Use this format:

`[MODULE]_[ReturnType][FunctionName]`

-   `MODULE`: uppercase module identifier, such as `UART`, `GPIO`, or
    `ADC`.
-   `ReturnType`: agreed type token, such as `void`, `bool`, `uint8`,
    `uint32`, or a custom type token.
-   `FunctionName`: descriptive `PascalCase` name, preferably beginning
    with a verb.

``` c
void        UART_voidInit(void);
uint32_t    UART_uint32GetBaudRate(void);
bool        GPIO_boolIsPinHigh(uint8_t cpy_uint8Pin);
ErrorCode_t ADC_ErrorCodeStartConversion(void);
```

Use the same return-type token consistently across the project. The
function name should describe the action or result.

### Public and private functions

[↑ Back to summary](#summary)

Declare public functions in the module header. Functions used only
inside one `.c` file should be declared `static`, while still following
the module naming format.

``` c
static uint8_t UART_uint8CalculateChecksum(const uint8_t *ref_uint8Data,
                                          uint16_t cpy_uint16Length);
```

### Function parameter and return rules

[↑ Back to summary](#summary)

-   Use `(void)` for a function that takes no arguments:
    `UART_voidInit(void)`.
-   The return-type token must match the actual C return type.
-   Use `const` on input pointers when the function must not modify the
    pointed-to data.
-   Use status or error return types consistently for operations that
    can fail.

------------------------------------------------------------------------

## Macros and `#define`

[↑ Back to summary](#summary)

All names introduced by `#define` must be uppercase with words separated
by underscores. This includes constants, function-like macros, and
include guards.

``` c
#define MAX_BUFFER_SIZE       128U
#define UART_DEFAULT_BAUDRATE 115200U
#define BIT_MASK(position)    (1UL << (position))
```

Use parentheses around macro arguments and the full expression in
function-like macros. Do not add a trailing semicolon to a macro
definition. Prefer `const` objects or enum constants when suitable.

``` c
#ifndef UART_DRIVER_H
#define UART_DRIVER_H

/* Header declarations */

#endif /* UART_DRIVER_H */
```

------------------------------------------------------------------------

## Files and modules

[↑ Back to summary](#summary)

Use lowercase `snake_case` for filenames. Keep module identifiers
consistent across the source file, header file, and public function
names.

Examples: - `uart_driver.c` - `uart_driver.h` - `sensor_manager.c` -
`sensor_manager.h`

Each module should have a clear responsibility. Put public declarations
in the matching header and implementation details in the source file.

------------------------------------------------------------------------

## Type-prefix reference

[↑ Back to summary](#summary)

Use these prefixes consistently. Standard C does not define `uint8_t`
unless the appropriate standard header is included; use `<stdint.h>` for
fixed-width integer types and `<stdbool.h>` for `bool`.

  C type                 Name prefix              Example
  ---------------------- ------------------------ --------------------------------
  `bool`                 `bool`                   `Loc_boolIsReady`
  `char`                 `char`                   `Loc_charDelimiter`
  `signed char`          `schar`                  `Loc_scharTemperature`
  `unsigned char`        `uchar`                  `Loc_ucharByte`
  `int8_t`               `int8`                   `Loc_int8Offset`
  `uint8_t`              `uint8`                  `Loc_uint8RetryCount`
  `int16_t`              `int16`                  `Loc_int16Correction`
  `uint16_t`             `uint16`                 `Loc_uint16Sample`
  `int32_t`              `int32`                  `Loc_int32Position`
  `uint32_t`             `uint32`                 `Loc_uint32TimeoutMs`
  `int64_t`              `int64`                  `Loc_int64Accumulator`
  `uint64_t`             `uint64`                 `Loc_uint64Timestamp`
  `short`                `short`                  `Loc_shortSampleCount`
  `unsigned short`       `ushort`                 `Loc_ushortFlags`
  `int`                  `int`                    `Loc_intErrorCode`
  `unsigned int`         `uint`                   `Loc_uintPacketCount`
  `long`                 `long`                   `Loc_longElapsedTicks`
  `unsigned long`        `ulong`                  `Loc_ulongMask`
  `long long`            `longlong`               `Loc_longlongTotal`
  `unsigned long long`   `ulonglong`              `Loc_ulonglongTotal`
  `float`                `float32`                `Loc_float32VoltageV`
  `double`               `float64`                `Loc_float64CalibrationFactor`
  `long double`          `float128`\*             `Loc_float128PrecisionValue`
  Pointer                pointed-to type prefix   `ref_uint8Buffer`
  Array                  element type prefix      `Loc_uint16Samples`
  Custom type            agreed short token       `Loc_ErrorCodeStatus`

`float128` is a naming token only in this table; C's `long double`
precision and size are implementation-dependent and are not guaranteed
to be 128-bit. Prefer fixed-width integer types in portable embedded
code. If your project uses only fixed-width types, you may omit the
native integer rows from this table.

------------------------------------------------------------------------

## General rules

[↑ Back to summary](#summary)

1.  **Be descriptive:** prefer `Loc_uint32TimeoutMs` over `Loc_uint32T`.
2.  **Include units when useful:** use names such as
    `Loc_uint32TimeoutMs` or `Loc_float32VoltageV`.
3.  **Avoid ambiguous abbreviations:** common technical names such as
    `UART`, `ADC`, and `GPIO` are acceptable.
4.  **Respect case sensitivity:** `UART_voidInit` and `UART_voidINIT`
    are different identifiers.
5.  **Avoid reserved identifiers:** do not create names beginning with
    reserved underscore patterns defined by the C standard.
6.  **Avoid shadowing:** do not reuse an outer-scope name for a
    different object in an inner scope without a clear reason.
7.  **Keep type prefixes accurate:** the declaration is authoritative;
    update the name if the type changes.
8.  **Use unsigned literal suffixes where appropriate:** for example,
    `1000U` or `1UL`.
9.  **Name for purpose:** do not name variables after temporary values
    or implementation accidents.
10. **Be consistent:** agree on type tokens once and apply them across
    the codebase.
11. **Remember:** prefixes improve readability but do not provide type
    safety.
