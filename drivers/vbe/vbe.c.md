# vbe.c

## Description
Implementation of the VESA graphics driver. Sets up a backbuffer (`bf`) using `kmalloc_primitive` and provides low-level drawing primitives like `_VBE_putpixel` and `_VBE_drawRect` optimized with inline assembly `rep stosl`.

## Imports
- [[vbe.h.md]]
- [[colors.h.md]]
- [[window.h.md]]
- [[testing.c.md]]

## Variables
- `VbeDriverState VbeDriver`

## Functions
- `char *vbeDriverStateToJson(...)`: Debug function (currently largely disabled) returning a JSON representation.
- `void _VBE_putpixel(int x, int y, int color)`: Draws to the backbuffer.
- `void _VBE_drawRect(...)`: Fast rectangle drawing using `rep stosl`.
- `void _VBE_putcursor(...)`
- `void _VBE_fillScreen(...)`
- `void _VBE_init(int ebx)`: Parses multiboot info to set resolution variables and allocates the backbuffer.
- `void _VBE_render()`: Sample test drawing.
- `void _VBE_renderLoop()`: Defers to `windowManagerInit`.
- `void VbeConstructor(int ebx)`: Initializes the driver struct.
