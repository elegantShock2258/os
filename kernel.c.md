# kernel.c

## Description
Handles the primary initialization of the kernel and hardware abstraction layer (HAL) before jumping into the main loop.

## Imports
- [[multiboot.h.md]]
- [[hal.c.md]]
- [[kheap.c.md]]
- [[paging.c.md]]
- [[drivers.c.md]]
- [[main.c.md]]

## Functions
- `void init(unsigned long ebx)`: Calls the HAL initialization, driver initialization, sets up paging, and initializes the bitmap allocator.
- `void kernel_main(unsigned long ebx)`: The C entry point called from the bootloader assembly. Calls `init()` and then `main()`.
