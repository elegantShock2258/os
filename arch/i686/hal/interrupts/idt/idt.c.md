# idt.c

## Description
Implementation of the Interrupt Descriptor Table (IDT) configuration.

## Imports
- [[idt.h.md]]

## Variables
- `static IDTEntry idt[256]`
- `static idtr_t idtr`

## Functions
- `void IDT_EnableGate(int interrupt)`
- `void IDT_DisableGate(int interrupt)`
- `void idt_set_descriptor(u8 interrupt, void (*base)(), u8 flags)`
- `void idt_init()`: Loads the `idtr` using `lidt`.
- `void enableInterrupts()`: Uses `sti`.
- `void disableInterrupts()`: Uses `cli`.
