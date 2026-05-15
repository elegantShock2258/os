# kheap.c

## Description
Implementation of a kernel heap allocator (`kmalloc` and `kfree`) using a simple bitmap array.

## Imports
- [[kheap.h.md]]

## Variables
- `BitMapColumn BitMap[BitMapSize]`
- `u32 heap_start`: Initialized to the end of the kernel section in memory.

## Functions
- `void *kmalloc_primitive(u32 size)`: Dumb bump allocator used before `bitmap_init`.
- `void bitmap_init()`
- `int getContigousBlocks(u32 block, int blocksRequired)`
- `void *kmalloc(u32 size)`: Allocates blocks, saves block count metadata, and returns pointer.
- `void *kfree(void *pointer)`: Frees memory blocks using metadata.
