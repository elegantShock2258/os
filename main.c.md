# main.c

## Description
The main entry point for the operating system after the initial architecture-specific kernel initialization. It primarily relies on the VBE driver to run the graphical interface loop.

## Imports
- [[testing.c.md]]
- [[pit.c.md]]
- [[printf.c.md]]
- [[printf.h.md]]
- [[stdio.c.md]]
- [[kheap.c.md]]
- [[window.h.md]]
- [[vbe.c.md]]
- [[kernel_utils.c.md]]

## Variables
- `extern VbeDriverState VbeDriver`

## Functions
- `void main(void)`: Initializes the render loop via `VbeDriver.renderLoop()` and then enters an infinite halt loop.
