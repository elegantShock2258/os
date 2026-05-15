# mouse.h

## Description
Header definitions for the PS/2 mouse driver, supporting 3-button parsing and movement coordinates.

## Imports
- [[irq.c.md]]
- [[isr.c.md]]
- [[serial.c.md]]
- [[kernel_utils.c.md]]

## Types
- `mouse_device_packet_t`: High level mouse struct (X diff, Y diff, buttons).
- `mouse_byte_state_data`: Bit-field matching the first byte of a PS/2 packet (signs, overflows).
- `MouseDriverState`: Encapsulates driver properties and interface.

## Constants/Macros
- `MOUSE_IRQ` (12)
- Port definitions: `MOUSE_PORT`, `MOUSE_STATUS`
