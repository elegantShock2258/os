# irq.c

## Description
Implementation of Interrupt Request (IRQ) handling, PIC configuration, and default timer registration.

## Imports
- [[irq.h.md]]
- [[printf.c.md]]
- [[idt.c.md]]
- [[isr.c.md]]
- [[pic.c.md]]
- [[pit.c.md]]

## Variables
- `IRQHandler g_IRQHandlers[16]`

## Functions
- `void i686_IRQ_Handler(Registers *regs)`: Dispatches the IRQ to its registered handler or prints an unhandled message. Sends EOI.
- `void IRQ_RegisterHandler(int irq, IRQHandler handler)`
- `void irq_init()`: Configures PIC with offset 0x20, unmasks IRQs, registers ISR wrappers, and initializes the PIT at 1000Hz.
