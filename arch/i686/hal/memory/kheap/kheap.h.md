# kheap.h

## Description
Header for a bitmap-based kernel heap allocator.

## Imports
- [[kernel_utils.c.md]]
- [[memory.c.md]]

## Types
- `bitColumn`, `BitMapColumn`

## Functions
- `void *kmalloc(u32 size)`
- `void *kmalloc_page()`
