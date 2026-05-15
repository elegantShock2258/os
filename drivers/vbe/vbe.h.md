# vbe.h

## Description
Header file for the VESA BIOS Extension (VBE) graphics driver. Contains the structs needed to parse the VBE info block returned by the bootloader/GRUB.

## Imports
- [[kernel_utils.c.md]]
- [[hal.h.md]]
- [[pit.c.md]]
- [[kheap.c.md]]
- [[memory.c.md]]
- [[paging.c.md]]
- [[multiboot.h.md]]
- [[keyboard.c.md]]
- [[mouse.c.md]]
- [[colors.c.md]]
- [[window.c.md]]

## Types
- `VbeInfoBlock`: Standard VESA info block (signature, version, memory).
- `vbe_mode_info_structure`: Standard VESA mode info block (pitch, width, height, framebuffer pointer).
- `svga_mode_info_t`: SVGA equivalent.
- `VbeDriverState`: State object for the graphics driver. Contains `putpixel`, `fillScreen`, `render`, `fb`, and `bf` (backbuffer).
