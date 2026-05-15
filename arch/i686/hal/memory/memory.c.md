# memory.c

## Description
Standard memory manipulation routines like `memcpy`, `memset`, and `memcmp`.

## Imports
- [[memory.h.md]]
- [[kernel_utils.c.md]]

## Functions
- `void *memcpy(void *dst, const void *src, uint32_t num)`
- `void *memset(void *ptr, u32 value, u32 num)`
- `int memcmp(const void *ptr1, const void *ptr2, uint16_t num)`
