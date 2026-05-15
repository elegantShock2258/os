# kernel_utils.c

## Description
Implementation of kernel utilities including bitwise operations and a custom logging function.

## Imports
- [[kernel_utils.h.md]]
- [[printf.c.md]]
- [[types.h.md]]

## Functions
- `int abs(int y)`
- `int max(int a, int b)`
- `int kernel_log(const char *fmt, ...)`
- `bool getNthBit(u32 data, int n)`
- `void setNthBit(u32 *data, int n, bool value)`
- `int popcount(u32 n)`
- `int findFirstUnSetBit(unsigned int n)`
- `void printBinary(u32 n)`
