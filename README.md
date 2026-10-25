# C Naming Convention

Use these naming rules for C code in this repository. Names should make the
role and ownership of each declaration clear and should follow the existing
module-based structure.

## Types and members

| Declaration | Convention | Example |
| --- | --- | --- |
| Struct types | `TitleCase` | `ClockConfig` |
| Struct members | `lower_case` or `lowerCase` | `source_clock` |
| Enum types | `ETitleCase` | `EClockStatus` |
| Enum members | `ALL_CAPS` or `lowerCase` | `CLOCK_READY` |

Choose one member style per type and use it consistently.

## Functions

| Function | Convention | Example |
| --- | --- | --- |
| Public functions | `pfx_TitleCase`, using a two- or three-letter module prefix | `RCC_Init` |
| Private functions | `TitleCase` | `WaitForClock` |

Keep private functions file-local with `static` when they are defined in a
`.c` file. Use the module prefix for public functions to make their ownership
clear.

## Variables and macros

| Name | Convention | Example |
| --- | --- | --- |
| Trivial loop or temporary variables | Short names such as `i`, `x`, `n`, or `f` | `i` |
| Local variables | `lower_case` or `lowerCase` | `clock_source` |
| Global variables | `g_lowerCase` or `g_lower_case` | `g_systemClock` |
| Macros | `ALL_CAPS`, with words separated by underscores | `SET_BIT` |

Prefer descriptive local names unless a variable is genuinely trivial.
Avoid global variables when a local variable or function parameter is suitable.

## Files and header guards

Use lowercase file names, separating words with underscores. Name files for
their module and purpose, for example `rcc.c`, `rcc_private.h`, and `rcc_cfg.h`.
Header guards should be uppercase and derived from the file name, for example:

```c
#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

/* Declarations */

#endif /* RCC_PRIVATE_H */
```

## Example

```c
typedef struct
{
    unsigned int clock_source;
} ClockConfig;

typedef enum
{
    CLOCK_READY,
    CLOCK_ERROR
} EClockStatus;

EClockStatus RCC_Init(const ClockConfig *config);

static void WaitForClock(void);
```
