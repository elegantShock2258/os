# pit.c

## Description
Implementation of the Programmable Interval Timer (PIT) used for system ticks and basic sleep functionality.

## Imports
- [[serial.c.md]]
- [[isr.h.md]]

## Variables
- `volatile uint32_t ticks`

## Functions
- `void pit_init(uint32_t frequency)`: Configures PIT Channel 0.
- `void timer(Registers *regs)`: IRQ0 handler that increments `ticks`.
- `void sleep(uint32_t milliseconds)`: Halts the CPU until a target tick count is reached.
