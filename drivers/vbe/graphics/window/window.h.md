# window.h

## Description
Header definitions for the VBE Windowing system. A Window struct represents a 2D rectangular area to be blitted onto the screen.

## Imports
- [[memory.c.md]]
- [[AvlTree.c.md]]
- [[kernel_utils.c.md]]
- [[vbe.c.md]]

## Types
- `Window`: Contains X/Y coordinates, width, height, Z-Index, and a pointer to the window's own framebuffer (`windowFb`).
