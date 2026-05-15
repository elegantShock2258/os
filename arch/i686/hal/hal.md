# hal.md

## Directory: arch/i686/hal

This directory contains the Hardware Abstraction Layer for the 32-bit x86 architecture. It serves as the bridge between generic kernel operations and hardware-specific implementations.

### Modules
- `hal.c` / `hal.h`: Main controller for initializing all lower-level hardware structures. `hal_init()` handles calling initialization functions for GDT, IDT, ISRs, and IRQs.
- **GDT** (Global Descriptor Table): Handled in `gdt/gdt.md`. Sets up memory segmentation for kernel and userland.
- **Interrupts**: Handled in `interrupts/interrupts.md`. Manages CPU exceptions and external hardware interrupts.
- **I/O**: Handled in `io/io.md`. Controls serial debug output and standard I/O (printf).
- **Memory & Paging**: Handled in `memory/memory.md` and `paging/paging.md`.
