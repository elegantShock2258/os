# isr.h

## Description
Header for Interrupt Service Routines (ISRs) and the CPU Registers state structure pushed by assembly stubs.

## Imports
- [[kernel_utils.h.md]]
- [[idt.h.md]]

## Types
- `Registers`: Packed structure representing the CPU state at the time of an interrupt.
- `ISRHandler`: Function pointer typedef.

## Functions
- `void ISR_Handler(Registers *regs)`
- `void isr_init()`
