# hal.c

## Description
Hardware Abstraction Layer (HAL) initialization for the i686 architecture.

## Imports
- [[hal.h.md]]
- [[gdt.c.md]]
- [[idt.c.md]]
- [[irq.c.md]]
- [[isr.c.md]]
- [[printf.c.md]]
- [[serial.c.md]]
- [[paging.c.md]]

## Functions
- `void hal_init()`: Initializes terminal, GDT, IDT, ISRs, IRQs, enables interrupts, and prints a separator.
