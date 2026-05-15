# drivers.md

## Directory: drivers

Encapsulates all external hardware drivers interacting with the user and generating graphical output.

### Device Drivers
- **Keyboard (`keyboard/keyboard.c`)**: A PS/2 interrupt-driven keyboard driver mapped to IRQ1. Maintains a large struct tracking keys, modifiers, locks, and multimedia controls. Scancodes are queued into a Circular Buffer.
- **Mouse (`mouse/mouse.c`)**: A PS/2 mouse driver mapped to IRQ12. Reads 3-byte cycle packets containing X/Y deltas and parses left/right/middle click bits. Clamps coords to `1920x1080`.

### VBE (VESA BIOS Extensions)
- **VBE Base (`vbe/vbe.c`)**: Provides 2D graphical functions (`_VBE_putpixel`, `_VBE_drawRect`) leveraging hardware properties parsed from GRUB's multiboot headers. Operates predominantly via a `bf` backbuffer before blitting.
- **Windowing (`vbe/graphics/window/window.c`)**: Implements a modular window manager. It treats windows as distinct nodes in an AVL tree, rendering them sequentially based on height to establish visual depth (Z-ordering) before passing them to the main screen framebuffer.


## Todo
make graphics compositor
make a jsx to c code compiler so you can write uis in jsx
