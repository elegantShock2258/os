# boot.S

## Description
The initial multiboot-compliant assembly entry point for the kernel. It sets up the stack, multiboot header, and invokes the C kernel entry.

## Constants/Macros
- `ALIGN`, `MEMINFO`, `VIDINFO`, `FLAGS`, `MAGIC`, `CHECKSUM`: Multiboot header magic numbers and flags.

## Functions/Labels
- `_start`: The absolute entry point called by the bootloader. Initializes the stack pointer to `stack_top` and calls `kernel_main`.
