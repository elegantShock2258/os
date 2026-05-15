# idt.h

## Description
Definitions for the Interrupt Descriptor Table (IDT), including gate flags and table pointer structures.

## Imports
- [[kernel_utils.h.md]]
- [[printf.h.md]]

## Constants/Macros
- Various `IDT_FLAG_*` macros for ring levels and 16/32-bit gates.

## Types
- `IDTEntry`
- `idtr_t`

## Functions
- `void IDT_EnableGate(int interrupt)`
- `void IDT_DisableGate(int interrupt)`
- `void idt_set_descriptor(u8 interrupt, void (*base)(), u8 flags)`
- `void idt_init()`
