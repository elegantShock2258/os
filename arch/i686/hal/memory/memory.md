# memory.md

## Directory: arch/i686/hal/memory & paging

Handles dynamic memory allocation and x86 virtual-to-physical address translation.

### Sub-Modules
- **Paging**: `paging.c` and `paging.h` handle the setup of the Page Directory Pointer Table (PDPT) and Page Directory (PD). It enables PAE (Physical Address Extension) for 32-bit architecture and allows the kernel to map virtual memory using `paging_map_virtual_to_phys`.
- **KHeap**: A bitmap-based heap allocator (`kheap.c`). It allocates memory chunks via `kmalloc` and uses a BitMap structure to track free/busy states. Includes an early-boot primitive allocator before the bitmap is fully set up.
- **Memory Operations**: `memory.c` provides fast implementations for standard library equivalents such as `memcpy`, `memset`, and `memcmp`.
