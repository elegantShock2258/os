# interrupts.md

## Directory: arch/i686/hal/interrupts

This sub-directory handles all CPU exceptions, hardware interrupts, and associated programmable controllers.

### Core Components
- **IDT (Interrupt Descriptor Table)**: Defines the table that vectors hardware and software interrupts to specific functions (`idt.c`, `idt.h`).
- **ISR (Interrupt Service Routines)**: High-level C handlers mapping directly to CPU exceptions (Divide by zero, Page faults, etc.). It includes a panic dump if the exception is fatal.
- **IRQ (Interrupt Requests)**: Specialized handlers for hardware interrupts like keyboards and mice, bridged using `i686_IRQ_Handler`.
- **PIC (Programmable Interrupt Controller)**: Responsible for multiplexing hardware interrupts and remapping them to avoid collisions with CPU exceptions (offset `0x20`).
- **PIT (Programmable Interval Timer)**: Generates clock ticks on IRQ0 to facilitate time-keeping and the `sleep()` function.
